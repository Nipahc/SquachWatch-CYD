// SquachWatch-CYD — TFT_eSPI config for the Hosyond/LCDWIKI E32R32P
// (3.2 inch, 240x320 ST7789P3, XPT2046 resistive touch).
//
// This board is not the 2.8-inch ESP32-2432S028R despite sharing the CYD
// display pins. Its XPT2046 is on the display SPI bus with CS on GPIO33,
// and its backlight is GPIO27. These values have been confirmed on E32R32P
// hardware by the Gume project; they also agree with the vendor family pin
// allocation. The XPT2046 IRQ on GPIO36 is intentionally unused: the board's
// IRQ is unreliable, so main.cpp detects contact from pressure instead.
#pragma once

#define USER_SETUP_INFO "SquachWatch-CYD / Hosyond E32R32P 3.2 inch / ST7789P3"
#define ST7789_DRIVER

#define TFT_WIDTH   240
#define TFT_HEIGHT  320
#define TFT_ROTATION 1

// Keep display/touch on HSPI. The SD slot uses the ESP32's other SPI engine
// on 18/19/23, so attaching both sets of pins to one controller would corrupt
// shared-bus touch reads after SD initialisation.
#define USE_HSPI_PORT
#define TFT_MISO  12
#define TFT_MOSI  13
#define TFT_SCLK  14
#define TFT_CS    15
#define TFT_DC     2
#define TFT_RST   -1
#define TFT_BL    27

// XPT2046 shares TFT_MISO/TFT_MOSI/TFT_SCLK.
#define TOUCH_CS  33
// Measured on this physical panel: idle noise is 12-21, while deliberate
// presses are well above 1000.  A 100-count gate keeps a wide noise margin
// while making the resistive overlay less demanding than the generic 350.
#define TOUCH_PRESSURE_THRESHOLD 100

#define TFT_BACKLIGHT_ON HIGH

#ifndef SPI_FREQUENCY
#define SPI_FREQUENCY         40000000
#endif
#define SPI_READ_FREQUENCY    20000000
#define SPI_TOUCH_FREQUENCY    2500000

#define LOAD_GLCD
#define LOAD_FONT2

// Confirmed on physical E32R32P hardware: BGR order, normal polarity.
#define TFT_INVERSION_OFF
#define TFT_RGB_ORDER TFT_BGR
