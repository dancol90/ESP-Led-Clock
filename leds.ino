/*############################################################################################
 ESP-Led-Clock
 WiFi connected LED clock based on ESP8266

 Author: Daniele Colanardi
 License: BSD, see LICENSE file
############################################################################################*/

const short ic_count = 3;

/*
 pin 0 is connected to the DataIn 
 pin 2 is connected to the CLK 
 pin 1 (TX) is connected to LOAD 
 */
LedControl lc = LedControl(0,2,1, ic_count);

// 8 rows of 8*3 pixel each = 24*8 display
long buffer[8];

void initLeds() {
    for(int i = 0; i < ic_count; i++) {
        // The MAX72XX is in power-saving mode on startup, we have to do a wakeup call
        lc.shutdown(i, false);
        // Set the brightness
        lc.setIntensity(i, 15);
        // and clear the display 
        lc.clearDisplay(i);
    }

    clearBuffer();
}

// #############################################################################

void clearBuffer() {
    for(int i = 0; i < 8; i++) {
        buffer[i] = 0;
    }
}

void clearDisplay() {
    for(int i = 0; i < ic_count; i++) {
        // clear the display 
        lc.clearDisplay(i);
    }  
}

void updateDisplay() {
    int shift;

    for(int d = 0; d < ic_count; d++) {
        // buffer[i] (long) structure:
        // 00000000  xxxxxxxx  xxxxxxxx  xxxxxxxx
        //  ignored  matrix 0  matrix 1  matrix 2
        shift = 8 * d;//(2 - d);

        for(int i = 0; i < 8; i++)
            lc.setRow(d, i, buffer[i] >> shift);
    }
}

// #############################################################################

void draw4x8Digit(uint8_t x, uint8_t digit) {
    uint8_t offset = 8 * digit;

    long tmp, mask;
    
    for(int j = 0; j < 8; j++) {
        // Allineo la riga del carattere (formato xxxx0000) al bordo sinistro
        tmp = (long)font_numbers[offset + j] << 16;

        mask = ((long)B11110000 << 16) >> x;

        buffer[j] = (buffer[j] & ~mask) + ( (tmp >> x) & mask );
    }
}


void draw3x5Digit(uint8_t x, uint8_t y, uint8_t digit) {
    uint8_t offset = 5 * digit;

    long tmp, mask;

    uint8_t count = y + 5;

    if(count > 8) count = 8;
    
    for(uint8_t j = y; j < count; j++) {
        // Allineo la riga del carattere (formato xxx00000) al bordo sinistro
        tmp = (long)small_numbers[offset + j - y] << 16;

        mask = ((long)B11100000 << 16) >> x;

        buffer[j] = (buffer[j] & ~mask) + ( (tmp >> x) & mask );
    }
}
