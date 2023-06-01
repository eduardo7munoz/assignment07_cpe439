################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Aes.c \
../Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Calibration.c \
../Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Commands.c \
../Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Csma.c \
../Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_DirectRF.c \
../Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_General.c \
../Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Gpio.c \
../Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Irq.c \
../Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_LinearFifo.c \
../Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Management.c \
../Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_PktBasic.c \
../Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_PktCommon.c \
../Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_PktMbus.c \
../Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_PktStack.c \
../Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Qi.c \
../Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Radio.c \
../Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Timer.c \
../Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Types.c 

OBJS += \
./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Aes.o \
./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Calibration.o \
./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Commands.o \
./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Csma.o \
./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_DirectRF.o \
./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_General.o \
./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Gpio.o \
./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Irq.o \
./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_LinearFifo.o \
./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Management.o \
./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_PktBasic.o \
./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_PktCommon.o \
./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_PktMbus.o \
./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_PktStack.o \
./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Qi.o \
./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Radio.o \
./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Timer.o \
./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Types.o 

C_DEPS += \
./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Aes.d \
./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Calibration.d \
./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Commands.d \
./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Csma.d \
./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_DirectRF.d \
./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_General.d \
./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Gpio.d \
./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Irq.d \
./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_LinearFifo.d \
./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Management.d \
./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_PktBasic.d \
./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_PktCommon.d \
./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_PktMbus.d \
./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_PktStack.d \
./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Qi.d \
./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Radio.d \
./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Timer.d \
./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Types.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/%.o Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/%.su Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/%.cyclo: ../Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/%.c Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"/Users/eduardomunoz/Library/CloudStorage/OneDrive-CalPoly/college/Spring 2023/RTOS/assignment07_cpe439/Drivers/BSP/Components/spirit1/SPIRIT1_Library/Inc" -I"/Users/eduardomunoz/Library/CloudStorage/OneDrive-CalPoly/college/Spring 2023/RTOS/assignment07_cpe439/Drivers/BSP/Components/spirit1" -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-spirit1-2f-SPIRIT1_Library-2f-Src

clean-Drivers-2f-BSP-2f-Components-2f-spirit1-2f-SPIRIT1_Library-2f-Src:
	-$(RM) ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Aes.cyclo ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Aes.d ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Aes.o ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Aes.su ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Calibration.cyclo ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Calibration.d ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Calibration.o ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Calibration.su ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Commands.cyclo ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Commands.d ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Commands.o ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Commands.su ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Csma.cyclo ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Csma.d ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Csma.o ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Csma.su ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_DirectRF.cyclo ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_DirectRF.d ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_DirectRF.o ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_DirectRF.su ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_General.cyclo ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_General.d ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_General.o ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_General.su ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Gpio.cyclo ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Gpio.d ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Gpio.o ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Gpio.su ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Irq.cyclo ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Irq.d ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Irq.o ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Irq.su ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_LinearFifo.cyclo ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_LinearFifo.d ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_LinearFifo.o ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_LinearFifo.su ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Management.cyclo ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Management.d ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Management.o ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Management.su ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_PktBasic.cyclo ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_PktBasic.d ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_PktBasic.o ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_PktBasic.su ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_PktCommon.cyclo ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_PktCommon.d ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_PktCommon.o ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_PktCommon.su ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_PktMbus.cyclo ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_PktMbus.d ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_PktMbus.o ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_PktMbus.su ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_PktStack.cyclo ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_PktStack.d ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_PktStack.o ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_PktStack.su ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Qi.cyclo ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Qi.d ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Qi.o ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Qi.su ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Radio.cyclo ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Radio.d ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Radio.o ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Radio.su ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Timer.cyclo ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Timer.d ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Timer.o ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Timer.su ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Types.cyclo ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Types.d ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Types.o ./Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/SPIRIT_Types.su

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-spirit1-2f-SPIRIT1_Library-2f-Src

