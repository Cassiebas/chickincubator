obj-m += GPIO_Driver.o

all: module dt
	echo Builded Device Tree Overlay and kernel module

module:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
dt: gpio.dts
	dtc -@ -I dts -O dtb -o gpio.dtbo gpio.dts
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -rf gpio.dtbo