/*############################################################################################
 ESP-Led-Clock
 WiFi connected LED clock based on ESP8266

 Author: Daniele Colanardi
 License: BSD, see LICENSE file
############################################################################################*/

extern "C" {
    #include <sntp.h>
}

const long GMT8 = 8UL * 60 * 60;
const long JAN_1_2010 = 1262304000UL;

unsigned long getTimestamp() {
    sntp_setservername(0, (char*)NTP_SERVER_HOST);

    sntp_init();

    // Wait a moment to let the sntp system to start.
    delay(200);

    // Espressif API uses the GMT+8 timezone
    long current_stamp = sntp_get_current_timestamp();

    // Compensate for the wrong timezone and change reference year to 2010
    return current_stamp - GMT8 - JAN_1_2010;
}

#if 0

const  int  NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message
byte packet_buffer[NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets

WiFiUDP udp;

unsigned long getTimestamp() {
    // Open ad UDP socket
    udp.begin(2390);

    // set all bytes in the buffer to 0
    memset(packet_buffer, 0, NTP_PACKET_SIZE);
    // Initialize values needed to form NTP request
    // (see URL above for details on the packets)
    packet_buffer[0] = 0b11100011;   // LI, Version, Mode
    packet_buffer[1] = 0;     // Stratum, or type of clock
    packet_buffer[2] = 6;     // Polling Interval
    packet_buffer[3] = 0xEC;  // Peer Clock Precision
    // 8 bytes of zero for Root Delay & Root Dispersion
    packet_buffer[12]  = 49;
    packet_buffer[13]  = 0x4E;
    packet_buffer[14]  = 49;
    packet_buffer[15]  = 52;

    // All NTP fields have been given values, now
    // you can send a packet requesting a timestamp:
    udp.beginPacket(NTP_SERVER_HOST, 123);
    udp.write(packet_buffer, NTP_PACKET_SIZE);
    udp.endPacket();

    // Wait for a response
    do {
        delay(100);
    } while (!udp.parsePacket());

    // We've received a packet, read the data from it
    udp.read(packet_buffer, NTP_PACKET_SIZE);

    // Close the socket to free some resources
    udp.stop();

    //the timestamp starts at byte 40 of the received packet.
    unsigned long highWord = word(packet_buffer[40], packet_buffer[41]);
    unsigned long lowWord  = word(packet_buffer[42], packet_buffer[43]);

    unsigned long ntpTimestamp = highWord << 16 | lowWord;
    
    // Subtract seventy years in seconds to get the corresponding unix timestamp
    return ntpTimestamp - 2208988800UL;
}

#endif