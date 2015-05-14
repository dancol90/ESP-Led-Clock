/*############################################################################################
 ESP-Led-Clock
 WiFi connected LED clock based on ESP8266

 Author: Daniele Colanardi
 License: BSD, see LICENSE file
############################################################################################*/


#define FLASH_STR(str) reinterpret_cast<const __FlashStringHelper *>(str)

const char config_html[] PROGMEM = "<html><head><title>Led Clock Configuration</title><style type=\"text/css\">body{font-family: sans-serif;}</style></head><body><h1>WiFi LED Clock</h1><h2>Configuration page</h2><form method=\"POST\"><label>SSID: <input name=\"ssid\" type=\"text\" value=\"%%ssid%%\"></label><label>Password: <input name=\"password\" type=\"password\" value=\"%%key%%\"></label><button type=\"submit\">Save</button></form></body></html>";