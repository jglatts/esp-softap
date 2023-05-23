/**
 * @file DataLogger.h
 * 
 * @author John Glatts
 * @version 0.1
 * @date 2023-05-21
 */
#ifndef __DATA_LOGGER__H__
#define __DATA_LOGGER_H__

#include "Arduino.h"
#include <WiFi.h>

#define err_loop() while(1);

#define ap_ssid  "my-ap-net"
#define ap_pw    "my-ap-net-super-pw"
#define host     "192.168.4.1"
#define port     80
#define max      10

struct DataLogger {
public:
    DataLogger();
    bool init_wifi(int);
    void run();
    String read_response();
    void connect_to_server();
private:
    void collect_data();
    void client_send(); 
    void send_server_data();
    bool server_time_out();
    long int send_count;
    int sensor_data[10];
    bool has_client;
    WiFiClient* client;
};

#endif // __DATA_LOGGER_H__