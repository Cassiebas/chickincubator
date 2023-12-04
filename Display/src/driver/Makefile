obj-m += ssd1306_i2c.o

all: module dt
	echo Builded Device Tree Overlay and kernel module

module:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
dt: display.dts
	dtc -@ -I dts -O dtb -o display.dtbo display.dts
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -rf display.dtbo