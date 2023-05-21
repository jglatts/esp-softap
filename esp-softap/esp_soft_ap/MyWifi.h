/**
 * @file MyWifii.cpp
 * 
 * @author John Glatts
 * @brief  WiFi.h utility functions for ESP32
 * @version 0.1
 * @date 2023-05-21
 */
#ifndef __MYWIFI__H__
#define __MYWIFI__H__

#include "Arduino.h"
#include <WiFi.h>

#define ssid     "ssid"
#define pw       "pw"
#define ap_ssid  "my-ap-net"
#define ap_pw    "my-ap-net-super-pw"
#define host     "10.0.0.136"
#define port     80

struct WifiUtil {
public:
    static bool init_wifi(int);
    static bool init_soft_ap();
    static bool eval_line(String*);
    static void check_found(bool*, String);
    static String handle_client(WiFiServer*);
    static void client_send_http(WiFiClient*, bool);
};

#endif //__MYWIFI__H__
