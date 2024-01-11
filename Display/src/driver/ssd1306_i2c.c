#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/i2c.h>
#include <linux/slab.h>

/* Meta Information */
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Casper Leitner");
MODULE_DESCRIPTION("A driver for our SSD1306 display chip");

static struct i2c_client *display_driver_client;

/* Declate the probe and remove functions */
static int display_probe(struct i2c_client *client, const struct i2c_device_id *id);
static void display_remove(struct i2c_client *client);

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

static ssize_t driver_write(struct file *File, const char *user_buffer, size_t count, loff_t *offs)
{
  int not_copied;
  char *buffer;
  printk("driver_write() called!\n");

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

  if(i2c_master_send(display_driver_client, buffer, count)) {
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