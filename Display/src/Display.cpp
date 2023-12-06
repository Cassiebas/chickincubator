#include "../includes/Display.hpp" 
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>
#include <cstring>
#include <string>
#include "Font.hpp"


Display::Display()
{
  fd = open("/proc/SSD1306", O_RDWR);
  if (fd < 0)
  {
    printf("Error opening the device driver\n");
  }
}

Display::~Display() 
{
  close(fd);
}

uint8_t Display::oled_onoff(uint8_t onoff)
{
  data_buf[0] = SSD1306_COMM_CONTROL_BYTE;
  if (onoff == 0)
    data_buf[1] = SSD1306_COMM_DISPLAY_OFF;
  else
    data_buf[1] = SSD1306_COMM_DISPLAY_ON;
  
  printf("Writing Line to Kernel \n");
  ssize_t result = write(fd, data_buf, 2);
  if (result == -1) {
    perror("Error writing to kernel");
    return 1;  // Or another appropriate error code
  }
  return static_cast<uint8_t>(result);
}

uint8_t Display::oled_set_col(uint8_t start, uint8_t end)
{
  data_buf[0] = SSD1306_COMM_CONTROL_BYTE;
  data_buf[1] = SSD1306_COMM_SET_COL_ADDR;
  data_buf[2] = start;
  data_buf[3] = end;
  
  printf("Writing Line to Kernel \n");
  ssize_t result = write(fd, data_buf, 4);
  if (result == -1) {
    perror("Error writing to kernel");
    return 1;  // Or another appropriate error code
  }
  return static_cast<uint8_t>(result);
}

uint8_t Display::oled_set_page(uint8_t start, uint8_t end)
{
  data_buf[0] = SSD1306_COMM_CONTROL_BYTE;
  data_buf[1] = SSD1306_COMM_SET_PAGE_ADDR;
  data_buf[2] = start;
  data_buf[3] = end;
  
  printf("Writing Line to Kernel \n");
  ssize_t result = write(fd, data_buf, 4);
  if (result == -1) {
    perror("Error writing to kernel");
    return 1;  // Or another appropriate error code
  }
  return static_cast<uint8_t>(result);
}

uint8_t Display::oled_set_X(uint8_t x)
{
  if (x >= max_columns)
    return 1;

  global_x = x;
  
  data_buf[0] = SSD1306_COMM_CONTROL_BYTE;
  data_buf[1] = SSD1306_COMM_LOW_COLUMN | (x & 0x0f);
  data_buf[2] = SSD1306_COMM_HIGH_COLUMN | ((x >> 4) & 0x0f);
  
  printf("Writing Line to Kernel \n");
  ssize_t result = write(fd, data_buf, 3);
  if (result == -1) {
    perror("Error writing to kernel");
    return 1;  // Or another appropriate error code
  }
  return static_cast<uint8_t>(result);
}

uint8_t Display::oled_set_Y(uint8_t y)
{
  if (y >= (max_lines / 8))
    return 1;

  global_y = y;
  
  data_buf[0] = SSD1306_COMM_CONTROL_BYTE;
  data_buf[1] = SSD1306_COMM_PAGE_NUMBER | (y & 0x0f);

  printf("Writing Line to Kernel \n");
  ssize_t result = write(fd, data_buf, 2);
  if (result == -1) {
    perror("Error writing to kernel");
    return 1;  // Or another appropriate error code
  }
  return static_cast<uint8_t>(result);
}

uint8_t Display::oled_write_line(uint8_t size, const char* ptr) {
  uint16_t i = 0;
  uint16_t index = 0;
  const uint8_t* font_table = nullptr;
  uint8_t font_table_width = 0;

  if (ptr == nullptr)
    return 1;

  if (size == SSD1306_FONT_SMALL) { // 5x7
    font_table = font5x7;
    font_table_width = 5;
  } else if (size == SSD1306_FONT_NORMAL) { // 8x8
    font_table = font8x8;
    font_table_width = 8;
  } else
    return 1;

  data_buf[i] = SSD1306_DATA_CONTROL_BYTE;

  // font table range in ASCII table is from 0x20(space) to 0x7e(~)
  while (ptr[index] != 0 && i <= MAX_BUFFER_SIZE) {
    if ((ptr[index] < ' ') || (ptr[index] > '~'))
      return 1;

    const uint8_t* font_ptr = &font_table[(ptr[index] - 0x20) * font_table_width];
    for (uint8_t j = 0; j < font_table_width; j++) {
      data_buf[i++] = font_ptr[j];
      if (i > MAX_BUFFER_SIZE)
        return 1;
    }
    // insert 1 col space for small font size)
    if (size == SSD1306_FONT_SMALL)
      data_buf[i++] = 0x00;
    index++;
  }

  printf("Writing Line to Kernel \n");
  ssize_t result = write(fd, data_buf, i);
  if (result == -1) {
    perror("Error writing to kernel");
    return 1;  // Or another appropriate error code
  }
  return static_cast<uint8_t>(result);
}

uint8_t Display::oled_write_string(uint8_t size, const char* ptr) {
  uint8_t returnCode = 0;

  if (ptr == nullptr)
    return 1;

  const char* line = ptr;
  do {
    std::vector<char> buf(20, 0);
    char *buffArray = buf.data();
    // char buf[20];
    // std::memset(buf, 0, 20);
    std::size_t pos = std::string(line).find('\n');
    const char* newlinePosition = (pos != std::string::npos) ? line + pos : nullptr;
    if (newlinePosition != nullptr) {
      std::size_t length = newlinePosition - line;
      std::strncpy(buffArray, line, length);
      buffArray[length] = '\0';
    } else {
      std::strcpy(buffArray, line);
    }

    // set cursor position
    oled_set_X(global_x);
    oled_set_Y(global_y);
    returnCode += oled_write_line(size, buffArray);

    if (newlinePosition != nullptr) {
      line = &newlinePosition[2];
      global_x = 0;
      global_y++;
      if (global_y >= (max_lines / 8))
        global_y = 0;
    } else {
      line = nullptr;
    }
  } while (line != nullptr);

  return returnCode;
}

uint8_t Display::oled_clear_line(uint8_t row)
{
  uint8_t i;
  if (row >= (max_lines / 8))
    return 1;
    
  oled_set_X(0);
  oled_set_Y(row);
  data_buf[0] = SSD1306_DATA_CONTROL_BYTE;
  for (i = 0; i < max_columns; i++)
    data_buf[i+1] = 0x00;
      
  printf("Writing Line to Kernel \n");
  ssize_t result = write(fd, data_buf, 1 + max_columns);
  if (result == -1) {
    perror("Error writing to kernel");
    return 1;  // Or another appropriate error code
  }
  return static_cast<uint8_t>(result);
}

uint8_t Display::oled_clear_screen() {
  // Set the column range to cover the entire display
  oled_set_X(0);
  oled_set_X(max_columns - 1);

  // Set the page range to cover the entire display
  oled_set_page(0, 3);

  // Clear each pixel by sending 0x00 to the display
  uint8_t clear_data[] = {SSD1306_COMM_CONTROL_BYTE, 0x00};

  for (uint8_t page = 0; page < MAX_PAGES; ++page) {
    for (uint8_t col = 0; col < max_columns; ++col) {
      ssize_t result = write(fd, clear_data, 2);
      if (result == -1) {
        perror("Error writing to kernel");
        return 1;  // Or another appropriate error code
      }
    }
  }

  return 0; // Successfully cleared the display
}