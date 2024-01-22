#ifndef WIFI_H
#define WIFI_H

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

class Wifi {
  private:
    ESP8266WiFiMulti wifi;

  public:
    Wifi();

    void connect();

    ~Wifi();
};

#endif
