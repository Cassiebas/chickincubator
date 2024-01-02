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
    int fd;
    ssd1306_i2c_t* oled;
    ssd1306_framebuffer_t *fbp;

    const static uint8_t FONT_SIZE = 5;
    const static unsigned char font[][FONT_SIZE];

  public:
    Display();
    ~Display();
    bool Draw(std::vector<std::vector<bool>> buffer, uint8_t x = 0, uint8_t y = 0);
    void Print(std::string message, uint8_t x = 0, uint8_t y = 0);
    int draw_char(ssd1306_framebuffer_t *fbp, uint8_t x, uint8_t y, char character);
    // bool Print(std::string message, uint8_t x = 0, uint8_t y = 0);
    // fill the display (calls ssd1306_i2c_display_update() internally)
    // int ssd1306_i2c_display_fill(ssd1306_i2c_t *oled);

    int framebuffer_put_pixel(ssd1306_framebuffer_t *fbp,
                                      uint8_t x, uint8_t y, bool color, uint8_t rotation_flag = 0);

    int framebuffer_clear(ssd1306_framebuffer_t *fbp);

    ssd1306_i2c_t* get_oled_data();
    ssd1306_framebuffer_t* get_framebuffer_data();
};

#endif // DISPLAY_HPP