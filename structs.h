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