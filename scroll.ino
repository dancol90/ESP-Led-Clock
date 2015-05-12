/*############################################################################################
 ESP-Led-Clock
 WiFi connected LED clock based on ESP8266

 Author: Daniele Colanardi
 License: BSD, see LICENSE file
############################################################################################*/

// the maximum value of scrollStep is strlen(dateStr)*5 + 24 (+24 let the scroll effect exit to the left)

void initScroll() {
    scrolling = true;

    scroll.text_len = strlen(scroll.text);

    // Reset the step count
    scroll.step = 0;
    scroll.column_left = 0;

    scroll_timer.attach_ms(SCROLL_SPEED, updateScroll);
}

void updateScroll() {
    scrollTextStep();

    updateDisplay();

    // Do scroll ended? e.g, have we moved everything?
    if (scroll.step == 5 + scroll.text_len * 5 + 24) {
        stopScroll();
    }
}

void stopScroll() {
    scroll_timer.detach();
    scrolling = false;
}

// #############################################################################


void scrollTextStep() {
    // If the current character has been completely showed, load a new one.
    if(scroll.column_left == 0) {
        // Get the char entire data (5 row, each one is a byte)
        for(int r = 0; r < 5; r++) {
            if(scroll.step != 0 && scroll.step <= scroll.text_len * 5) {
                uint8_t c = scroll.text[(scroll.step - 1) / 5];
                scroll.glyph[r] = font5x5[(c - 32) * 5 + r];
            } else
                scroll.glyph[r] = 0x00;
        }

        // reset the counter
        scroll.column_left = 5;
    }

    // For each row of the screen
    for(int i = 0; i < 8; i++) {
        // Move the row to the left
        buffer[i] = buffer[i] << 1;

        // do this only if this row is one in which the char goes.
        if(i >= 2 && i < 7)
            buffer[i] += scroll.glyph[i - 2] >> (scroll.column_left + 2) & 0x01;
    }

    scroll.column_left--;

    scroll.step++;
}

