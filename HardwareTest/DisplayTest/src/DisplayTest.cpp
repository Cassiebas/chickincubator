#include "Display.hpp"

#include <iostream>
#include <unistd.h>  

int main(){
  Display display;

  ssd1306_i2c_t *oled = display.get_oled_data();
  ssd1306_framebuffer_t *frameBuff = display.get_framebuffer_data();

  display.framebuffer_clear(frameBuff);

  display.framebuffer_put_pixel(frameBuff, 0, 0, true);
  display.framebuffer_put_pixel(frameBuff, frameBuff->width - 1, 0, true);
  display.framebuffer_put_pixel(frameBuff, 0, frameBuff->height - 1, true);
  display.framebuffer_put_pixel(frameBuff, frameBuff->width - 1, frameBuff->height - 1, true);
  display.framebuffer_put_pixel(frameBuff, 9, 10, true);

  ssd1306_i2c_display_update(oled, frameBuff);
  sleep(3);
  display.framebuffer_clear(frameBuff);
  display.framebuffer_put_pixel(frameBuff, 0, 0, false);
  display.framebuffer_put_pixel(frameBuff, frameBuff->width - 1, 0, false);
  display.framebuffer_put_pixel(frameBuff, 0, frameBuff->height - 1, false);
  display.framebuffer_put_pixel(frameBuff, frameBuff->width - 1, frameBuff->height - 1, false);
  display.framebuffer_put_pixel(frameBuff, 9, 10, false);
  ssd1306_i2c_display_update(oled, frameBuff);
  display.framebuffer_clear(frameBuff);
  sleep(3);
  
  display.framebuffer_clear(frameBuff);
  ssd1306_i2c_display_clear(oled);

  return 0;
}