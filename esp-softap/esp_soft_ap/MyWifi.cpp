/**
 * @file MyWifii.cpp
 * 
 * @author John Glatts
 * @brief  WiFi.h utility functions for ESP32
 * @version 0.1
 * @date 2023-05-21
 */
#include "MyWifi.h"
#include "Arduino.h"
#include <WiFi.h>

/**
 *  @brief Init the esp as a wifi station 
 */
bool WifiUtil::init_wifi(int num_times) {
  int i;
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pw);
  Serial.print("Connecting to Wifi...");
  for (i = 0; i < num_times; i++) {
    if (WiFi.status() != WL_CONNECTED) {
          Serial.print('.');
          if (i % 10 == 0 && i != 0)
            Serial.println("");
          delay(1000);
    }
    else break;
  }
  if (i == num_times) return false;
  Serial.print("\nConnected to ");
  Serial.println(WiFi.localIP());
  return true;
}

/**
 *  @brief Init the esp as softAP device 
 */
bool WifiUtil::init_soft_ap() {
  WiFi.mode(WIFI_AP);
  if (!WiFi.softAP(ap_ssid, ap_pw)) {
    return false;
  }
  Serial.print("\nSoftAP Created with IP: ");
  Serial.println(WiFi.softAPIP());
  return true;  
}

/**
 *  @brief Handles client request
 *         Checks for two new lines ('\n\n') to indicate end of request 
 */
String WifiUtil::handle_client(WiFiServer* server) {
  WiFiClient client = server->available();
  String current_line = "";
  char old_c;
  bool found = false;

  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();   
        if (c == '\r')
          continue;
        else if (c == '\n' && old_c == '\n') {
          for (int i = 0; i < 100; i++) {
            client.println("HELLO FROM SERVER");
          }
          break;
        } 
        else 
          current_line += c;
        old_c = c;
        check_found(&found, current_line);
      }
    }
    client.stop();
  }

  return current_line;
}  

/**
 * @brief Send a example HTTP response to a client 
 */
void WifiUtil::client_send_http(WiFiClient* client, bool found) {
  client->println("HTTP/1.1 200 OK");
  client->println("Content-type:text/html");
  client->println();
  if (!found) {
    client->print("Hello World<br>");
    client->print("Click <a href=\"/H\">Here</a><br>");
  }
  else {
    client->print("Thanks for clicking!");
    client->print("Click <a href=\"/B\">Here</a> To Go Back<br>");
  }
}

/**
 * @brief Check the current line for any get requests 
 */
void WifiUtil::check_found(bool* found, String line) {
  if (line.endsWith("GET /H")) {
    *found = true;
  } 
  if (line.endsWith("GET /B")) {
    *found = false;
  }  
}

/**
 *  @brief Check the current request  for two new lines 
 */
bool WifiUtil::eval_line(String* line) {
  if (line->length() != 0) {
    *line = "";
    return false;
  }
  else {
    return true;
  }
}
