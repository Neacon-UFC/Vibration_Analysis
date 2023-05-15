/**********************
 * University Federal of Ceará - UFC                          *
 * Lamotriz - Laboratory (Driving Force Systems Laboratory)   *
 * Author: Joel Pontes                                        *
 * ********************/

// Libraries
//#include <Adafruit_MPU6050.h>
//#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <WiFi.h>
#include <PubSubClient.h>

// Defines
#define pi 3.1415 // Pi value

// Defining Current Pinout
#define i1 36  // ADC_0 GPIO36
#define i2 39  // ADC_3 GPIO39
#define i3 34  // ADC_6 GPIO34

// Defining MPU-6050 Pinout
#define SCL 22  //GPI022
#define SDA 21  //GPI021

// Defining MQTT Port
#define mqtt_port 1883

// Defining Serial Speed
#define serial_speed 115200

// Defining timer MPU 
#define mpu_timer 100  // Ts = 0.1s

// MPU-6050 I2C Address
const int MPU_addr=0x68;
const int size_request=14;

// Wifi Parameters
const char* ssid = "Lamotriz";
const char* password = "lamotrizwifi2";

// Mqtt Parameters
const char* mqtt_server = "10.101.94.64";             // Mqtt Broker IP
// Mqtt Topics
const char* mqtt_topic = "mpu6050/acceleration/x";
const char* mqtt_topic2 = "mpu6050/acceleration/y";
const char* mqtt_topic3 = "mpu6050/acceleration/z";
const char* mqtt_topic4 = "mpu6050/acceleration/samples";

// Number of samples to send by Mqtt
int acceleration_samples = 0;

// Global Variables
// Aceleration for each axe
// 8 bits H + 8 bits L
int16_t AcX;
int16_t AcY;
int16_t AcZ;
// Float values
float Ax;
float Ay;
float Az;

// Gyroscope for each axe
// 8 bits H + 8 bits L
int16_t GyX;
int16_t GyY;
int16_t GyZ;
// Float values
float Gx;
float Gy;
float Gz;

// Temperature
int16_t Tmp;

// MPU Timer variables
uint64_t mpu_last_time=0;

// Starting Objects
WiFiClient wifiClient;                // Wifi Object
PubSubClient mqttClient(wifiClient);  // Mqtt Object

void setup() {
  // Setting Serial speed
  Serial.begin(serial_speed);
  // Wait until serial console opens
  while (!Serial)
    delay(10);         

  // Setting pinout Modes
  pinMode(i1, INPUT);
  pinMode(i2, INPUT);
  pinMode(i3, INPUT);

  // Connecting to Wifi...
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // Setting MQTT server and port
  mqttClient.setServer(mqtt_server, mqtt_port);
  // Setting callback function
  mqttClient.setCallback(callback);

  // Connecting to Mqtt Broker...
  while (!mqttClient.connected()) {
    Serial.println("Connecting to MQTT broker...");
    if (mqttClient.connect("ESP32Client")) {
      Serial.println("Connected to MQTT broker.");
      // Subscribing to the topics.
      // Add the topics there.
      mqttClient.subscribe(mqtt_topic);
      mqttClient.subscribe(mqtt_topic2);
      mqttClient.subscribe(mqtt_topic3);
      mqttClient.subscribe(mqtt_topic4);

    } else {
      Serial.print("Failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
  }

  // Starting I2C Protocol
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);                   // PWR_MGMT_1 register
  Wire.write(0);                      // Defining as 0 (wakes up the MPU-6050)
  Wire.endTransmission(true);         // Finishing Transmission
}

void loop() {

  // Timer for the MPU routine
  if (millis()-mpu_last_time >= mpu_timer){
    // Reading MPU data
    mpu_read();

    if(acceleration_samples){
      // Sending data by Mqtt
      String message = String(Ax);
      mqttClient.publish(mqtt_topic, message.c_str());
      message = String(Ay);
      mqttClient.publish(mqtt_topic2, message.c_str());
      message = String(Az);
      mqttClient.publish(mqtt_topic3, message.c_str());
      acceleration_samples--;
    }

    mpu_last_time = millis();
  }
  
  // Mqtt Loop
  mqttClient.loop();
}


// MPU function
void mpu_read(){
  // Start Transmission
  Wire.beginTransmission(MPU_addr);

  // Send to Master the value 0x3B
  Wire.write(0x3B);                       // starting with register 0x3B (ACCEL_XOUT_H)

  // Keeping the Transmission
  Wire.endTransmission(false);

  // Requesting data from MPU
  
  Wire.requestFrom(MPU_addr, 14);         // request a total of 14 registers
  AcX = Wire.read()<<8|Wire.read();       // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read()<<8|Wire.read();       // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read()<<8|Wire.read();       // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read()<<8|Wire.read();       // 0x41 (TEMP_OUT_H)   & 0x42 (TEMP_OUT_L)
  GyX = Wire.read()<<8|Wire.read();       // 0x43 (GYRO_XOUT_H)  & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read()<<8|Wire.read();       // 0x45 (GYRO_YOUT_H)  & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read()<<8|Wire.read();       // 0x47 (GYRO_ZOUT_H)  & 0x48 (GYRO_ZOUT_L)

  /* convert the RAW values into acceleration in 'g'
   *  we have to divide according to the Full scale value set in FS_SEL
   *  I have configured FS_SEL = 0. So I am dividing by 16384.0
   *  for more details check ACCEL_CONFIG Register              
   */
   
  Ax = (float)AcX/16384.0;
  Ay = (float)AcY/16384.0;
  Az = (float)AcZ/16384.0;
  
  /* 
   *  convert the RAW values into dps (º/s)
   *  we have to divide according to the Full scale value set in FS_SEL
   *  I have configured FS_SEL = 0. So I am dividing by 131.0
   *  for more details check GYRO_CONFIG Register              
   */
   
  Gx = (float)(GyX/131.0)*(pi/180);
  Gy = (float)(GyY/131.0)*(pi/180);
  Gz = (float)(GyZ/131.0)*(pi/180);

  // Printing the values on Serial Monitor
  //Serial.print("Valores do acelerômetro: \n");
  //Serial.print("("); Serial.print(Ax); Serial.print(","); Serial.print(Ay); Serial.print(","); Serial.print(Az); Serial.print(")"); 
  //Serial.print("\nTemperature: " );  
  //Serial.print(Tmp);
  //Serial.print("\nValores do giroscópio: \n");
  //Serial.print("("); Serial.print(Gx); Serial.print(","); Serial.print(Gy); Serial.print(","); Serial.print(Gz);Serial.print(")\n"); 
}

// Callback Mqtt
void callback(char* topic, byte* payload, unsigned int length) {
  // Routine to topic 4
  if(!strcmp(topic, mqtt_topic4)){
    String message;
    for (int i = 0; i < length; i++) {
      message += (char)payload[i];
    }
    // Converting to integer
    acceleration_samples = message.toInt();
    
    // Printing sample size
    Serial.print("Acceleration Sample Size = [");
    Serial.print(acceleration_samples);
    Serial.print("] ");
  }
}

/*
void reconnect() {
  // Reconect to the Mqtt Broker
  while (!mqttClient.connected()) {
    Serial.print("Tentando reconectar ao servidor MQTT...");
    if (mqttClient.connect("ESP32Client")) {
      Serial.println("Conectado");
      mqttClient.subscribe(mqtt_topic);
    } else {
      Serial.print("Falha na conexão MQTT, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" tentando novamente em 5 segundos");
      delay(5000);
    }
  }
}
*/