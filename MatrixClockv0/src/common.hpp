#ifndef COMMON_HPP
#define COMMON_HPP
//240x135
#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library
#define TFT_GREY 0x5AEB
#define lightblue 0x01E9
#define darkred 0xA041
#define blue 0x5D9B
#define orange 0xFB60
#define purple 0xFB9B

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library
#endif