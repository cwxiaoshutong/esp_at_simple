# ESP32 simple AT in pure c
A simple AT command based on libcAT [<https://github.com/marcinbor85/cAT>]

## Features
>+ All the features of libcAT

## How to use
### Download
Download directly or
  mkdir -p esp_at
  cd esp_at
  git clone git@github.com:cwxiaoshutong/esp_at_simple.git

### Build
Reference at [<https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/build-system.html>]
ESP-IDF required!
  make flash
  
## Current AT commands
>+AT
return OK
>+ATI
return chip info
>+AT+HELP
return registered commands

## How to use
Connect esp32 to computer
On linux run:
  picocom -b 115200 /dev/ttyUSB0
  
