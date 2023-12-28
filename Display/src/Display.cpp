#include "Display.hpp"
#include "Font.hpp"


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/uio.h>
#include <unistd.h>
#include <vector>
#include <cstring>
#include <string>

Display::Display()
{
  const char *filename = "/dev/i2c-1";
  const int i2c_address = 0x3C;
  oled = ssd1306_i2c_open(filename, i2c_address, 128, 32);
  if (ssd1306_i2c_display_initialize(oled) < 0)
  {
    printf("ERROR: Failed to initialize the display. Check if it is connected !\n");
    ssd1306_i2c_close(oled);
  }
  //Create framebuffer to send data with
  fbp = ssd1306_framebuffer_create(oled->width, oled->height);
  sleep(3);
}

Display::~Display()
{
  if (oled)
    ssd1306_i2c_close(oled);
}

ssd1306_i2c_t* Display::get_oled_data()
{
  return oled;
}

ssd1306_framebuffer_t* Display::get_framebuffer_data()
{
  return fbp;
}

int Display::framebuffer_put_pixel(ssd1306_framebuffer_t *fbp,
                                  uint8_t x, uint8_t y, bool color, uint8_t rotation_flag)
{
  uint8_t w = fbp->width;
  uint8_t h = fbp->height;
  // based on the page arrangement in GDDRAM as per the datasheet
  if (x >= 0 && x < w && y >= 0 && y < h)
  {
    switch (rotation_flag)
    {
      uint8_t tmp;
    case 1: // 90deg rotation
      tmp = x;
      x = y;
      y = tmp; // swap x&y
      x = w - x - 1;
      break;
    case 2: // 180deg rotation
      x = w - x - 1;
      y = h - y - 1;
      break;
    case 3: // -90deg rotation
      tmp = x;
      x = y;
      y = tmp; // swap x&y
      y = h - y - 1;
      break;
    default:
      break; // no rotation
    }
  }
  else
  {
    return -1;
  }
  if (color)
  {
    fbp->buffer[x + (y / 8) * w] |= (1 << (y & 7));
  }
  else
  {
    fbp->buffer[x + (y / 8) * w] &= ~(1 << (y & 7));
  }
  return 0;
}

int Display::framebuffer_clear(ssd1306_framebuffer_t *fbp)
{
  memset(fbp->buffer, 0, fbp->len);
  return 0;
}