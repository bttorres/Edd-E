#ifndef EDDIE_E_WEBAPP_FUNCTIONS_H_
#define EDDIE_E_WEBAPP_FUNCTIONS_H_

// Library that allows developer to code with Arduino structure
#include <Arduino.h>
/* Libraries that allows developer to code ESP32's'
    WiFi capabilities */
#include <esp_http_server.h>
#include <esp_timer.h>
#include <soc/soc.h>
#include <soc/rtc_cntl_reg.h>
#include <ESP32Servo.h>
#include <WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SdFat.h>                  // SD card & FAT filesystem library
#include <Adafruit_SPIFlash.h>      // SPI / QSPI flash library
#include <Adafruit_ImageReader.h>   // Image-reading library
#include <SPI.h>                    // SPI needed for ESP32 to send data to ST7789

// Allow variable to be used across multiple files/functions
extern int sendVal[6];
/*/////////////////////////////////////////////////////////////////////////////
   sendVal[] structure:

   |   Pan   |   Tilt   |   Roll   |     Left Wheel      |     Right Wheel      | Action |
   |---------+----------+----------+---------------------+----------------------+--------|
   | 0 - 180 | 45 - 135 | 45 - 135 |  (+ or -) 50 - 255  |  (+ or -) 50 - 255   | 0 - 8  |

   For example: 90, 90, 90, 150, 150, 1
                90 = pan facing forward
                90 = tilt level with ground
                90 = roll level with ground
                -150 = Left wheel going backward at half speed
                150 = Right wheel going forward at half speed
                1 = happy
*/
/////////////////////////////////////////////////////////////////////////////

// Initialize functions
esp_err_t index_handler(httpd_req_t *req);
esp_err_t status_handler(httpd_req_t *req);
esp_err_t cmd_handler(httpd_req_t *req);
void startServer();

#endif // EDDIE_E_WEBAPP_FUNCTIONS_H_
