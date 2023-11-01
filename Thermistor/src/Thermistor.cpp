#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <math.h>

float A = 0.0011252566721075908;
float B = 0.0002347204472978223;
float C = 8.563052731505118e-8;


int main() {
    int file;
    const char *filename = "/dev/i2c-1"; // Use the appropriate I2C bus number
    if ((file = open(filename, O_RDWR)) < 0) {
        std::cerr << "Failed to open the bus." << std::endl;
        return 1;
    }

    int addr = 0x48; // Replace with the address of your device
    if (ioctl(file, I2C_SLAVE, addr) < 0) {
        std::cerr << "Failed to acquire bus access and/or talk to slave." << std::endl;
        return 1;
    }

    // Set the configuration bytes for continuous conversion mode
    char config[2] = {0b10000100, 0b00000011}; // MSB, LSB for configuration register
    if (write(file, config, 2) != 2) {
        std::cerr << "Error writing to the i2c bus." << std::endl;
        return 1;
    }

    while (true) {
        // Read the data from the ADC
        char data[2] = {0};
        if (read(file, data, 2) != 2) {
            std::cerr << "Error reading from the i2c bus." << std::endl;
            return 1;
        }

        // Convert the data to 16-bits
        int16_t adc_value = (data[0] << 8) | data[1];

        // Adjust the ADC value
        int16_t adjusted_adc_value = adc_value;

        float kelvin = 1 / (A + B * log(adjusted_adc_value) + C * pow(log(adjusted_adc_value), 3));

        float celsius = kelvin - 273.15;


        // Print the resistance value
        std::cout << "Celcius: " << adc_value << std::endl;

        sleep(1); // Sleep for 1 second before the next reading
    }

    close(file);
    return 0;
}