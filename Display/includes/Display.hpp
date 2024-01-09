#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <stdint.h>
#include <cstddef>
#include <vector>
#include <string>

#include "SSD1306.h"

class Display
{
  private:
    const char *filename;
    const uint8_t i2c_address;
    int fd;
    ssd1306_i2c_t* oled;
    ssd1306_framebuffer_t *fbp;

    const static uint8_t FONT_SIZE = 5;
    const static unsigned char font[][FONT_SIZE];

  public:
    Display();
    ~Display();
    int Draw(std::vector<std::vector<bool>> buffer, uint8_t x = 0, uint8_t y = 0);
    int Print(std::string message, uint8_t x = 0, uint8_t y = 0);
    int DrawChar(uint8_t x, uint8_t y, char character);
    int DrawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
    int Update();

    int PutPixel(uint8_t x, uint8_t y, bool pixelState);

    int Clear();

    ssd1306_i2c_t* GetOledData();
    ssd1306_framebuffer_t* GetBufferData();
};

#endif // DISPLAY_HPP