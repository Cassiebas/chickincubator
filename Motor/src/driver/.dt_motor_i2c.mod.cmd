cmd_/home/pi/chickincubator/Motor/src/driver/dt_motor_i2c.mod := printf '%s\n'   dt_motor_i2c.o | awk '!x[$$0]++ { print("/home/pi/chickincubator/Motor/src/driver/"$$0) }' > /home/pi/chickincubator/Motor/src/driver/dt_motor_i2c.mod