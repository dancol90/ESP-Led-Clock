/*############################################################################################
 ESP-Led-Clock
 WiFi connected LED clock based on ESP8266

 Author: Daniele Colanardi
 License: BSD, see LICENSE file
############################################################################################*/

void initWifi() {
    WiFi.begin(WIFI_SSID, WIFI_KEY);
    
    // Set scroll message
    sprintf(scroll.text, "Connecting to %s...", WIFI_SSID);

    while (WiFi.status() != WL_CONNECTED) {
    	if (!scroll.scrolling)
    		startScroll();

        delay(500);
    }

    // Connected, force stop the scroll animation
    if (scroll.scrolling)
    	stopScroll();
}