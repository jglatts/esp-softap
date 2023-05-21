#include "DataLogger.h"

/**
 * @brief DatalLogger constructor
 */
DataLogger::DataLogger() {
    send_count = 0;
    for (int i = 0; i < max; i++)
        sensor_data[i] = 0;
}

/**
 * @brief Check for a timeout from the server  
 */
bool DataLogger::server_time_out(WiFiClient* client) {
  unsigned long start = millis();

  while (!client->available()) {
    if (millis() - start > 5000) {
        Serial.println("Time out from server!\n");
        client->stop();
        return true;
    }
   }

   return false;
}

/**
 * @brief Read and and return response from server 
 */
String DataLogger::read_response(WiFiClient* client) {
  String line;

  if (server_time_out(client))
    return "";

  while(client->available()) {
    line += client->readStringUntil('\r');
  }

  return line;
}

/**
 * @brief Connect and get the response from server
 */
void DataLogger::connect_to_server() {
  WiFiClient client;

  if (!client.connect(host, port)) {
    Serial.println("Couldnt connect to server");
    return;
  }
  
  client_send(&client);
  Serial.print(read_response(&client));
}

/**
 * @brief Send data from client to server
 */
void DataLogger::client_send(WiFiClient* client) {
  client->print("I LOVE MY STINKY\n");
  client->print("count\n");
  client->print(send_count++);
  client->print("\n\n");
  if (send_count >= 1000000) send_count = 0;
}

/**
 * @brief Init ESP client wifi device as a station
 */
bool DataLogger::init_wifi(int num_times) {
  int i;
  WiFi.mode(WIFI_STA);
  WiFi.begin(ap_ssid, ap_pw);
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