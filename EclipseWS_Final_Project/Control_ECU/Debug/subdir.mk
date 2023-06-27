################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DC_motor.c \
../E24c16.c \
../buzzer.c \
../gpio.c \
../i2c.c \
../main.c \
../main_Functions.c \
../timer1.c \
../uart.c 

OBJS += \
./DC_motor.o \
./E24c16.o \
./buzzer.o \
./gpio.o \
./i2c.o \
./main.o \
./main_Functions.o \
./timer1.o \
./uart.o 

C_DEPS += \
./DC_motor.d \
./E24c16.d \
./buzzer.d \
./gpio.d \
./i2c.d \
./main.d \
./main_Functions.d \
./timer1.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


