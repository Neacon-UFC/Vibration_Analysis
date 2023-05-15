// Libraries
#include <Wire.h>
#include <WiFi.h>
#include <PubSubClient.h>

// Pinout
// Defining Current Pinout
#define i1 0  // ADC_0
#define i2 1  // ADC_1
#define i3 2  // ADC_2

// Defining MPU-6050 Pinout
#define SCL 22  //GPI022
#define SDA 21  //GPI021

// Defining MQTT Port
#define mqtt_port 1883

// Defining Serial Speed
#define serial_speed 115200

// Defining timer MPU 
#define mpu_timer 3000  // 3000 ms

// MPU-6050 I2C Address
#define MPU_addr 0x68

// Wifi Parameters
const char* ssid = "Lamotriz";
const char* password = "lamotrizwifi2";

// Mqtt Parameters
const char* mqtt_server = "10.101.94.54";   // Mqtt Broker IP
// Mqtt Topics
const char* mqtt_topic = "test";
//const char* mqtt_topic2 = "";

// Global Variables
// Aceleration for each axe
int16_t AcX;
int16_t AcY;
int16_t AcZ;

// Gyroscope for each axe
int16_t GyX;
int16_t GyY;
int16_t GyZ;

// Temperature
int16_t Tmp;

// MPU Timer variables
uint64_t mpu_last_time=0;

// Starting Objects
// Wifi Object
WiFiClient wifiClient;
// Mqtt Object
PubSubClient mqttClient(wifiClient);

void setup() {
  // Setting Serial speed
  Serial.begin(serial_speed);

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

  // Connecting to Mqtt Broker...
  while (!mqttClient.connected()) {
    Serial.println("Connecting to MQTT broker...");
    if (mqttClient.connect("ESP32Client")) {
      Serial.println("Connected to MQTT broker.");
      // Subscribing to the topics.
      // Add the topics there.
      mqttClient.subscribe(mqtt_topic);
      //mqttClient.subscribe(mqtt_topic2);
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

    mpu_last_time = millis();
  }
  
  // Mqtt Loop
  mqttClient.loop();

  //String message = String(random(24,30));
  //mqttClient.publish(mqtt_topic, message.c_str());
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
  Wire.requestFrom(MPU_addr,14,true);     // request a total of 14 registers
  AcX = Wire.read()<<8|Wire.read();       // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read()<<8|Wire.read();       // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read()<<8|Wire.read();       // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read()<<8|Wire.read();       // 0x41 (TEMP_OUT_H)   & 0x42 (TEMP_OUT_L)
  GyX = Wire.read()<<8|Wire.read();       // 0x43 (GYRO_XOUT_H)  & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read()<<8|Wire.read();       // 0x45 (GYRO_YOUT_H)  & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read()<<8|Wire.read();       // 0x47 (GYRO_ZOUT_H)  & 0x48 (GYRO_ZOUT_L)

  // Printing the values on Serial Monitor
  Serial.print("Valores do acelerômetro: \n");
  Serial.print("AcX: "); 
  Serial.print(AcX); 
  Serial.print("\nAcY: "); 
  Serial.print(AcY); 
  Serial.print("\nAcZ: "); 
  Serial.print(AcZ);   
  Serial.print("\nTemperature: " );  
  Serial.print(Tmp);
  Serial.print("\nValores do giroscópio: \n");
  Serial.print("GyX: "); 
  Serial.print(GyX); 
  Serial.print("\nGyY: "); 
  Serial.print(GyY); 
  Serial.print("\nGyZ: "); 
  Serial.print(GyZ);
  Serial.print("\n");
}
