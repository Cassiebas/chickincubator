#include "Display.hpp"

#include <iostream>
#include <unistd.h>  

int main(){

  const char *filename = "/dev/i2c-1";
  const int i2c_address = 0x3C;

  ssd1306_i2c_t *oled = ssd1306_i2c_open(filename, i2c_address, 128, 32);
  ssd1306_framebuffer_t *fbp = ssd1306_framebuffer_create(oled->width, oled->height);


  Display display(oled);
  
  display.ssd1306_framebuffer_clear(fbp);

  display.ssd1306_framebuffer_put_pixel(fbp, 0, 0, true);
  display.ssd1306_framebuffer_put_pixel(fbp, fbp->width - 1, 0, true);
  display.ssd1306_framebuffer_put_pixel(fbp, 0, fbp->height - 1, true);
  display.ssd1306_framebuffer_put_pixel(fbp, fbp->width - 1, fbp->height - 1, true);
  display.ssd1306_framebuffer_put_pixel(fbp, 9, 10, true);

  display.ssd1306_i2c_display_update(oled, fbp);
  sleep(3);
  display.ssd1306_framebuffer_clear(fbp);
  display.ssd1306_framebuffer_put_pixel(fbp, 0, 0, false);
  display.ssd1306_framebuffer_put_pixel(fbp, fbp->width - 1, 0, false);
  display.ssd1306_framebuffer_put_pixel(fbp, 0, fbp->height - 1, false);
  display.ssd1306_framebuffer_put_pixel(fbp, fbp->width - 1, fbp->height - 1, false);
  display.ssd1306_framebuffer_put_pixel(fbp, 9, 10, false);
  display.ssd1306_i2c_display_update(oled, fbp);
  display.ssd1306_framebuffer_clear(fbp);
  sleep(3);
  
  display.ssd1306_framebuffer_clear(fbp);
  display.ssd1306_i2c_display_clear(oled);

  return 0;
}