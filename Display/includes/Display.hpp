#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <stdint.h>
#include <cstddef>
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

// ssd1306 has 1:1 correspondence between pixel to bit
ssd1306_framebuffer_t *ssd1306_framebuffer_create(
    uint8_t width, // width of the screen in pixels
    uint8_t height // height of the screen in pixels
);

ssd1306_i2c_t *ssd1306_i2c_open( // open the device for read/write
    const char *dev,             // name of the device such as /dev/i2c-1. cannot be NULL
    uint8_t daddr,               // I2C address of the device. valid values: 0 (default) or 0x3c or 0x3d
    uint8_t width,               // OLED display width. valid values: 0 (default) or 128
    uint8_t height               // OLED display height. valid values: 0 (default) or 32 or 64
);

void ssd1306_i2c_close(ssd1306_i2c_t *oled); // free object and close fd

class Display
{
  private:
    int fd;
    ssd1306_i2c_t *oled; // Member variable to store the ssd1306_i2c_t pointer

    const static uint8_t FONT_SIZE = 5;
    const static unsigned char font[][FONT_SIZE];

    static size_t ssd1306_i2c_internal_get_cmd_bytes(ssd1306_i2c_cmd_t cmd,
                                                    uint8_t *data, size_t dlen, uint8_t *cmdbuf, size_t cmd_buf_max);

    int ssd1306_i2c_run_cmd(ssd1306_i2c_t *oled,   // the ssd1306_i2c_t object
                            ssd1306_i2c_cmd_t cmd, // command to run on the display
                            uint8_t *data,         // optional command data, if any, otherwise use 0 or NULL
                            size_t dlen            // length of the data bytes. max is 6 per datasheet.
    );

    // initialize the display before use
    int ssd1306_i2c_display_initialize(ssd1306_i2c_t *oled);

  public:
    Display(ssd1306_i2c_t *oled);
    ~Display();

    // clear the display (calls ssd1306_i2c_display_update() internally)
    int ssd1306_i2c_display_clear(ssd1306_i2c_t *oled);

    // fill the display (calls ssd1306_i2c_display_update() internally)
    // int ssd1306_i2c_display_fill(ssd1306_i2c_t *oled);

    // update the display's GDDRAM with the framebuffer contents.
    // this function can be called in an idle loop or on a timer or on-demand
    int ssd1306_i2c_display_update(ssd1306_i2c_t *oled, const ssd1306_framebuffer_t *fbp);

    int ssd1306_framebuffer_put_pixel(ssd1306_framebuffer_t *fbp,
                                      uint8_t x, uint8_t y, bool color, uint8_t rotation_flag = 0);

    int ssd1306_framebuffer_clear(ssd1306_framebuffer_t *fbp);
};

#endif // DISPLAY_HPP