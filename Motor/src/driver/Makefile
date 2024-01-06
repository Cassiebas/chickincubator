obj-m += dt_motor_i2c.o

all: module dt
	echo Builded Device Tree Overlay and kernel module

module:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
dt: motor.dts
	dtc -@ -I dts -O dtb -o motor.dtbo motor.dts
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -rf motor.dtbo