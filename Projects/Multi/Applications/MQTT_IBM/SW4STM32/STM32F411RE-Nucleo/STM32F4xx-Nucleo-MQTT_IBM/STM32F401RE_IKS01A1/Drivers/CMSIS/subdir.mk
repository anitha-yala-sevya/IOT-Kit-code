################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Projects/Multi/Applications/MQTT_IBM/Src/system_stm32f4xx.c 

OBJS += \
./Drivers/CMSIS/system_stm32f4xx.o 

C_DEPS += \
./Drivers/CMSIS/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/system_stm32f4xx.o: C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Projects/Multi/Applications/MQTT_IBM/Src/system_stm32f4xx.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DUSE_HAL_DRIVER -DUSART_PRINT_MSG -DSTM32F401xE -DUSE_STM32F4XX_NUCLEO -D__IKS01A1 -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Projects/Multi/Applications/MQTT_IBM/Inc" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Drivers/BSP/STM32F4xx-Nucleo" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Drivers/CMSIS/Include" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Drivers/BSP/Components/Common" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Drivers/BSP/Components/hts221" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Drivers/BSP/Components/lis3mdl" -I../../../../../../../../Drivers/BSP/Components/lps25h -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Drivers/BSP/Components/lps25hb" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Drivers/BSP/Components/lsm6ds0" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Drivers/BSP/Components/lsm6ds3" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Drivers/BSP/Components/M24SR" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Drivers/BSP/X-NUCLEO-NFC01A1" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Drivers/BSP/X-NUCLEO-IDW01M1" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Middlewares/ST/lib_NDEF/inc" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Middlewares/ST/STM32_SPWF01SA/Inc" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Middlewares/ST/STM32_SPWF01SA/Utils" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Middlewares/Third_Parties/MQTT-Paho/MQTTClient-C/src" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Middlewares/Third_Parties/MQTT-Paho/MQTTPacket/src" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Middlewares/Third_Parties/MQTT-Paho/Utils" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Middlewares/Third_Parties/MQTT-Paho/Porting" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Drivers/BSP/Components/lps22hb" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Drivers/BSP/Components/lsm6dsl" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Drivers/BSP/Components/lsm303agr" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Drivers/BSP/X_NUCLEO_IKS01A1"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


