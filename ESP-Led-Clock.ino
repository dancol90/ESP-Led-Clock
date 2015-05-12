/*############################################################################################
 ESP-Led-Clock
 WiFi connected LED clock based on ESP8266

 Author: Daniele Colanardi
 License: BSD, see LICENSE file
############################################################################################*/

#include <EEPROM.h>
#include <Wire.h>
#include <Ticker.h>
#include <LedControl.h>

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include "fonts.h"
#include "strings.h"
#include "config.h"
#include "structs.h"

// #############################################################################

Ticker rtc_timer;
Ticker clock_timer;
Ticker date_timer;
Ticker scroll_timer;

bool do_no_update;


// #############################################################################

void setup() { 
    initLeds();
    initScroll();
    initWifi();
    initTime();
    
    rtc_timer.attach_ms(10, updateTime);
    clock_timer.attach_ms(CLOCK_TIMEOUT, clockCallback);
    date_timer.attach(DATE_TIMEOUT,   dateCallback);

    do_no_update = false;
}

// Everything is updated in timers, no need to loop
void loop() {}

// #############################################################################

void clockCallback() {
    do_no_update = true;

    if (!scroll.scrolling) {
        drawClock();
        updateDisplay();
    }

    do_no_update = false;
}

void dateCallback() {
    do_no_update = true;

    if (!scroll.scrolling) {
        writeDate(scroll.text);
        startScroll();
    }

    do_no_update = false;
}


// #############################################################################

void drawClock() {
    // draw here
    clearBuffer();

    draw4x8Digit(0,  time.hour / 10);
    draw4x8Digit(4,  time.hour % 10);

    draw4x8Digit(9,  time.minute / 10);  
    draw4x8Digit(13, time.minute % 10);

    draw3x5Digit(18, 3, time.second / 10);  
    draw3x5Digit(21, 3, time.second % 10);
}

void writeDate(char* dest) {
    char d[4], m[12];
    
    // Get day and month names
    strcpy(d, days[time.dow]);
    strcpy(m, months[time.month - 1]);
    
    // Prepare the string
    sprintf(dest, "%s %d %s %d", d, time.day, m, time.year);
}
