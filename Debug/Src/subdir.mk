################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/buzzer_task.c \
../Src/freertos.c \
../Src/main.c \
../Src/stm32f3xx_hal_msp.c \
../Src/stm32f3xx_it.c \
../Src/syscalls.c \
../Src/system_stm32f3xx.c 

OBJS += \
./Src/buzzer_task.o \
./Src/freertos.o \
./Src/main.o \
./Src/stm32f3xx_hal_msp.o \
./Src/stm32f3xx_it.o \
./Src/syscalls.o \
./Src/system_stm32f3xx.o 

C_DEPS += \
./Src/buzzer_task.d \
./Src/freertos.d \
./Src/main.d \
./Src/stm32f3xx_hal_msp.d \
./Src/stm32f3xx_it.d \
./Src/syscalls.d \
./Src/system_stm32f3xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DUSE_HAL_DRIVER -DSTM32F303xC -I"/Users/clementfeeser/Documents/workspace/quizzbox/Inc" -I"/Users/clementfeeser/Documents/workspace/quizzbox/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy" -I"/Users/clementfeeser/Documents/workspace/quizzbox/Drivers/STM32F3xx_HAL_Driver/Inc" -I"/Users/clementfeeser/Documents/workspace/quizzbox/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/clementfeeser/Documents/workspace/quizzbox/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/clementfeeser/Documents/workspace/quizzbox/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/clementfeeser/Documents/workspace/quizzbox/Drivers/CMSIS/Device/ST/STM32F3xx/Include" -I"/Users/clementfeeser/Documents/workspace/quizzbox/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


