/*############################################################################################
 ESP-Led-Clock
 WiFi connected LED clock based on ESP8266

 Author: Daniele Colanardi
 License: BSD, see LICENSE file
############################################################################################*/

#include "string.h"
#include "pages.h"

ESP8266WebServer server(80);

void initServer() {
    // In case of error generate a 404
    server.onNotFound([](){
        server.send(404, "text/plain", String("Invalid URL: ") + server.uri());
    });

    // Main page - configuration
    server.on("/",  handleConfig);

    // http://<ip>/message?m=<text> 
    // Sends a message to visualize on the clock 
    server.on("/message", HTTP_GET, handleMessageCommand);

    // Returns current time.
    server.on("/time", handleTime);

    server.begin();
}

void updateServer() {
    server.handleClient();
}

void handleMessageCommand() {
    server.arg("m").toCharArray(scroll.text, 250);

    startScroll();

    server.send(200, "text/plain", "success");
}

void handleTime() {
    char str[100];

    sprintf(str, "{h: %d, m: %d, s: %d, dow: %d, d: %d, m: %d, y: %d, leap: %d}", time.hour, time.minute, time.second, time.dow, time.day, time.month, time.year, time.leap);

    server.send(200, "text/json", str);
}


void handleConfig() {
    if (server.method() == HTTP_POST) {
        server.arg("ssid").toCharArray(config.wifi_ssid, STRING_LENGTH);
        server.arg("password").toCharArray(config.wifi_key, STRING_LENGTH);

        commitConfig();
    }

    String p(FLASH_STR(config_html));

    p.replace("%%ssid%%", config.wifi_ssid);
    p.replace("%%key%%",  config.wifi_key);

    server.send(200, "text/html", p);
}
