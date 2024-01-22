#include "Wifi.h"

Wifi::Wifi() {
  wifi.addAP("ssid", "pass"); 
};

void Wifi::connect() {
  WiFi.mode(WIFI_STA);
  
  Serial.print("Conectando");

  while (wifi.run() != WL_CONNECTED) {
    Serial.print(".");
  }
  
  Serial.println();
  Serial.println("Conexão Estabelecida");
  Serial.print("Conectado a ");
  Serial.println(WiFi.SSID());
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
};

Wifi::~Wifi() {};
