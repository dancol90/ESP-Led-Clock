/*############################################################################################
 ESP-Led-Clock
 WiFi connected LED clock based on ESP8266

 Author: Daniele Colanardi
 License: BSD, see LICENSE file
############################################################################################*/

/*
    Some of the code below is inspired by ESP8266-Arduino EEPROM library
*/

extern "C" {
    #include "spi_flash.h"
}

#define CONFIG_START_SECTOR 0x7b
//#define CONFIG_SECTOR_INDEX (CONFIG_START_SECTOR + 0)
#define CONFIG_START_ADDR (SPI_FLASH_SEC_SIZE * CONFIG_START_SECTOR)

void initConfig() {
    // Read config from flash
    spi_flash_read(
        CONFIG_START_ADDR,
        reinterpret_cast<uint32_t*>(&config),
        sizeof(config)
    );

    if (config.programmed != 0xDC) {
        // No configuration in flash! Save defaults.

        config = { 
            .programmed = 0xDC,
            .clock_timeout = CLOCK_TIMEOUT, .date_timeout = DATE_TIMEOUT,
            .scroll_speed = SCROLL_SPEED,
            .timezone = TIMEZONE
        };

        strcpy(config.ntp_server_host, NTP_SERVER_HOST);

        commitConfig();
    }
}

void commitConfig() {
    if (spi_flash_erase_sector(CONFIG_START_SECTOR) == SPI_FLASH_RESULT_OK)
        // Write data to flash
        spi_flash_write(
            CONFIG_START_ADDR,
            reinterpret_cast<uint32_t*>(&config),
            sizeof(config)
        );
}