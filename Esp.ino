#include "Wifi.h"
#include "SerialCommunication.h"
#include <PubSubClient.h>

Wifi wifi;
SerialCommunication serial;

WiFiClient espClient;
PubSubClient client(espClient);

String received = "";
String lastMsg = "";

const char * server = "192.169.131.29";
const int port = 1883;

void callback(char* topic, byte* payload, unsigned int length) {
  received = "";

  for (int i = 0; i < length; i++) {
    char c = (char)payload[i];
    received += c;
  }
}


void reconnect() {

  while (!client.connected()) {
    Serial.print("Tentando se reconectar ao broker MQTT...");
    
    String topic = "stem/prototipos/" + serial.getMsg()["Id"].as<String>();
    
    if (client.connect(serial.getMsg()["Id"].as<String>().c_str())) {
      Serial.println("Conectado!");

      client.subscribe(topic.c_str());
    } else {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos...");

      delay(5000);
    }
  }
}


void setup() 
{
  Serial.begin(9600);
  
  wifi.connect();
  
  client.setServer(server, port);
  client.setCallback(callback);

  serial.waitHandshake("{\"Id\": \"ESP\", \"Data\": \"Ok\"}");
  delay(1000);
}

void loop() 
{
  if (!client.connected())
  {
    reconnect();
  }

  if (lastMsg != received)
  {
    serial.send(received);

    lastMsg = received;
  }

  client.loop();
}
