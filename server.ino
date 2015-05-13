/*############################################################################################
 ESP-Led-Clock
 WiFi connected LED clock based on ESP8266

 Author: Daniele Colanardi
 License: BSD, see LICENSE file
############################################################################################*/

ESP8266WebServer server(80);

void initServer() {
	// Top level request. Returns current time.
    server.on("/", [](){
        char str[100];

        sprintf(str, "%d:%d:%d (dow: %d) %d/%d/%d (leap: %d)", time.hour, time.minute, time.second, time.dow, time.day, time.month, time.year, time.leap);
  
        server.send(200, "text/plain", str);
    });
    // In case of error generate a 404
    server.onNotFound([](){
        server.send(404, "text/plain", String("Invalid URL: ") + server.uri());
    });

    // http://<ip>/message?m=<text> 
    // Sends a message to visualize on the clock 
    server.on("/message", HTTP_GET, handleMessageCommand);

    server.on("/config", handleConfigPage);

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

void handleConfigPage() {
	
}