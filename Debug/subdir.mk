################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../adc.c \
../dio.c \
../lcd.c \
../main.c \
../motor.c \
../temperature_sensor.c \
../timer.c 

OBJS += \
./adc.o \
./dio.o \
./lcd.o \
./main.o \
./motor.o \
./temperature_sensor.o \
./timer.o 

C_DEPS += \
./adc.d \
./dio.d \
./lcd.d \
./main.d \
./motor.d \
./temperature_sensor.d \
./timer.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


