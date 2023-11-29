#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <stdint.h>

class Display
{
  private:
    int Init();
    int Write(bool is_cmd, unsigned char data);
    void Fill(unsigned char data);

    int file;
    uint8_t CursorPos;
    const static uint8_t FONT_SIZE = 5;
    const static uint8_t SSD1306_MAX_SEG = 128;
    const static uint8_t SSD1306_MAX_LINE = 3;
    const static unsigned char font[][FONT_SIZE];

  public:
    Display();
    ~Display();
    void PrintChar(unsigned char c);
    void PrintString(unsigned char *str);
};

#endif // DISPLAY_HPP