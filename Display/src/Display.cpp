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
  oled = OpenSSD1306(filename, i2c_address, 128, 32);
  if (InitializeDisplay(oled) < 0)
  {
    printf("ERROR: Failed to initialize the display. Check if it is connected !\n");
    CloseSSD1306(oled);
  }
  //Create framebuffer to send data with
  fbp = CreateBuffer(oled->width, oled->height);
  sleep(3);
}

Display::~Display()
{
  if (oled)
    CloseSSD1306(oled);
}

ssd1306_i2c_t* Display::GetOledData()
{
  return oled;
}

ssd1306_framebuffer_t* Display::GetBufferData()
{
  return fbp;
}

int Display::PutPixel(uint8_t x, uint8_t y, bool pixelState)
{
  uint8_t w = fbp->width;
  uint8_t h = fbp->height;
  // based on the page arrangement in GDDRAM as per the datasheet
  if (!(x >= 0 && x < w && y >= 0 && y < h))
    return -1;
  if (pixelState)
  {
    fbp->buffer[x + (y / 8) * w] |= (1 << (y & 7));
  }
  else
  {
    fbp->buffer[x + (y / 8) * w] &= ~(1 << (y & 7));
  }
  return 0;
}

int Display::Clear()
{
  std::fill(fbp->buffer, fbp->buffer + fbp->len, 0);
  return 0;
}

int Display::Draw(std::vector<std::vector<bool>> buffer, uint8_t x, uint8_t y) {
  if (buffer.size() == 0)
    return -1;
  for (unsigned int y_ = y; y_ < buffer.size() + y && y_ < buffer.size(); y_++) {
    for (unsigned int x_ = x; x_ < buffer.at(0).size() + x && x_ < buffer.at(0).size(); x_++) {
      PutPixel((uint8_t)x_, (uint8_t)y_, buffer.at(y_ - y).at(x_ - x));
    }
  }
  return 0;
}

int Display::DrawChar(uint8_t x, uint8_t y, char character)
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
        PutPixel(col + x, row + y, pixelData[col] & (1 << row));
      }
    }
  }
  else
  {
    return -1; // Coordinates out of bounds
  }
  
  return 0;
}

int Display::Print(std::string message, uint8_t x, uint8_t y) {
  uint8_t x_ = x, y_ = y;
  for(char &c : message) {
    DrawChar(x_, y_, c);
    x_ += 9;
    if (x_ >= 128 - 9) {
      x_ = x;
      y_ += 9;
    }
  }
  return 0;
}

int Display::Update() {
  return UpdateDisplay(oled, fbp);
}