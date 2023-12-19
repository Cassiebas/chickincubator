#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <stdint.h>
#include <cstddef>

#define SSD1306_I2C_ADDR 0x3c

#define SSD1306_COMM_CONTROL_BYTE 0x00
#define SSD1306_DATA_CONTROL_BYTE 0x40

#define SSD1306_COMM_DISPLAY_OFF 0xae
#define SSD1306_COMM_DISPLAY_ON 0xaf
#define SSD1306_COMM_HORIZ_NORM 0xa0
#define SSD1306_COMM_HORIZ_FLIP 0xa1
#define SSD1306_COMM_RESUME_RAM 0xa4
#define SSD1306_COMM_IGNORE_RAM 0xa5
#define SSD1306_COMM_DISP_NORM 0xa6
#define SSD1306_COMM_DISP_INVERSE 0xa7
#define SSD1306_COMM_MULTIPLEX 0xa8
#define SSD1306_COMM_VERT_OFFSET 0xd3
#define SSD1306_COMM_CLK_SET 0xd5
#define SSD1306_COMM_PRECHARGE 0xd9
#define SSD1306_COMM_COM_PIN 0xda
#define SSD1306_COMM_DESELECT_LV 0xdb
#define SSD1306_COMM_CONTRAST 0x81
#define SSD1306_COMM_DISABLE_SCROLL 0x2e
#define SSD1306_COMM_ENABLE_SCROLL 0x2f
#define SSD1306_COMM_PAGE_NUMBER 0xb0
#define SSD1306_COMM_LOW_COLUMN 0x00
#define SSD1306_COMM_HIGH_COLUMN 0x10

#define SSD1306_COMM_START_LINE 0x40

#define SSD1306_COMM_CHARGE_PUMP 0x8d

#define SSD1306_COMM_SCAN_NORM 0xc0
#define SSD1306_COMM_SCAN_REVS 0xc8

#define SSD1306_COMM_MEMORY_MODE 0x20
#define SSD1306_COMM_SET_COL_ADDR 0x21
#define SSD1306_COMM_SET_PAGE_ADDR 0x22

#define SSD1306_HORI_MODE 0x00
#define SSD1306_VERT_MODE 0x01
#define SSD1306_PAGE_MODE 0x02

#define SSD1306_FONT_SMALL 0x00
#define SSD1306_FONT_NORMAL 0x01

#define SSD1306_128_32_COLUMNS 128
#define SSD1306_128_32_LINES 32
#define SSD1306_128_64_LINES 64

#define NUM_ROWS_PER_PAGE 8
#define MAX_PAGES 4

typedef struct
{
  int fd;
  char *dev;                // device name. a copy is made.
  uint8_t addr;             // default 0x3c
  uint8_t width;            // default 128
  uint8_t height;           // default 64
  uint8_t *gddram_buffer;   // buffer for GDDRAM size (height x width/8) + 1 bytes
  size_t gddram_buffer_len; // value = (height x width / 8) + 1
} ssd1306_i2c_t;

ssd1306_i2c_t *ssd1306_i2c_open( // open the device for read/write
  const char *dev,             // name of the device such as /dev/i2c-1. cannot be NULL
  uint8_t daddr,               // I2C address of the device. valid values: 0 (default) or 0x3c or 0x3d
  uint8_t width,               // OLED display width. valid values: 0 (default) or 128
  uint8_t height             // OLED display height. valid values: 0 (default) or 32 or 64
);

void ssd1306_i2c_close(ssd1306_i2c_t *oled); // free object and close fd


typedef enum
{
  SSD1306_I2C_CMD_NOP, // no operation
  // power
  SSD1306_I2C_CMD_POWER_OFF,
  SSD1306_I2C_CMD_POWER_ON,
  // addressing
  SSD1306_I2C_CMD_MEM_ADDR_HORIZ, // set horizontal addressing mode
  SSD1306_I2C_CMD_MEM_ADDR_VERT,  // set vertical addressing mode
  SSD1306_I2C_CMD_MEM_ADDR_PAGE,  // set page addressing mode (RESET)
  SSD1306_I2C_CMD_COLUMN_ADDR,    // set column address. requires 2 data bytes
  SSD1306_I2C_CMD_PAGE_ADDR,      // set page address. requires 2 data bytes
  // layout
  SSD1306_I2C_CMD_DISP_START_LINE,        // set display start line. data 0x00-0x3F
  SSD1306_I2C_CMD_DISP_OFFSET,            // set display offset. data 0x00-0x3F
  SSD1306_I2C_CMD_DISP_CLOCK_DIVFREQ,     // set display clock divide/frequency.
                                          // data: refer datasheet
  SSD1306_I2C_CMD_DISP_CONTRAST,          // set display contrast control. data: 1-255
  SSD1306_I2C_CMD_DISP_NORMAL,            // set display normal
  SSD1306_I2C_CMD_DISP_INVERTED,          // set display inverted
  SSD1306_I2C_CMD_DISP_DISABLE_ENTIRE_ON, // disable entire display on
  SSD1306_I2C_CMD_DISP_ENTIRE_ON,         // set entire display on
  SSD1306_I2C_CMD_SEG_REMAP,              // set segment remap. data: 0 for col 0 or 1 for col 127
  SSD1306_I2C_CMD_MUX_RATIO,              // set multiplex ratio 0x1F or 0x3F
  SSD1306_I2C_CMD_COM_SCAN_DIRXN_NORMAL,  // set COM pins scan direction normal
  SSD1306_I2C_CMD_COM_SCAN_DIRXN_INVERT,  // set COM pins scan direction reverse
  SSD1306_I2C_CMD_COM_PIN_CFG,            // set COM pin config. data: 0x02, 0x12, 0x22, 0x32
  SSD1306_I2C_CMD_PRECHARGE_PERIOD,       // set precharge period. data: 0xF1 for reset. refer datasheet
  SSD1306_I2C_CMD_VCOMH_DESELECT,         // set VCOMH deselect level
  SSD1306_I2C_CMD_ENABLE_CHARGE_PUMP,     // enable charge pump regulator
  SSD1306_I2C_CMD_DISABLE_CHARGE_PUMP,    // disable charge pump regulator
  SSD1306_I2C_CMD_SCROLL_DEACTIVATE,
  // for scroll, reasonable defaults are automatically setup by the function
  // when these commands are invoked with NULL data pointers. however, the
  // user must verify that those defaults are correct for their use case or
  // must refer to the data sheets.
  SSD1306_I2C_CMD_SCROLL_LEFT_HORIZONTAL, // perform left horizontal scroll
                                          // legacy enum value set to activate left horizontal scrolling automatically
#define SSD1306_I2C_CMD_SCROLL_ACTIVATE SSD1306_I2C_CMD_SCROLL_LEFT_HORIZONTAL
  SSD1306_I2C_CMD_SCROLL_RIGHT_HORIZONTAL,          // perform right horizontal scroll
  SSD1306_I2C_CMD_SCROLL_VERTICAL_LEFT_HORIZONTAL,  // perform vertical and left horizontal scroll
  SSD1306_I2C_CMD_SCROLL_VERTICAL_RIGHT_HORIZONTAL, // perform vertical and right horizontal scroll
  SSD1306_I2C_CMD_SCROLL_VERTICAL_AREA              // set vertical scroll area.
} ssd1306_i2c_cmd_t;

class Display
{
private:
  static constexpr uint8_t MAX_COLUMNS = SSD1306_128_32_COLUMNS;
  static constexpr uint8_t MAX_LINES = SSD1306_128_32_LINES;
  uint8_t global_x = 0;
  uint8_t global_y = 0;

  // Array of pages to model the entire display
  uint8_t frameBuffer[MAX_LINES][MAX_COLUMNS];

  int fd;
  ssd1306_i2c_t *oled;  // Member variable to store the ssd1306_i2c_t pointer

  const static uint8_t FONT_SIZE = 5;
  const static unsigned char font[][FONT_SIZE];

  static size_t ssd1306_i2c_internal_get_cmd_bytes(ssd1306_i2c_cmd_t cmd,
                                                 uint8_t *data, size_t dlen, uint8_t *cmdbuf, size_t cmd_buf_max);

  int ssd1306_i2c_run_cmd(ssd1306_i2c_t *oled,   // the ssd1306_i2c_t object
                          ssd1306_i2c_cmd_t cmd, // command to run on the display
                          uint8_t *data,         // optional command data, if any, otherwise use 0 or NULL
                          size_t dlen            // length of the data bytes. max is 6 per datasheet.
  );

  // initialize the display before use
  int ssd1306_i2c_display_initialize(ssd1306_i2c_t *oled);

public:
  Display(ssd1306_i2c_t *oled);
  ~Display();

  // clear the display (calls ssd1306_i2c_display_update() internally)
  int ssd1306_i2c_display_clear(ssd1306_i2c_t *oled);

  // fill the display (calls ssd1306_i2c_display_update() internally)
  int ssd1306_i2c_display_fill(ssd1306_i2c_t *oled);

  // update the display's GDDRAM with the framebuffer contents.
  // this function can be called in an idle loop or on a timer or on-demand
  int ssd1306_i2c_display_update(ssd1306_i2c_t *oled);

};

#endif // DISPLAY_HPP