#ifndef SSD1306_H
#define SSD1306_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include "Commands.hpp"

typedef struct ssd1306_font_ ssd1306_font_t;

typedef struct
{
  int fd;
  char *dev;                // device name. a copy is made.
  uint8_t addr;             // default 0x3c
  uint8_t width;            // default 128
  uint8_t height;           // default 64
  uint8_t *gddram_buffer;   // buffer for GDDRAM size (height x width/8) + 1 bytes
  size_t gddram_buffer_len; // value = (height x width / 8) + 1
} ssd1306_i2c_t;

typedef struct
{
  uint8_t width;        // width of the framebuffer
  uint8_t height;       // height of the framebuffer
  uint8_t *buffer;      // buffer pointer
  size_t len;           // length of the buffer
  ssd1306_font_t *font; // pointer to an opaque font library implementation - default is freetype
} ssd1306_framebuffer_t;

#ifdef __cplusplus
extern "C" {
#endif

    // ssd1306 has 1:1 correspondence between pixel to bit
    ssd1306_framebuffer_t *CreateBuffer(
        uint8_t width, // width of the screen in pixels
        uint8_t height // height of the screen in pixels
    );

    ssd1306_i2c_t *OpenSSD1306(       // open the device for read/write
        const char *dev,              // name of the device such as /dev/i2c-1. cannot be NULL
        uint8_t daddr,                // I2C address of the device. valid values: 0 (default) or 0x3c or 0x3d
        uint8_t width,                // OLED display width. valid values: 0 (default) or 128
        uint8_t height                // OLED display height. valid values: 0 (default) or 32 or 64
    );

    void CloseSSD1306(ssd1306_i2c_t *oled); // free object and close fd

    size_t GetCommand(ssd1306_i2c_cmd_t cmd, uint8_t *data, size_t dlen, uint8_t *cmdbuf, size_t cmd_buf_max);

    int RunCommand(ssd1306_i2c_t *oled,   // the ssd1306_i2c_t object
                            ssd1306_i2c_cmd_t cmd, // command to run on the display
                            uint8_t *data,         // optional command data, if any, otherwise use 0 or NULL
                            size_t dlen            // length of the data bytes. max is 6 per datasheet.
    );

    // clear the display (calls ssd1306_i2c_display_update() internally)
    int ClearDisplay(ssd1306_i2c_t *oled);

    // Update the display by sending the framebuffer
    int UpdateDisplay(ssd1306_i2c_t *oled, const ssd1306_framebuffer_t *fbp);

    // initialize the display before use
    int InitializeDisplay(ssd1306_i2c_t *oled);

#ifdef __cplusplus
}
#endif

#endif