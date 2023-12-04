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
#define SSD1306_SETSTARTLINE 0x40
#define SSD1306_MEMORYMODE 0x20
#define SSD1306_COLUMNADDR 0x21
#define SSD1306_PAGEADDR   0x22
#define SSD1306_COMSCANINC 0xC0
#define SSD1306_COMSCANDEC 0xC8
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

static int Write_Data(bool is_cmd, uint8_t data);
static int OLED_Init(void);

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

static int Write_Data(bool is_cmd, uint8_t data) {
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
  u8 buf[2];
  if (is_cmd == true)
  {
    buf[0] = 0x00;
  }
  else
  {
    buf[0] = 0x40;
  }
  buf[1] = data;

  if (i2c_smbus_write_i2c_block_data(display_driver_client, 0x00, 2, buf) < 0) {
    printk("Error writing to the i2c bus.\n");
    return -1;
  }
  return 0;
}

/** 
 * @brief Configuration bytes for intitial OLED startup
*/
static int OLED_Init(void) {
  int fault = 0;

  fault |= Write_Data(true, SSD1306_DISPLAYOFF);
  fault |= Write_Data(true, SSD1306_SETDISPLAYCLOCKDIV);
  fault |= Write_Data(true, 0x80);
  fault |= Write_Data(true, SSD1306_SETMULTIPLEX);
  fault |= Write_Data(true, 31);
  fault |= Write_Data(true, SSD1306_SETDISPLAYOFFSET);
  fault |= Write_Data(true, 0x0);
  fault |= Write_Data(true, SSD1306_CHARGEPUMP);
  fault |= Write_Data(true, 0x14);
  fault |= Write_Data(true, SSD1306_SETCOMPINS);
  fault |= Write_Data(true, 0x02);
  fault |= Write_Data(true, SSD1306_SETCONTRAST);
  fault |= Write_Data(true, 0x7F);
  fault |= Write_Data(true, SSD1306_SETPRECHARGE);
  fault |= Write_Data(true, 0xf1);
  fault |= Write_Data(true, SSD1306_SETVCOMDETECT);
  fault |= Write_Data(true, 0x40);
  fault |= Write_Data(true, SSD1306_DISPLAYALLON_RESUME);
  fault |= Write_Data(true, 0x00);
  fault |= Write_Data(true, SSD1306_NORMALDISPLAY);
  fault |= Write_Data(true, SSD1306_DISPLAYON);
  fault |= Write_Data(true, SSD1306_COMM_DISABLE_SCROLL);

  if(fault < 0)
  {
    return -1;
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

  // Check for copy errors
  if (not_copied != 0) {
    return -EINVAL;
  }

  is_cmd = (buffer[0] == 0x00 ? 1 : 0);

  // Process each byte and call Write_Data
  for (size_t i = 1; i < count; ++i)
  {
    // Assuming your Write_Data function takes a single byte as an argument
    if(Write_Data(is_cmd, buffer[i] < 0)){
      printk("Error writing received data: %s \n", buffer);
    }
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