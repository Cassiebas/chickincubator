#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/cdev.h>
#include <linux/property.h>
#include <linux/uaccess.h>
#include <linux/gpio/consumer.h>
#include <linux/kernel.h>
#include <linux/mod_devicetable.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>

/* Meta Information */
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Casper Leitner");
MODULE_DESCRIPTION("A simple gpio driver for setting a GPIO's output value and reading a pin's value");

/* Declate the probe and remove functions */
static int dt_probe(struct platform_device *pdev);
static int dt_remove(struct platform_device *pdev);

static struct gpio_desc *gpio_descs[26];

static struct proc_dir_entry *proc_file;

static struct of_device_id my_driver_ids[] = {
	{
		.compatible = "gpio,mygpiodev",
	}, { /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, my_driver_ids);

static struct platform_driver my_driver = {
	.probe = dt_probe,
	.remove = dt_remove,
	.driver = {
		.name = "my_device_driver",
		.of_match_table = my_driver_ids,
	},
};

/**
 * @brief Read data out of the buffer
 */
static ssize_t driver_read(struct file *File, char *user_buffer, size_t count, loff_t *offs)
{
  int not_copied, delta;
  char pin_state;
  long gpio_pin_int = 0;
  char gpio_pin[3] = {0};

  /* Copy data from user_buffer */
  not_copied = copy_from_user(gpio_pin, user_buffer, count);
  gpio_pin[count > 1 ? 2 : 1] = '\0'; // Null-terminate the string

  if (kstrtol(gpio_pin, 10, &gpio_pin_int)) {
    printk("Failed to convert GPIO pin to integer\n");
    return -EINVAL; // Return an error code
  }

  printk("GPIO pin to read: %ld\n", gpio_pin_int);

  pin_state = gpiod_get_value(gpio_descs[gpio_pin_int]) + '0';

  printk("%s's value is %c\n", gpio_pin, pin_state); 

  /* Copy data to user_buffer */
  if (copy_to_user(user_buffer, &pin_state, sizeof(pin_state))) {
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
  int not_copied, delta;
  int output_state = -2;
  long gpio_pin_int = 0;
  char io_set_value = 0;
  char gpio_pin[3] = {0};

  /* Ensure there is at least one byte to copy */
  if (count < 1)
  {
    printk("Invalid input: at least 1 byte required!\n");
    return -EINVAL; // Return an error code
  }

  /* Copy data from user_buffer */
  not_copied = copy_from_user(gpio_pin, user_buffer,count > 2 ? 2 : 1);

  if (count == 2) {
    printk("A char was sent\n");
    not_copied = copy_from_user(&io_set_value, user_buffer + 1,1);
    if(io_set_value != 'O' && io_set_value != 'I')
      output_state = io_set_value - '0'; // a 1 or 0 for output has been send

    gpio_pin[1] = '\0'; // Null-terminate the string
  }
  else
  {
    printk("A string was sent\n");
    not_copied = copy_from_user(&io_set_value, user_buffer + 2,1);
    if(io_set_value != 'O' && io_set_value != 'I')
      output_state = io_set_value - '0'; // a 1 or 0 for output has been send

    gpio_pin[2] = '\0'; // Null-terminate the string
  }
  if (kstrtol(gpio_pin, 10, &gpio_pin_int)) {
    printk("Failed to convert GPIO pin to integer\n");
    return -EINVAL; // Return an error code
  }

  printk("GPIO_PIN send : %ld\n", gpio_pin_int);
  printk("GPIO_PIN state : %c\n", io_set_value);
  if (io_set_value == 'I')
  {
    if (gpiod_direction_input(gpio_descs[gpio_pin_int]))
    {
      printk("GPIO pin %s is already set to input!\n", gpio_pin);
    }
    printk("GPIO pin %s, set as Input\n", gpio_pin);
  }
  else if (io_set_value == 'O')
  {
    if (gpiod_direction_output(gpio_descs[gpio_pin_int], 0))
    {
      printk("GPIO pin %s is already set to output!\n", gpio_pin);
    }
    printk("GPIO pin %s, set as output\n", gpio_pin);
  }
  
	switch(output_state) {
		case 0:
        printk("Setting pin output LOW\n");
        gpiod_set_value(gpio_descs[gpio_pin_int], 0);
			break;
		case 1:
        printk("Setting pin output HIGH\n");
        gpiod_set_value(gpio_descs[gpio_pin_int], 1);
			break;
		default:
			break;
	}

  /* Calculate data */
  delta = min(count, sizeof(gpio_pin) + sizeof(io_set_value)) - not_copied;

  return delta;
}

static struct proc_ops fops = {
  .proc_read = driver_read,
  .proc_write = driver_write
};

static int dt_probe(struct platform_device *pdev) {
	struct device *dev = &pdev->dev;
  int i;

	printk("dt_gpio - Now I am in the probe function!\n");
	/* Init GPIO */
  for (i = 0; i < 26; ++i) {
    char label[3];
      if(!(i > 1 && i <= 4)){
      snprintf(label, sizeof(label), "%d", i);
      
      printk("%s", label);
      gpio_descs[i] = gpiod_get(dev, label, GPIOD_ASIS);

      if (IS_ERR(gpio_descs[i])) {
        pr_err("Error obtaining GPIO descriptor for pin %d: %ld\n", i, PTR_ERR(gpio_descs[i]));
        gpio_descs[i] = NULL;  // Set to NULL to indicate failure
      }
    }
    else
      gpio_descs[i] = NULL;
  }

	/* Creating procfs file */
	proc_file = proc_create("gpio_driver", 0666, NULL, &fops);
	if(proc_file == NULL) {
		printk("procfs_test - Error creating /proc/my-led\n");
		return -ENOMEM;
	}

	return 0;
}

/**
 * @brief This function is called on unloading the driver 
 */
static int dt_remove(struct platform_device *pdev) {
  int index;
	printk("dt_gpio - Now I am in the remove function\n");

  for (index = 0; index < 26; ++index) {
    if (gpio_descs[index] != NULL) {
      gpiod_put(gpio_descs[index]);
    }
  }
	proc_remove(proc_file);
	return 0;
}

/**
 * @brief This function is called, when the module is loaded into the kernel
 */
static int __init my_init(void) {
	printk("dt_gpio - Loading the driver...\n");
	if(platform_driver_register(&my_driver)) {
		printk("dt_gpio - Error! Could not load driver\n");
		return -1;
	}
	return 0;
}

/**
 * @brief This function is called, when the module is removed from the kernel
 */
static void __exit my_exit(void) {
	printk("dt_gpio - Unload driver");
	platform_driver_unregister(&my_driver);
}

module_init(my_init);
module_exit(my_exit);