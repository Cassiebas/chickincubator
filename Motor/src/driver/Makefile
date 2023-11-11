obj-m += dt_motor_i2c.o

all: module dt
	echo Builded Device Tree Overlay and kernel module

module:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
dt: Moter_overlay.dts
	dtc -@ -I dts -O dtb -o Moter_overlay.dtbo Moter_overlay.dts
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -rf Moter_overlay.dtbo