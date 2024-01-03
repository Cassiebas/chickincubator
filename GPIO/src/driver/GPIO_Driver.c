#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>
#include <linux/kernel.h>

/* Meta Information */
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Casper Leitner");
MODULE_DESCRIPTION("A simple gpio driver for setting a GPIO's output value and reading a pin's value");

/* Variables for device and device class */
static dev_t my_device_nr;
static struct class *my_class;
static struct cdev my_device;

#define DRIVER_NAME "gpio_driver_egg_incubator"
#define DRIVER_CLASS "MyModuleClass"

/**
 * @brief Read data out of the buffer
 */
static ssize_t driver_read(struct file *File, char *user_buffer, size_t count, loff_t *offs)
{
  int not_copied, delta, pin_value_int;
  char tmp = '0';
  char gpio_pin[3] = {0};

  /* Copy data from user_buffer */
  not_copied = copy_from_user(gpio_pin, user_buffer, count > 1 ? 2 : 1);
  gpio_pin[count > 1 ? 2 : 1] = '\0'; // Null-terminate the string

  if(count > 1) {
    printk("a string\n");
    // string is sent
    pin_value_int = simple_strtol(gpio_pin, NULL, 10);
  }
  else
  {
    printk("a char\n");
    // char is sent
    pin_value_int = gpio_pin[0] - '0';
  }
  printk("GPIO pin to read: %d\n", pin_value_int);

  /* Check if the GPIO pin is valid */
  if (!gpio_is_valid(pin_value_int))
  {
    printk("GPIO pin %d is not valid!\n", pin_value_int);
    return -EINVAL; // Return an error code
  }

  printk("%d's value is %d\n", pin_value_int, gpio_get_value(pin_value_int));
  tmp = gpio_get_value(pin_value_int) + '0';

  /* Copy data to user_buffer */
  if (copy_to_user(user_buffer, &tmp, 1)) {
    printk("Failed to copy data to user_buffer\n");
    return -EFAULT; // Return a bad address error code
  }

  /* Calculate data */
  delta = count - not_copied;
  return delta;
}

/**
 * @brief Write data to buffer
 */
static ssize_t driver_write(struct file *File, const char *user_buffer, size_t count, loff_t *offs)
{
  int not_copied, delta, pin_value_int, set_value_int;
  char io_set_value = 0;
  char gpio_pin[3] = {0};

  /* Ensure there is at least one byte to copy */
  if (count < 1)
  {
    printk("Invalid input: at least 1 byte required!\n");
    return -EINVAL; // Return an error code
  }

  /* Copy data from user_buffer */
  not_copied = copy_from_user(gpio_pin, user_buffer, count > 1 ? 2 : 1);
  gpio_pin[count > 1 ? 2 : 1] = '\0'; // Null-terminate the string

  pin_value_int = simple_strtol(gpio_pin, NULL, 10);
  if (count == 2) {
    printk("A char was sent\n");
    pin_value_int = gpio_pin[0] - '0';
    if (!(gpio_pin[1] == 'O' || gpio_pin[1] == 'I'))
    {
      set_value_int = gpio_pin[1] - '0';
      printk("You are sending an output state:%d \n", set_value_int);
    }
    else
    {
      io_set_value = gpio_pin[1];
    }
  }
  else
  {
    printk("A string was sent\n");
    pin_value_int = simple_strtol(gpio_pin, NULL, 10);
    not_copied += copy_from_user(&io_set_value, user_buffer + 2, 1);
    if (!(io_set_value == 'O' || io_set_value == 'I'))
    {
      set_value_int = io_set_value - '0';
      printk("You are sending an output state:%d \n", set_value_int);
    }
  }

  // Check if the GPIO pin is already valid and requested
  if (!gpio_is_valid(pin_value_int))
  {
    printk("GPIO pin %d is not valid!\n", pin_value_int);
    return -1;
  }

  if (gpio_request(pin_value_int, "rpi-gpio"))
  {
    printk("Can not allocate pin %d\n", pin_value_int);
    goto GpioError;
  }

  if (io_set_value == 'I')
  {
    if (gpio_direction_input(pin_value_int))
    {
      printk("GPIO pin %d is already set to input!\n", pin_value_int);
      goto GpioError;
    }
    printk("GPIO pin %d, set as Input\n", pin_value_int);
  }
  else if (io_set_value == 'O')
  {
    if (gpio_direction_output(pin_value_int, 0))
    {
      printk("GPIO pin %d is already set to output!\n", pin_value_int);
      goto GpioError;
    }
    printk("GPIO pin %d, set as output\n", pin_value_int);
  }

	switch(set_value_int) {
		case 0:
        if(!(io_set_value == 'O' || io_set_value == 'I'))
        {
          printk("Setting pin output LOW\n");
          gpio_set_value(pin_value_int, 0);
        }
			break;
		case 1:
    printk("Setting pin output HIGH\n");
			gpio_set_value(pin_value_int, 1);
			break;
		default:
			printk("Invalid Input!\n");
			break;
	}

  /* Calculate data */
  delta = min(count, sizeof(gpio_pin) + sizeof(io_set_value)) - not_copied;

GpioError:
	gpio_free(pin_value_int);

  return delta;
}

/**
 * @brief This function is called, when the device file is opened
 */
static int driver_open(struct inode *device_file, struct file *instance)
{
  printk("dev_nr - open was called!\n");
  return 0;
}

/**
 * @brief This function is called, when the device file is opened
 */
static int driver_close(struct inode *device_file, struct file *instance)
{
  printk("dev_nr - close was called!\n");
  return 0;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = driver_open,
    .release = driver_close,
    .read = driver_read,
    .write = driver_write};

/**
 * @brief This function is called, when the module is loaded into the kernel
 */
static int __init ModuleInit(void)
{
  printk("Hello, Kernel!\n");

  /* Allocate a device nr */
  if (alloc_chrdev_region(&my_device_nr, 0, 1, DRIVER_NAME) < 0)
  {
    printk("Device Nr. could not be allocated!\n");
    return -1;
  }
  printk("read_write - Device Nr. Major: %d, Minor: %d was registered!\n", my_device_nr >> 20, my_device_nr && 0xfffff);

  /* Create device class */
  if ((my_class = class_create(THIS_MODULE, DRIVER_CLASS)) == NULL)
  {
    printk("Device class can not be created!\n");
    goto ClassError;
  }

  /* create device file */
  if (device_create(my_class, NULL, my_device_nr, NULL, DRIVER_NAME) == NULL)
  {
    printk("Can not create device file!\n");
    goto FileError;
  }

  /* Initialize device file */
  cdev_init(&my_device, &fops);

  /* Regisering device to kernel */
  if (cdev_add(&my_device, my_device_nr, 1) == -1)
  {
    printk("Registering of device to kernel failed!\n");
    goto AddError;
  }

  return 0;
AddError:
  device_destroy(my_class, my_device_nr);
FileError:
  class_destroy(my_class);
ClassError:
  unregister_chrdev_region(my_device_nr, 1);
  return -1;
}

/**
 * @brief This function is called, when the module is removed from the kernel
 */
static void __exit ModuleExit(void)
{
  gpio_set_value(4, 0);
  gpio_free(17);
  gpio_free(4);
  cdev_del(&my_device);
  device_destroy(my_class, my_device_nr);
  class_destroy(my_class);
  unregister_chrdev_region(my_device_nr, 1);
  printk("Goodbye, Kernel\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);