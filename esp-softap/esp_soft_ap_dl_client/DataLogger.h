#ifndef __DATA_LOGGER__H__
#define __DATA_LOGGER_H__

#include "Arduino.h"
#include <WiFi.h>

#define ap_ssid  "my-ap-net"
#define ap_pw    "my-ap-net-super-pw"
#define host     "192.168.4.1"
#define port     80
#define max      10

struct DataLogger {

public:
    DataLogger();
    bool init_wifi(int);
    String read_response(WiFiClient*);
    void connect_to_server();
private:
    void client_send(WiFiClient*); 
    bool server_time_out(WiFiClient*);
    long int send_count;
    int sensor_data[10];

};

#endif // __DATA_LOGGER_H__