/**
 * @file esp_soft_ap_dl_client.ino
 * 
 * @author John Glatts
 * @brief  Demo code showing a ESP as a data logger. 
 *         Connects to a ESP server running as a softap 
 * @version 0.1
 * @date 2023-05-21
 */
#include "DataLogger.h"

DataLogger logger;

/**
 * @brief Program setup and init 
 */
void setup() {
  Serial.begin(115200);
  if (!logger.init_wifi(1000)) {
    while (1); // NOP
  }
}

/**
 * @brief Main program loop 
 */
void loop() {
    logger.run();
}
