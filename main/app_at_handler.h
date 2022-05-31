#include "stdio.h"
#include "libcat.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

/* AT */
static int handler_at(const struct cat_command* cmd){
    return CAT_RETURN_STATE_OK;
}

/* ATI */
static int handler_at_i(const struct cat_command* cmd){
    esp_chip_info_t info;
    esp_chip_info(&info);
    printf("IDF Version:%s\r\n", esp_get_idf_version());
    printf("Chip info:\r\n");
    char* chip_name = "Unknown";
    switch(info.model){
        case CHIP_ESP32: chip_name = "ESP32"; break;
        case CHIP_ESP32S2: chip_name = "ESP32S2"; break;
        case CHIP_ESP32S3: chip_name = "ESP32S3"; break;
        case CHIP_ESP32C3: chip_name = "ESP32C3"; break;
    }
    printf("\tmodel:%s\r\n", chip_name);
    printf("\tcores:%d\r\n", info.cores);
    printf("\tfeature:%s%s%s%s%d%s\r\n",
           info.features & CHIP_FEATURE_WIFI_BGN ? "/802.11bgn" : "",
           info.features & CHIP_FEATURE_BLE ? "/BLE" : "",
           info.features & CHIP_FEATURE_BT ? "/BT" : "",
           info.features & CHIP_FEATURE_EMB_FLASH ? "/Embedded-Flash:" : "/External-Flash:",
           spi_flash_get_chip_size() / (1024 * 1024), " MB");
    printf("\trevision number:%d\r\n", info.revision);
    return CAT_RETURN_STATE_OK;
}

/* AT+HELP */
static int handler_at_help(const struct cat_command *cmd){
    return CAT_RETURN_STATE_PRINT_CMD_LIST_OK;
}

const struct cat_command cmd_at = {
    .name = "",
    .run = handler_at,
};

const struct cat_command cmd_ati = {
    .name = "I",
    .run = handler_at_i,
};

const struct cat_command cmd_help = {
    .name = "+HELP",
    .run = handler_at_help,
};

/* declaring commands array */
static struct cat_command cmds[] = {cmd_at, cmd_ati, cmd_help};