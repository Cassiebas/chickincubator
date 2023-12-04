#include "../includes/Display.hpp" 
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <cstring>
#include "Font.hpp"


Display::Display()
{
  fd = open("/dev/ssd1306_i2c", O_RDWR);
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
  
  return write(fd, data_buf, 2);
}

uint8_t Display::oled_set_col(uint8_t start, uint8_t end)
{
  data_buf[0] = SSD1306_COMM_CONTROL_BYTE;
  data_buf[1] = SSD1306_COMM_SET_COL_ADDR;
  data_buf[2] = start;
  data_buf[3] = end;
  
  return write(fd, data_buf, 4);
}

uint8_t Display::oled_set_page(uint8_t start, uint8_t end)
{
  data_buf[0] = SSD1306_COMM_CONTROL_BYTE;
  data_buf[1] = SSD1306_COMM_SET_PAGE_ADDR;
  data_buf[2] = start;
  data_buf[3] = end;
  
  return write(fd, data_buf, 4);
}

uint8_t Display::oled_set_X(uint8_t x)
{
  if (x >= max_columns)
    return 1;

  global_x = x;
  
  data_buf[0] = SSD1306_COMM_CONTROL_BYTE;
  data_buf[1] = SSD1306_COMM_LOW_COLUMN | (x & 0x0f);
  data_buf[2] = SSD1306_COMM_HIGH_COLUMN | ((x >> 4) & 0x0f);
  
  return write(fd, data_buf, 3);
}

uint8_t Display::oled_set_Y(uint8_t y)
{
  if (y >= (max_lines / 8))
    return 1;

  global_y = y;
  
  data_buf[0] = SSD1306_COMM_CONTROL_BYTE;
  data_buf[1] = SSD1306_COMM_PAGE_NUMBER | (y & 0x0f);

  return write(fd, data_buf, 2);
}

uint8_t Display::oled_write_line(uint8_t size, char* ptr)
{
  uint16_t i = 0;
  uint16_t index = 0;
  uint8_t* font_table = 0;
  uint8_t font_table_width = 0;
  
  if (ptr == 0)
    return 1;
  
  if (size == SSD1306_FONT_SMALL) // 5x7
  {
    font_table = (uint8_t*)font5x7;
    font_table_width = 5;
  }
  else if (size == SSD1306_FONT_NORMAL) // 8x8
  {
    font_table = (uint8_t*)font8x8;
    font_table_width = 8;
  }
  else
    return 1;
  
  data_buf[i++] = SSD1306_DATA_CONTROL_BYTE;
  
  // font table range in ascii table is from 0x20(space) to 0x7e(~)
  while (ptr[index] != 0 && i <= 1024)
  {
    if ((ptr[index] < ' ') || (ptr[index] > '~'))
      return 1;

    uint8_t* font_ptr = &font_table[(ptr[index] - 0x20) * font_table_width];
    uint8_t j = 0;
    for (j = 0; j < font_table_width; j++)
    {
      data_buf[i++] = font_ptr[j];
      if (i > 1024)
        return 1;
    }
    // insert 1 col space for small font size)
    if (size == SSD1306_FONT_SMALL)
      data_buf[i++] = 0x00;
    index++;
  }
  
  return write(fd, data_buf, i);
}

uint8_t Display::oled_write_string(uint8_t size, char* ptr)
{
  uint8_t rc = 0;
  
  if (ptr == 0)
    return 1;
  
  char* line = 0;
  char* cr = 0;
  char buf[20];
  
  line = ptr;
  do {
    memset(buf, 0, 20);
    cr = strstr(line, "\\n");
    if (cr != NULL)
    {
      strncpy(buf, line, cr - line);
    }
    else
    {
      strcpy(buf, line);
    }
    
    // set cursor position
    oled_set_X(global_x);
    oled_set_Y(global_y);
    rc += oled_write_line(size, buf);
    
    if (cr != NULL)
    {
      line = &cr[2];
      global_x = 0;
      global_y++;
      if (global_y >= (max_lines / 8))
        global_y = 0;
    }
    else
      line = NULL;
              
  }while (line != NULL);
  
  return rc;
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
      
  return write(fd, data_buf, 1 + max_columns);
}

uint8_t Display::oled_clear_screen()
{
  uint8_t rc = 0;
  uint8_t i;
  
  for (i = 0; i < (max_lines / 8); i++)
  {
    rc += oled_clear_line(i);
  }
  
  return rc;
}

// void Display::PrintChar(unsigned char c) {
//   uint8_t data_byte;
//   uint8_t temp = 0;
//   /*
//   ** If the character is greater than segment len or we got new line charcter
//   ** then move the cursor to the new line
//   */ 
//   if( (( CursorPos + FONT_SIZE ) >= SSD1306_MAX_SEG ) || ( c == '\n' ))
//   {
//     //Placeholder for next line function
//   }
//   // print charcters other than new line
//   if( c != '\n' )
//   {
//     /*
//     ** In our font array (font), space starts in 0th index.
//     ** But in ASCII table, Space starts from 32 (0x20).
//     ** So we need to match the ASCII table with our font table.
//     ** We can subtract 32 (0x20) in order to match with our font table.
//     */
//     c -= 0x20;  //or c -= ' ';
//     do
//     {
//       data_byte= font[c][temp]; // Get the data to be displayed from LookUptable
//       Write(false, data_byte);  // write data to the OLED
//       CursorPos++;
      
//       temp++;
      
//     } while ( temp < FONT_SIZE);
//     Write(false, 0x00);         //Display the data
//     CursorPos++;
//   }
// }

// void Display::PrintString(unsigned char *str) {

//   while(*str)
//   {
//     PrintChar(*str++);
//   }
// }

// void Display::Fill(unsigned char data) {
//   unsigned int total = 128 * 7; // 4 pages x 128 segments x 4 bits of data
//   unsigned int i = 0;

//   // Fill the Display
//   for (i = 0; i < total; i++)
//   {
//     Write(false, data);
//   }
// }