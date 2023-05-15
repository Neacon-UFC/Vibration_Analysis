#include <WiFi.h>
 
#define SSID "Lamotriz"
#define PASSWORD "lamotrizwifi2"

unsigned long int last_time = millis();
const uint16_t port = 4242;
const char * host = "10.101.94.54";

void setup() {
  Serial.begin(9600);

  WiFi.begin(SSID,PASSWORD);
  while (WiFi.status() != WL_CONNECTED){delay(100);}

  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  WiFiClient client;
 
  if (!client.connect(host, port)) {
      Serial.println("Falha de conexao");
      delay(1000);
      return;
  }

  Serial.println("Conectado!");

  client.print("Hello word");

  Serial.println("Desconectando...");
  client.stop();

  Serial.print("Aguardando 15 segundos para proximo envio:");
  while ((millis()-last_time) < 15000){delay(100);}
  last_time = millis();
}
