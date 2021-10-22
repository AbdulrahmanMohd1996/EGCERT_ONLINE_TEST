################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/spi.c 

OBJS += \
./MCAL/spi.o 

C_DEPS += \
./MCAL/spi.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/%.o: ../MCAL/%.c MCAL/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\EclipseWorkSpaces\RTOS_EXC\EGCERT_MASTERMC" -I"D:\EclipseWorkSpaces\RTOS_EXC\EGCERT_MASTERMC\MCAL" -I"D:\EclipseWorkSpaces\RTOS_EXC\EGCERT_MASTERMC\RTOS" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


