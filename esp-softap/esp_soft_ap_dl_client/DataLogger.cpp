/**
 * @file DataLogger.h
 * 
 * @author John Glatts
 * @version 0.1
 * @date 2023-05-21
 */
#include "DataLogger.h"

/**
 * @brief DatalLogger constructor
 */
DataLogger::DataLogger(): client{nullptr} {
    send_count = 0;
    for (int i = 0; i < max; i++)
        sensor_data[i] = 0;
}

/**
 * @brief Check for a timeout from the server  
 */
bool DataLogger::server_time_out() {
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
String DataLogger::read_response() {
  String line;

  if (server_time_out())
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
  if (!client->connect(host, port)) {
    Serial.println("Couldnt connect to server");
    return;
  }
}

/**
 * @brief Send data from client to server
 */
void DataLogger::client_send() {
  client->print("I LOVE MY STINKY\n");
  client->print("count\n");
  client->print(send_count++);
  client->print("\n\n");
  if (send_count >= 1000000) send_count = 0;
}

/**
 * @brief Main Datalogger function to collect data and send to server
 */
void DataLogger::run() {
  WiFiClient c;
  client = &c;
  connect_to_server();
  collect_data();
  client_send();
  Serial.println(read_response());
  //send_server_data();
}

/**
 * @brief Send data to the server 
 */
void DataLogger::send_server_data() {

}

/**
 * @brief Send data from client to server
 */
void DataLogger::collect_data() {
  for (int i = 0; i < max; i++) {
    // collect some sensor data to send 
  }
}

/**
 * @brief Init  ESP client wifi device as a station
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