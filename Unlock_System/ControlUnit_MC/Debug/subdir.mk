################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../buzzer.c \
../control_unit_programs.c \
../door.c \
../external_eeprom.c \
../i2c.c \
../lcd.c \
../led.c \
../mainCU.c \
../motor.c \
../timer.c \
../timer_pwm.c \
../uart.c 

OBJS += \
./buzzer.o \
./control_unit_programs.o \
./door.o \
./external_eeprom.o \
./i2c.o \
./lcd.o \
./led.o \
./mainCU.o \
./motor.o \
./timer.o \
./timer_pwm.o \
./uart.o 

C_DEPS += \
./buzzer.d \
./control_unit_programs.d \
./door.d \
./external_eeprom.d \
./i2c.d \
./lcd.d \
./led.d \
./mainCU.d \
./motor.d \
./timer.d \
./timer_pwm.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


