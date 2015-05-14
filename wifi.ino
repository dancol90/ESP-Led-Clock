/*############################################################################################
 ESP-Led-Clock
 WiFi connected LED clock based on ESP8266

 Author: Daniele Colanardi
 License: BSD, see LICENSE file
############################################################################################*/

bool initWifi() {
    byte status = 0;
    char msg[40];

    // Don't even try to connect if no config is provided.
    if (strlen(config.wifi_ssid) != 0) {
        // Station mode, connect to AP.
        WiFi.mode(WIFI_STA);
        WiFi.begin(config.wifi_ssid, config.wifi_key);
        
        // Set scroll message
        strcpy(scroll.text, "CONNECTING");

        do {
            status = WiFi.status();

            // Reshow the message if WiFi isn't connected yet.
            if (!scroll.scrolling)
                startScroll();

            delay(200);
        } while (status != WL_CONNECTED && status != WL_CONNECT_FAILED);
    }

    // At this point the connection can be established or there can be errors
    if (status == WL_CONNECTED) {

        // Connected. Get the module's IP address.
        IPAddress ip = WiFi.localIP();
        
        // Show new message with connection info
        sprintf(scroll.text, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
        startScroll();

        // Everything all right, go on.
        return true;

    } else {

        // Error, enter in configuration mode.
        WiFi.mode(WIFI_AP);
        WiFi.softAP("ESP-Led-Clock");

        // Show new message with connection info
        strcpy(scroll.text, "CONFIGURATION MODE");
        startScroll();

        return false;
    
    }
}