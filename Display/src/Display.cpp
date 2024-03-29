#include "Display.hpp"
#include "Font.hpp"


#include <stdio.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/uio.h>
#include <cstring>

#include <iostream>

Display::Display():
  //filename("/dev/i2c-1"),
  filename("/proc/SSD1306"),
  i2c_address(0x3C)
{
  oled = OpenSSD1306(filename, i2c_address, 128, 32);
  if (InitializeDisplay(oled) < 0)
  {
    printf("ERROR: Failed to initialize the display. Check if it is connected !\n");
    CloseSSD1306(oled);
  }
  if (oled) {
    //Create framebuffer to send data with
    fbp = CreateBuffer(oled->width, oled->height);
    // CloseSSD1306(oled);
  }
}

Display::~Display()
{

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
  const uint8_t w = fbp->width;
  const uint8_t h = fbp->height;

  // based on the page arrangement in GDDRAM as per the datasheet
  if (!(x < w && y < h))
    return -1;

  // Calculate the index in the buffer based on the page arrangement in GDDRAM
  const int bufferIndex = (int)(x + (y / 8) * w);

  if (pixelState)
  {
    fbp->buffer[bufferIndex] |= (uint8_t)(1 << (y & 7));
  }
  else
  {
    fbp->buffer[bufferIndex] &= (uint8_t)~(1 << (y & 7)); //0b11101111
  }
  return 0;
}

int Display::Clear()
{
  std::fill(fbp->buffer, fbp->buffer + fbp->len, 0);
  return 0;
}

int Display::Draw(std::vector<std::vector<bool>> buffer, unsigned int x, unsigned int y) {
  if (buffer.size() == 0) {
    // std::cout << "y size was 0!";
    return -1;
  }
  if (buffer.at(0).size() == 0) {
    // std::cout << "x size was 0!\n";
    return -1;
  }
  for (unsigned int y_ = y; y_ < buffer.size() + y; y_++) {
    for (unsigned int x_ = x; x_ < buffer.at(0).size() + x; x_++) {
      PutPixel((uint8_t)x_, (uint8_t)y_, buffer.at(y_ - y).at(x_ - x));
    }
  }
  return 0;
}

int Display::DrawChar(uint8_t x, uint8_t y, std::string character)
{
  const uint8_t w = fbp->width;
  const uint8_t h = fbp->height;

  // Check if the coordinates are within bounds
  if (x < w && y < h)
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

// Function to determine the number of bytes in a UTF-8 character based on its first byte
int Display::utf8BytesCount(char firstByte) {
  if ((firstByte & 0b10000000) == 0) {
    return 1;
  } else if ((firstByte & 0b11100000) == 0b11000000) {
    return 2;
  } else if ((firstByte & 0b11110000) == 0b11100000) {
    return 3;
  } else if ((firstByte & 0b11111000) == 0b11110000) {
    return 4;
  }
  return 0;  // Invalid UTF-8 sequence
}

int Display::Print(std::string message, uint8_t x, uint8_t y) {
  uint8_t x_ = x, y_ = y;
  int charLength = utf8BytesCount(message[0]);
  for(std::string::size_type i = 0; i < message.length(); i += charLength) {
    int charLength = utf8BytesCount(message[i]);
    if (charLength == 0) {
      continue;
    }
    std::string character = message.substr(i, charLength);
    DrawChar(x_, y_, character);
    x_ += 9;
    if (x_ >= 128 - 9) {
      x_ = x;
      y_ += 9;
    }
  }
  return 0;
}

int Display::Update() {
  int result;
  result = UpdateDisplay(oled, fbp);
  return result;
}

int Display::DrawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
  // Handle vertical line
  if (x0 == x1) {
    const uint8_t start_y = (y0 < y1) ? y0 : y1;
    const int8_t end_y = (y0 < y1) ? y1 : y0;
    for (uint8_t y = start_y; y <= end_y; y++) {
      PutPixel(x0, y, true);
    }
    return 0;
  }

  // Handle horizontal line
  if (y0 == y1) {
    const uint8_t start_x = (x0 < x1) ? x0 : x1;
    const uint8_t end_x = (x0 < x1) ? x1 : x0;
    for (uint8_t x = start_x; x <= end_x; x++) {
      PutPixel(x, y0, true);
    }
    return 0;
  }

  // For non-vertical and non-horizontal lines, return -1
  return -1;
}