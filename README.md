# ESP32 simple AT in pure c
[中文](#esp32at)
A simple AT command based on libcAT [<https://github.com/marcinbor85/cAT>]

## Features
>+ All the features of libcAT

## How to use
### Download
Download directly or
```
  mkdir -p esp_at
  cd esp_at
  git clone git@github.com:cwxiaoshutong/esp_at_simple.git
```

### Build
Reference at [<https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/build-system.html>]
ESP-IDF required!
```
  make flash
```
  
## Current AT commands
> + AT
<br>return OK
> + ATI
<br>return chip info
> + AT+HELP
<br>return registered commands

## How to use
Connect esp32 to computer
On linux run:
```
  picocom -b 115200 /dev/ttyUSB0
```
  
## test
```
~$ picocom -b 115200 /dev/ttyUSB0
Terminal ready

at

OK
ati
IDF Version:v4.3.1-dirty
Chip info:
	model:ESP32C3
	cores:1
	feature:/802.11bgn/BLE/External-Flash:4 MB
	revision number:3

OK
at+help

AT

ATI

AT+HELP

OK
```

## About
This is a try,and all the commands can be customized.

# esp32at
# 一个简单的ESP32 AT
基于libcAT  [<https://github.com/marcinbor85/cAT>]

## 下载 & 编译
需要ESP-IDF (如何安装[<https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/get-started/index.html#get-started-how-to-get-esp-idf>])
下载
```
  mkdir -p esp_at
  cd esp_at
  git clone git@github.com:cwxiaoshutong/esp_at_simple.git
  make flash
```

## 如何使用
环境:Ubuntu 20.04
需要picocom
```
sudo apt install picocom
```

连接
```
picocom -b 115200 /dev/ttyUSB0
```

简单测试
[AT](#test)

## 此项目的意义
> 个人学习
> <br>完全可定制的指令集
> <br>源码全部可见（无.a预编译）

