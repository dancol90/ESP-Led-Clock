/*############################################################################################
 ESP-Led-Clock
 WiFi connected LED clock based on ESP8266

 Author: Daniele Colanardi
 License: BSD, see LICENSE file
############################################################################################*/

struct scrollData {
    unsigned int step;
    
    char         text[250];
    uint8_t      text_len;
    
    uint8_t      glyph[8];

    uint8_t      position;
    uint8_t      column_left;

    bool         scrolling;
} scroll;

struct {
    int hour;
    int minute;
    int second;

    int day;
    int month;
    int year;

    int dow;

    bool leap;
} time;

struct _config_s {
    int programmed;

    // Time in milliseconds between a screen refresh and the next one.
    int clock_timeout;
    // Time in seconds to wait before seeing the date scroll
    int date_timeout;

    // Scroll animation step duration
    uint8_t scroll_speed;
    uint8_t timezone;

    char ntp_server_host[40];

    char wifi_ssid[40];
    char wifi_key[40];
} config;
