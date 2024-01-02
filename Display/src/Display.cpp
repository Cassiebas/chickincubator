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
  if (!(x >= 0 && x < w && y >= 0 && y < h))
    return -1;
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

bool Display::Draw(std::vector<std::vector<bool>> buffer, uint8_t x, uint8_t y) {
  if (buffer.size() == 0)
    return false;
  for (unsigned int y_ = y; y_ < buffer.size() + y && y_ < buffer.size(); y_++) {
    for (unsigned int x_ = x; x_ < buffer.at(0).size() + x && x_ < buffer.at(0).size(); x_++) {
      framebuffer_put_pixel(fbp, (uint8_t)x_, (uint8_t)y_, buffer.at(y_ - y).at(x_ - x));
    }
  }
  ssd1306_i2c_display_update(oled, fbp);
}

int Display::draw_char(ssd1306_framebuffer_t *fbp, uint8_t x, uint8_t y, char character)
{
  uint8_t w = fbp->width;
  uint8_t h = fbp->height;

  // Check if the coordinates are within bounds
  if (x >= 0 && x < w && y >= 0 && y < h)
  {
    const std::vector<uint8_t> pixelData = font8x8.at(character);

    // Iterate over each row and column of the character
    for (uint8_t row = 0; row < 8; ++row)
    {
      for (uint8_t col = 0; col < 8; ++col)
      {
        framebuffer_put_pixel(fbp, col + x, row + y, pixelData[col] & (1 << row));
      }
    }

    return 0;
  }
  else
  {
    return -1; // Coordinates out of bounds
  }
}

// bool Display::Draw(std::vector<uint8_t> buffer, uint8_t x, uint8_t y) {
//   if (buffer.size() == 0)
//     return false;
//   for (unsigned int i_ = i; i_ < buffer.size() + i && i_ < buffer.size(); i_++) {
//       framebuffer_put_pixel(fbp, (uint8_t)x_, (uint8_t)y_, buffer.at(y_ - y).at(x_ - x));
//   }
//   ssd1306_i2c_display_update(oled, fbp);
// }

bool Display::Print(std::string message, uint8_t x, uint8_t y) {
  uint8_t x_ = x, y_ = y;
  for(char &c : message) {
    draw_char(fbp, x_ += 9, y_, c);
    if (x_ >= 128 - 9) {
      x_ = x;
      y_ += 9;
    }
  }
  ssd1306_i2c_display_update(oled, fbp);
}