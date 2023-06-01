################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/spirit1/radio_target.c 

OBJS += \
./Drivers/BSP/Components/spirit1/radio_target.o 

C_DEPS += \
./Drivers/BSP/Components/spirit1/radio_target.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/spirit1/%.o Drivers/BSP/Components/spirit1/%.su Drivers/BSP/Components/spirit1/%.cyclo: ../Drivers/BSP/Components/spirit1/%.c Drivers/BSP/Components/spirit1/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I"/Users/eduardomunoz/Library/CloudStorage/OneDrive-CalPoly/college/Spring 2023/RTOS/assignment07_cpe439/Drivers/BSP/Components/spirit1" -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-spirit1

clean-Drivers-2f-BSP-2f-Components-2f-spirit1:
	-$(RM) ./Drivers/BSP/Components/spirit1/radio_target.cyclo ./Drivers/BSP/Components/spirit1/radio_target.d ./Drivers/BSP/Components/spirit1/radio_target.o ./Drivers/BSP/Components/spirit1/radio_target.su

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-spirit1

