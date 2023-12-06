#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/i2c.h>
#include <linux/slab.h>


#define SSD1306_LCDWIDTH      128
#define SSD1306_LCDHEIGHT      64
#define SSD1306_SETCONTRAST   0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON 0xA5
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_DISPLAYOFF 0xAE
#define SSD1306_DISPLAYON 0xAF
#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETCOMPINS 0xDA
#define SSD1306_SETVCOMDETECT 0xDB
#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE 0xD9
#define SSD1306_SETMULTIPLEX 0xA8
#define SSD1306_SETLOWCOLUMN 0x00
#define SSD1306_SETHIGHCOLUMN 0x10
#define SSD1306_PAGE_MODE 0x02
#define SSD1306_SETSTARTLINE 0x40
#define SSD1306_MEMORYMODE 0x20
#define SSD1306_COMSCANDEC 0xC8
#define SSD1306_COLUMNADDR 0x21
#define SSD1306_PAGEADDR   0x22
#define SSD1306_COMSCANINC 0xC0
#define SSD1306_SEGREMAP 0xA0
#define SSD1306_CHARGEPUMP 0x8D
#define SSD1306_EXTERNALVCC 0x1
#define SSD1306_SWITCHCAPVCC 0x2
#define SSD1306_COMM_DISABLE_SCROLL 0x2e


/* Meta Information */
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Casper Leitner");
MODULE_DESCRIPTION("A driver for our SSD1306 display chip");

static struct i2c_client *display_driver_client;

/* Declate the probe and remove functions */
static int display_probe(struct i2c_client *client, const struct i2c_device_id *id);
static void display_remove(struct i2c_client *client);

static int Write_Data(bool is_cmd, uint8_t *data, size_t size);
static int OLED_Init(void);
static int OLED_Resolution(void);

static struct of_device_id my_driver_ids[] = {
  {
    .compatible = "display,ssd1306",	
  },
  {/* sentinel */}
};
MODULE_DEVICE_TABLE(of, my_driver_ids);

static struct i2c_device_id display[] = {
  {"ssd1306", 0},
  {},
};
MODULE_DEVICE_TABLE(i2c, display);

static struct i2c_driver my_driver = {
  .probe = display_probe,
  .remove = display_remove,
  .id_table = display,
  .driver = {
    .name = "ssd1306",
    .of_match_table = my_driver_ids,
  },
};

static struct proc_dir_entry *proc_file;

static int Write_Data(bool is_cmd, uint8_t *data, size_t size) {
  uint8_t control_buffer;
  /*
  ** First byte is always control byte. Data is followed after that.
  **
  ** There are two types of data in SSD_1306 OLED.
  ** 1. Command
  ** 2. Data
  **
  ** Control byte decides that the next byte is, command or data.
  **
  ** -------------------------------------------------------
  ** |              Control byte's | 6th bit  |   7th bit  |
  ** |-----------------------------|----------|------------|
  ** |   Command                   |   0      |     0      |
  ** |-----------------------------|----------|------------|
  ** |   data                      |   1      |     0      |
  ** |-----------------------------|----------|------------|
  **
  ** Please refer the datasheet for more information.
  **
  */
  if (size == 0) {
    printk("Error: Data size is zero.\n");
    return -1;
  }

  if (is_cmd == true)
  {
    control_buffer = 0x00;
  }
  else
  {
    control_buffer = 0x40;
  }

  for(size_t i = 0; i < size; i++){
    if (i2c_smbus_write_byte_data(display_driver_client, control_buffer, data[i]) < 0) {
      printk("Error writing to the i2c bus.\n");
      return -1;
    }
  }

  return 0;
}

/** 
 * @brief Configuration bytes for intitial OLED startup
*/
static int OLED_Init(void) {
  uint8_t data[28];
  uint8_t i = 0;

  data[i] = SSD1306_DISPLAYOFF;
  data[i++] = SSD1306_NORMALDISPLAY;
  data[i++] = SSD1306_SETDISPLAYCLOCKDIV;
  data[i++] = 0x80;
  data[i++] = SSD1306_SETMULTIPLEX;
  data[i++] = 31;
  data[i++] = SSD1306_SETDISPLAYOFFSET;
  data[i++] = 0;
  data[i++] = SSD1306_SETSTARTLINE;
  data[i++] = SSD1306_CHARGEPUMP;
  data[i++] = 0x14;
  data[i++] = SSD1306_MEMORYMODE;
  data[i++] = 0x00;
  data[i++] = SSD1306_COMSCANDEC;
  data[i++] = SSD1306_MEMORYMODE;
  data[i++] = SSD1306_SETCOMPINS;
  data[i++] = 0x02;
  data[i++] = SSD1306_SETCONTRAST;
  data[i++] = 0x8F;
  data[i++] = SSD1306_SETPRECHARGE;
  data[i++] = 0xf1;
  data[i++] = SSD1306_SETVCOMDETECT;
  data[i++] = 0x40;
  data[i++] = SSD1306_DISPLAYALLON_RESUME;
  data[i++] = 0x00;
  data[i++] = SSD1306_NORMALDISPLAY;
  data[i++] = SSD1306_COMM_DISABLE_SCROLL;
  data[i++] = SSD1306_DISPLAYON;

  if(Write_Data(true, data, sizeof(data)) < 0)
  {
    return -1;
  }
  return 0;
}


/** 
 * @brief Resolution bytes for intitial OLED startup
*/
static int OLED_Resolution(void) {
  uint8_t data[7];
  uint8_t i = 0;

  data[i] = SSD1306_COLUMNADDR;
  data[i++] = 0;
  data[i++] = (SSD1306_LCDWIDTH - 1);
  data[i++] = SSD1306_PAGEADDR;
  data[i++] = 0;
  data[i++] = 3;

	for (uint8_t index = 0; index < (SSD1306_LCDWIDTH) * (SSD1306_LCDHEIGHT/2) / 8; index++) {
		i2c_smbus_write_byte_data(display_driver_client, 0x40, data[i]); 
		//This sends byte by byte. 
		//Better to send all buffer without 0x40 first
		//Should be optimized
	}
  return 0;
}
/**
 * @brief write to display driver
 */
static ssize_t driver_write(struct file *File, const char *user_buffer, size_t count, loff_t *offs)
{
  int is_cmd, not_copied;
  char *buffer;

  /* Ensure there is at least one byte to copy */
  if (count < 2)
  {
    printk("Invalid input: at least 2 byte required!\n");
    return -EINVAL; // Return an error code
  }

  // Dynamically allocate memory for the buffer
  buffer = kmalloc(count, GFP_KERNEL);

  if (!buffer)
  {
    printk("Memory allocation failed!\n");
    return -ENOMEM; // Return an error code
  }

  // Copy data from user space to kernel space
  not_copied = copy_from_user(buffer, user_buffer, count);

  for (size_t i = 0; i < count; ++i)
  {
    printk("0x%02X ", buffer[i]);  // Print each byte in hexadecimal format with leading zeros
  }
  printk("\n");  // Add a newline at the end for better readability

  // Check for copy errors
  if (not_copied != 0) {
    return -EINVAL;
  }

  is_cmd = (buffer[0] == 0x00 ? 1 : 0);

  if(Write_Data(is_cmd, buffer, sizeof(buffer))){
    printk("Error writing received data: %s \n", buffer);
  }

  // Free the dynamically allocated memory
  kfree(buffer);

  return count;
}

static struct proc_ops fops = {
  .proc_write = driver_write
};

/**
 * @brief This function is called on loading the driver
 */
static int display_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
  printk("dt_display_i2c - Now I am in the Probe function!\n");

  if (client->addr != 0x3C)
  {
    printk("dt_display_i2c - Wrong I2C address!\n");
    return -1;
  }

  display_driver_client = client;

  /* Creating procfs file */
  proc_file = proc_create("SSD1306", 0666, NULL, &fops);
  if (proc_file == NULL)
  {
    printk("dt_display_i2c - Error creating /proc/SSD1306\n");
    return -ENOMEM;
  }

  if (OLED_Init() > 0)
  {
    printk("Failed to write config bytes to display driver.\n");
  }

  if (OLED_Resolution() > 0)
  {
    printk("Failed to write resolution bytes to display driver.\n");
  }
  return 0;
}

/**
 * @brief This function is called on unloading the driver
 */
static void display_remove(struct i2c_client *client)
{
  printk("dt_display_i2c - Now I am in the Remove function!\n");
  proc_remove(proc_file);
}

/* This will create the init and exit function automatically */
module_i2c_driver(my_driver);