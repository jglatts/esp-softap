/**
 * @file esp_soft_ap.ino
 * 
 * @author John Glatts
 * @brief  Demo code showing a ESP as a softAP host and running a local server 
 * @version 0.1
 * @date 2023-05-21
 */
#include "MyWifi.h"
#include <WiFi.h>

/* Error forver loop */
#define err_loop() while (1) { } 

/* Global server object */
WiFiServer server(80);

/**
 * @brief Program setup and init
 */
void setup() {
  Serial.begin(115200);
  if (!WifiUtil::init_soft_ap()) {
    err_loop();
  }
  server.begin();
}

/**
 * @brief Main program loop  
 */
void loop() {
  String request = WifiUtil::handle_client(&server);
  if (request.length() > 0) {
    Serial.println("Received : ");
    Serial.println(request);
    Serial.println("From client\n");
  }
}
