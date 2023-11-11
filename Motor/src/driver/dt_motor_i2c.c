#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/i2c.h>

/* Meta Information */
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Casper Leitner");
MODULE_DESCRIPTION("A driver for our motor driver board");

static struct i2c_client *motor_driver_client;

struct motor_config
{
  const char *name;
  __u8 value;
};

static const struct motor_config config_registers[] = {
  {"CONTROL", 0x00},
  {"5v", 0b11111100},
  {"forward", 0b00000001},
  {"backward", 0b00000010},
  {"brake", 0b00000011},
  {"coast", 0b00000000},
  {"FAULT", 0x01},
  {"clear", 0b10000000}
};

struct voltage_config
{
  u8 binary_value;
  float output_voltage;
};

static const struct voltage_config voltage_data[] = {
  {0b00011000, 0.48},
  {0b00011100, 0.56},
  {0b00100000, 0.64},
  {0b00100100, 0.72},
  {0b00101000, 0.80},
  {0b00101100, 0.88},
  {0b00110000, 0.96},
  {0b00110100, 1.04},
  {0b00111000, 1.12},
  {0b00111100, 1.20},
  {0b01000000, 1.29},
  {0b01000100, 1.37},
  {0b01001000, 1.45},
  {0b01001100, 1.53},
  {0b01010000, 1.61},
  {0b01010100, 1.69},
  {0b01011000, 1.77},
  {0b01011100, 1.85},
  {0b01100000, 1.93},
  {0b01100100, 2.01},
  {0b01101000, 2.09},
  {0b01101100, 2.17},
  {0b01110000, 2.25},
  {0b01110100, 2.33},
  {0b01111000, 2.41},
  {0b01111100, 2.49},
  {0b10000000, 2.58},
  {0b10000100, 2.66},
  {0b10001000, 2.74},
  {0b10001100, 2.82},
  {0b10010000, 2.90},
  {0b10010100, 2.98},
  {0b10011000, 3.05},
  {0b10011100, 3.13},
  {0b10100000, 3.21},
  {0b10100100, 3.29},
  {0b10101000, 3.37},
  {0b10101100, 3.45},
  {0b10110000, 3.53},
  {0b10110100, 3.61},
  {0b10111000, 3.69},
  {0b10111100, 3.77},
  {0b11000000, 3.86},
  {0b11000100, 3.94},
  {0b11001000, 4.02},
  {0b11001100, 4.10},
  {0b11010000, 4.18},
  {0b11010100, 4.26},
  {0b11011000, 4.34},
  {0b11011100, 4.42},
  {0b11100000, 4.50},
  {0b11100100, 4.58},
  {0b11101000, 4.66},
  {0b11101100, 4.74},
  {0b11110000, 4.82},
  {0b11110100, 4.90},
  {0b11111000, 4.98},
  {0b11111100, 5.06}
};

int percentage_scale = 100 / sizeof(voltage_data);

/* Declate the probe and remove functions */
static int motor_probe(struct i2c_client *client, const struct i2c_device_id *id);
static void motor_remove(struct i2c_client *client);

static int write_config(void);

static struct of_device_id my_driver_ids[] = {
    {
        .compatible = "brightlight,motor",
    },
    {/* sentinel */}};
MODULE_DEVICE_TABLE(of, my_driver_ids);

static struct i2c_device_id motor[] = {
    {"motor", 0},
    {},
};
MODULE_DEVICE_TABLE(i2c, motor);

static struct i2c_driver my_driver = {
    .probe = motor_probe,
    .remove = motor_remove,
    .id_table = motor,
    .driver = {
        .name = "motor",
        .of_match_table = my_driver_ids,
    },
};

static struct proc_dir_entry *proc_file;

static int write_config(void)
{
  u8 config_data[2];

  config_data[0] = config_registers[6].value; // FAULT registry
  config_data[1] = config_registers[7].value; // clear
  if (i2c_smbus_write_i2c_block_data(motor_driver_client, 0x00, 2, config_data) < 0)
  {
    printk("Error writing to the i2c bus.\n");
    return -1;
  }

  config_data[0] = config_registers[0].value;                             // CONTROL registry
  config_data[1] = config_registers[1].value | config_registers[4].value; // 5v and brakes

  if (i2c_smbus_write_i2c_block_data(motor_driver_client, 0x00, 2, config_data) < 0)
  {
    printk("Error writing to the i2c bus.\n");
    return -1;
  }

  return 0;
}

/**
 * @brief write to motor driver
 */
static ssize_t my_write(struct file *File, const char *user_buffer, size_t count, loff_t *offs)
{
  char command[10];
  char pwm_str[5];
  int percentage, to_write, index;
  u8 voltage;

    // Copy user buffer data to kernel buffer
  if (copy_from_user(command, user_buffer, 7) != 0)
  {
    printk("Error copying data from user space.\n");
    return -EFAULT;
  }

  // Null-terminate the command string
  command[7] = '\0';

  // Extract the PWM value from the user buffer
  if (copy_from_user(pwm_str, user_buffer + 7, 3) != 0)
  {
    printk("Error copying data from user space.\n");
    return -EFAULT;
  }

  // Null-terminate the PWM string
  pwm_str[3] = '\0';

  // Convert PWM string to an integer
  percentage = simple_strtol(pwm_str, NULL, 10);

  index = (percentage_scale * percentage);

  voltage = voltage_data[index - 1].binary_value;

  printk("Motor command: %s, voltage selected: %d\n", command, voltage);

  if (strcmp(user_buffer, config_registers[2].name) == 0)
  { 
    to_write = voltage | config_registers[2].value;
    i2c_smbus_write_byte(motor_driver_client, to_write);
  }
  else if (strcmp(user_buffer, config_registers[3].name) == 0)
  {
    to_write = voltage | config_registers[2].value;
    i2c_smbus_write_byte(motor_driver_client, to_write);
  }
  else
  {
    printk("Invalid command. Please enter either 'forward' or 'backward'.\n");
    return -EINVAL;
  }

  return count;
}

// /**
//  * @brief Read ADC value
//  */
// static ssize_t my_read(struct file *File, char *user_buffer, size_t count, loff_t *offs) {
// 	u8 adc;
// 	adc = i2c_smbus_read_byte(motor_driver_client);
// 	return sprintf(user_buffer, "%d\n", adc);
// }

static struct proc_ops fops = {
    .proc_write = my_write,
    //.proc_read = my_read,
};

/**
 * @brief This function is called on loading the driver
 */
static int motor_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
  printk("dt_motor_i2c - Now I am in the Probe function!\n");

  if (client->addr != 0x60)
  {
    printk("dt_motor_i2c - Wrong I2C address!\n");
    return -1;
  }

  motor_driver_client = client;

  /* Creating procfs file */
  proc_file = proc_create("mymotor", 0666, NULL, &fops);
  if (proc_file == NULL)
  {
    printk("dt_motor_i2c - Error creating /proc/mymotor\n");
    return -ENOMEM;
  }

  if (write_config() > 0)
  {
    printk("Failed to write config bytes to motor driver.\n");
  }
  return 0;
}

/**
 * @brief This function is called on unloading the driver
 */
static void motor_remove(struct i2c_client *client)
{
  printk("dt_motor_i2c - Now I am in the Remove function!\n");
  proc_remove(proc_file);
}

/* This will create the init and exit function automatically */
module_i2c_driver(my_driver);