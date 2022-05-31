#include "pthread.h"
#include "driver/uart.h"
#include "esp_vfs_dev.h"
#include "libcat.h"

#include "app_at_handler.h"

static int at_task_status = 0;

//Libcat
struct cat_object at;
static uint8_t at_buffer[128];



static struct cat_command_group cmd_group = {
    .cmd = cmds,
    .cmd_num = sizeof(cmds) / sizeof(cmds[0]),
};

static struct cat_command_group* cmd_desc[] = {
    &cmd_group
};

/* Register cmds */
static struct cat_descriptor desc = {
    .cmd_group = cmd_desc,
    .cmd_group_num = sizeof(cmd_desc) / sizeof(cmd_desc[0]),

    .buf = at_buffer,
    .buf_size = sizeof(at_buffer)
};

/* custom target dependent input output handlers */
static int write_char(char ch){
    putc(ch, stdout);
    return 1;
}

static int read_char(char *ch){
    *ch = getc(stdin);
    putc(*ch, stdout);
    return 1;
}

static struct cat_io_interface iface = {
    .read = read_char,
    .write = write_char,
};

/**
 * @brief Subthread function for AT commands
 * 
 */
void* at_task(){
    while(1){
        //Avoid to trige watchdog
        if(!(cat_service(&at) != 0)){
            printf("AT service stopped\n");
            break;
        }
    }
    return &at_task_status;
}

/**
 * @brief Init UART
 * 
 */
void init_uart(){
     /* Drain stdout before reconfiguring it */
    fflush(stdout);
    fsync(fileno(stdout));
    /* Disable buffering on stdin */
    setvbuf(stdin, NULL, _IONBF, 0);

    /* Minicom, screen, idf_monitor send CR when ENTER key is pressed */
    esp_vfs_dev_uart_port_set_rx_line_endings(CONFIG_ESP_CONSOLE_UART_NUM, ESP_LINE_ENDINGS_CR);
    /* Move the caret to the beginning of the next line on '\n' */
    esp_vfs_dev_uart_port_set_tx_line_endings(CONFIG_ESP_CONSOLE_UART_NUM, ESP_LINE_ENDINGS_CRLF);

    /* Configure UART. Note that REF_TICK is used so that the baud rate remains
     * correct while APB frequency is changing in light sleep mode.
     */
    uart_config_t uart_config = {
        .baud_rate = CONFIG_ESP_CONSOLE_UART_BAUDRATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
#if CONFIG_IDF_TARGET_ESP32 || CONFIG_IDF_TARGET_ESP32S2
        .source_clk = UART_SCLK_REF_TICK,
#else
        .source_clk = UART_SCLK_XTAL,
#endif
    };
    /* Install UART driver for interrupt-driven reads and writes */
    ESP_ERROR_CHECK(uart_driver_install(CONFIG_ESP_CONSOLE_UART_NUM, 256, 0, 0, NULL, 0));
    ESP_ERROR_CHECK(uart_param_config(CONFIG_ESP_CONSOLE_UART_NUM, &uart_config));

    /* Tell VFS to use UART driver */
    esp_vfs_dev_uart_use_driver(CONFIG_ESP_CONSOLE_UART_NUM);
}

/**
 * @brief App AT main
 * 
 */
void app_at_main(){
    init_uart();
    cat_init(&at, &desc, &iface, NULL);
    pthread_t at_thread;
    pthread_create(&at_thread, NULL, at_task, NULL);
}