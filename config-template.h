/*############################################################################################
 ESP-Led-Clock
 WiFi connected LED clock based on ESP8266

 Author: Daniele Colanardi
 License: BSD, see LICENSE file
############################################################################################*/

const char* WIFI_SSID = "";
const char* WIFI_KEY  = "";

// Time in milliseconds between a screen refresh and the next one.
const int CLOCK_TIMEOUT = 500;
// Time in seconds to wait before seeing the date scroll
const int DATE_TIMEOUT = 30;

// Scroll animation step duration
const int SCROLL_SPEED = 75;

const int TIMEZONE = +2;

const char* NTP_SERVER_HOST = "ntp1.inrim.it";
