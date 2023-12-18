#include "../includes/Display.hpp" 
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
#include "Font.hpp"


Display::Display()
{
  const char *device_path = "/dev/i2c-1";
  const int i2c_address = 0x3C;
  fd = open(device_path, O_RDWR);
  if (fd < 0)
  {
    printf("Error opening the device driver\n");
  }
  // Set the I2C slave address
  if (ioctl(fd, I2C_SLAVE, i2c_address) < 0)
  {
    perror("Error setting I2C slave address");
    close(fd);
    return;
  }
}

Display::~Display() 
{
  close(fd);
}

uint8_t Display::oled_default_config(void)
{
  std::vector<uint8_t> data_buf;
  
  data_buf.push_back(SSD1306_COMM_CONTROL_BYTE);  // command control byte
  data_buf.push_back(SSD1306_COMM_DISPLAY_OFF);   // DISPLAY OFF  
  data_buf.push_back(SSD1306_COMM_DISP_NORM);     // Set Normal Display (default)
  data_buf.push_back(SSD1306_COMM_CLK_SET);       // SETDISPLAYCLOCKDIV
  data_buf.push_back(0x80);                       // the suggested ratio 0x80
  data_buf.push_back(SSD1306_COMM_MULTIPLEX);     // SSD1306_SETMULTIPLEX
  data_buf.push_back(32 - 1);                     // height is 32 or 64 (always -1)
  data_buf.push_back(SSD1306_COMM_VERT_OFFSET);   // SETDISPLAYOFFSET
  data_buf.push_back(0);                          // no offset
  data_buf.push_back(SSD1306_COMM_START_LINE);    // SETSTARTLINE
  data_buf.push_back(SSD1306_COMM_CHARGE_PUMP);   // CHARGEPUMP
  data_buf.push_back(0x14);                       // turn on charge pump
  data_buf.push_back(SSD1306_COMM_MEMORY_MODE | SSD1306_HORI_MODE);   // MEMORYMODE Register PLUS Mode
  data_buf.push_back(SSD1306_COMM_HORIZ_NORM);    // SEGREMAP  Mirror screen horizontally (A0)
  data_buf.push_back(SSD1306_COMM_SCAN_NORM);     // COMSCANDEC Rotate screen vertically (C0)
  data_buf.push_back(SSD1306_COMM_COM_PIN);       // HARDWARE PIN 
  data_buf.push_back(0x02);                       // 0x02for 32 lines 0x12 64 lines              
  data_buf.push_back(SSD1306_COMM_CONTRAST);      // SETCONTRAST
  data_buf.push_back(0x7f);                       // default contract value
  data_buf.push_back(SSD1306_COMM_PRECHARGE);     // SETPRECHARGE
  data_buf.push_back(0xf1);                       // default precharge value
  data_buf.push_back(SSD1306_COMM_DESELECT_LV);   // SETVCOMDETECT                
  data_buf.push_back(0x40);                       // default deselect value
  data_buf.push_back(SSD1306_COMM_RESUME_RAM);    // DISPLAYALLON_RESUME
  data_buf.push_back(SSD1306_COMM_DISP_NORM);     // NORMALDISPLAY
  data_buf.push_back(SSD1306_COMM_DISPLAY_ON);    // DISPLAY ON             
  //data_buf.push_back(SSD1306_COMM_DISABLE_SCROLL);// Stop scroll
  
  printf("Writing Line to Kernel \n");
  ssize_t result = write(fd, data_buf.data(), data_buf.size());
  if (result == -1) {
    perror("Error writing to kernel");
    return 1;  // Or another appropriate error code
  }
  return static_cast<uint8_t>(result);
}

uint8_t Display::oled_onoff(uint8_t onoff)
{
  std::vector<uint8_t> data_buf;
  data_buf.push_back(SSD1306_COMM_CONTROL_BYTE);
  if (onoff == 0)
    data_buf.push_back(SSD1306_COMM_DISPLAY_OFF);
  else
    data_buf.push_back(SSD1306_COMM_DISPLAY_ON);
  
  printf("Writing Line to Kernel \n");
  ssize_t result = write(fd, data_buf.data(), data_buf.size());
  if (result == -1) {
    perror("Error writing to kernel");
    return 1;  // Or another appropriate error code
  }
  return static_cast<uint8_t>(result);
}

// Set start and end column addresses (COL0 - COL127)
uint8_t Display::oled_set_col(uint8_t start, uint8_t end)
{
  std::vector<uint8_t> data_buf;

  data_buf.push_back(SSD1306_COMM_CONTROL_BYTE);
  data_buf.push_back(SSD1306_COMM_SET_COL_ADDR);
  data_buf.push_back(start);
  data_buf.push_back(end);
   
  printf("Writing Line to Kernel \n");
  ssize_t result = write(fd, data_buf.data(), data_buf.size());
  if (result == -1) {
    perror("Error writing to kernel");
    return 1;  // Or another appropriate error code
  }
  return static_cast<uint8_t>(result);
}

// Set the start and end pages (PAGE0-PAGE7)
uint8_t Display::oled_set_page(uint8_t start, uint8_t end)
{
  std::vector<uint8_t> data_buf;
  data_buf.push_back(SSD1306_COMM_CONTROL_BYTE);
  data_buf.push_back(SSD1306_COMM_SET_PAGE_ADDR);
  data_buf.push_back(start & 0x07);
  data_buf.push_back(end & 0x07);
  
  printf("Writing Line to Kernel \n");
  ssize_t result = write(fd, data_buf.data(), data_buf.size());
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

  return 0;  // Successfully updated the X position in the framebuffer
}

uint8_t Display::oled_set_Y(uint8_t y)
{
  if (y >= (max_lines / 8))
    return 1;

  global_y = y;

  return 0;  // Successfully updated the Y position in the framebuffer
}

// Set a pixel in the framebuffer
void Display::oled_draw_pixel(uint8_t col, uint8_t row, uint8_t pixel)
{
  oled_set_X(col);
  oled_set_Y(row);
  
  if (global_x >= max_columns || global_y >= max_lines)
    return;  // Check if the coordinates are within bounds

  // Calculate the page
  uint8_t global_page = global_y / NUM_ROWS_PER_PAGE;

  // Get the page the row exists at in the framebuffer
  uint8_t* page = frameBuffer[global_page];

  // Get the row within the page (0-7)
  const uint8_t page_row = global_y % NUM_ROWS_PER_PAGE;

  // Set the corresponding bit to set the pixel
  page[global_x] = (page[global_x] & ~(1 << page_row)) | (pixel << page_row);
}

void Display::update(void)
{
  oled_set_col(0, 127);
  oled_set_page(0, 3);
  oled_send_buffer(*frameBuffer, sizeof(frameBuffer));
}

// Send a data buffer GDDRAM
void Display::oled_send_buffer(const uint8_t* buffer, unsigned long length)
{
  uint8_t control_byte = SSD1306_DATA_CONTROL_BYTE;
  printf("Writing framebuffer to kernel\n");
  
  write(fd, &control_byte, 1);
  write(fd, buffer, length);
}

uint8_t Display::oled_horizontal_flip(uint8_t flip)
{
  std::vector<uint8_t> data_buf;
  data_buf.push_back(SSD1306_COMM_CONTROL_BYTE);
  if (flip == 0)
    data_buf.push_back(SSD1306_COMM_HORIZ_NORM);
  else
    data_buf.push_back(SSD1306_COMM_HORIZ_FLIP);

  printf("Writing Line to Kernel. Hori Flip \n");
  ssize_t result = write(fd, data_buf.data(), data_buf.size());
  if (result == -1) {
    perror("Error writing to kernel");
    return 1;
  }
  return static_cast<uint8_t>(result);
}

uint8_t Display::oled_display_flip(uint8_t flip)
{
  std::vector<uint8_t> data_buf;
  data_buf.push_back(SSD1306_COMM_CONTROL_BYTE);
  if (flip == 0)
    data_buf.push_back(SSD1306_COMM_DISP_NORM);
  else
    data_buf.push_back(SSD1306_COMM_DISP_INVERSE);
  
  printf("Writing Line to Kernel. Inverse \n");
  ssize_t result = write(fd, data_buf.data(), data_buf.size());
  if (result == -1) {
    perror("Error writing to kernel");
    return 1;
  }
  return static_cast<uint8_t>(result);
}

uint8_t Display::oled_write_line(uint8_t size, const char* ptr) {
  std::vector<uint8_t> data_buf;
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

  data_buf.push_back(SSD1306_DATA_CONTROL_BYTE);

  // font table range in ASCII table is from 0x20(space) to 0x7e(~)
  while (ptr[index] != 0 && i <= 1024) {
    if ((ptr[index] < ' ') || (ptr[index] > '~'))
      return 1;

    const uint8_t* font_ptr = &font_table[(ptr[index] - 0x20) * font_table_width];
    for (uint8_t j = 0; j < font_table_width; j++) {
      data_buf.push_back(font_ptr[j]);
      if (i > 1024)
        return 1;
    }
    // insert 1 col space for small font size)
    if (size == SSD1306_FONT_SMALL)
      data_buf.push_back(0x00);
    index++;
  }

  printf("Writing Line to Kernel. Write Line \n");
  ssize_t result = write(fd, data_buf.data(), data_buf.size());
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

// uint8_t Display::oled_clear_line(uint8_t row)
// {
//   std::vector<uint8_t> data_buf;

//   uint8_t i =0;
//   if (row >= max_lines)
//     return 1;
    
//   // oled_set_X(0);
//   // oled_set_Y(row);

//   data_buf.push_back(SSD1306_DATA_CONTROL_BYTE);
//   for (i = 0; i <= max_columns; i++)
//     data_buf.push_back(0x00);
      
//   printf("Writing Line to Kernel. Clean Line \n");
//   ssize_t result = write(fd, data_buf.data(), 1 + max_columns);
//   if (result == -1) {
//     perror("Error writing to kernel");
//     return 1;  // Or another appropriate error code
//   }
//   return static_cast<uint8_t>(result);
// }

// uint8_t Display::oled_set_line(uint8_t row)
// {
//   std::vector<uint8_t> data_buf;

//   uint8_t i =0;
//   if (row >= max_lines)
//     return 1;
    
//   // oled_set_X(0);
//   // oled_set_Y(row);
//   data_buf.push_back(SSD1306_DATA_CONTROL_BYTE);
//   for (i = 0; i <= max_columns; i++)
//     data_buf.push_back(0xFF);
      
//   printf("Writing Line to Kernel. Set Line\n");
//   ssize_t result = write(fd, data_buf.data(), 1 + max_columns);
//   if (result == -1) {
//     perror("Error writing to kernel");
//     return 1;  // Or another appropriate error code
//   }
//   return static_cast<uint8_t>(result);
// }

uint8_t Display::oled_clear_line(uint8_t row)
{
  if (row >= max_lines)
    return 1;

  // Get the page the row exists at in the framebuffer
  uint8_t* page = frameBuffer[row];

  // Clear the entire line
  for (uint8_t i = 0; i < max_columns; ++i) {
    page[i] = 0x00;
  }

  update();

  return 0;
}

uint8_t Display::oled_set_line(uint8_t row)
{
  if (row >= max_lines)
    return 1;

  // Get the page the row exists at in the framebuffer
  uint8_t* page = frameBuffer[row];

  // Set the entire line
  for (uint8_t i = 0; i < max_columns; ++i) {
    page[i] = 0xFF;
  }

  // Optionally update the display
  update();

  return 0;
}

uint8_t Display::oled_clear_screen()
{
  for (uint8_t row = 0; row < max_lines; ++row) {
    oled_clear_line(row);
  }

  return 0;
}

uint8_t Display::oled_white_screen()
{
  for (uint8_t row = 0; row < max_lines; ++row) {
    oled_set_line(row);
  }

  return 0;
}