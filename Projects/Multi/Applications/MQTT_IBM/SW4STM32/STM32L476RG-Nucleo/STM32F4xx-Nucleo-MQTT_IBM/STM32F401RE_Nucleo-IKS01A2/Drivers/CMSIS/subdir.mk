################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Projects/Multi/Applications/MQTT_IBM/Src/system_stm32l4xx.c 

OBJS += \
./Drivers/CMSIS/system_stm32l4xx.o 

C_DEPS += \
./Drivers/CMSIS/system_stm32l4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/system_stm32l4xx.o: C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Projects/Multi/Applications/MQTT_IBM/Src/system_stm32l4xx.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DUSE_HAL_DRIVER -DUSART_PRINT_MSG -DUSE_STM32L4XX_NUCLEO -DSTM32L4xx -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Projects/Multi/Applications/MQTT_IBM/Inc" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Drivers/STM32L4xx_HAL_Driver/Inc" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Drivers/BSP/STM32L4xx-Nucleo" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Drivers/BSP/Components/Common" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Drivers/BSP/Components/hts221" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Drivers/BSP/Components/lis3mdl" -I../../../../../../../../Drivers/BSP/Components/lps25h -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Drivers/BSP/Components/lps25hb" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Drivers/BSP/Components/lsm6ds0" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Drivers/BSP/Components/lsm6ds3" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Drivers/BSP/Components/M24SR" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Drivers/BSP/X-NUCLEO-NFC01A1" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Drivers/BSP/X-NUCLEO-IDW01M1" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Middlewares/ST/lib_NDEF/inc" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Middlewares/ST/STM32_SPWF01SA/Inc" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Middlewares/ST/STM32_SPWF01SA/Utils" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Middlewares/Third_Parties/MQTT-Paho/MQTTClient-C/src" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Middlewares/Third_Parties/MQTT-Paho/MQTTPacket/src" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Middlewares/Third_Parties/MQTT-Paho/Utils" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Middlewares/Third_Parties/MQTT-Paho/Porting" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Drivers/BSP/Components/lps22hb" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Drivers/BSP/Components/lsm6dsl" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Drivers/BSP/Components/lsm303agr" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Drivers/BSP/X_NUCLEO_IKS01A2" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Drivers/BSP/Components/iis2dh" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Middlewares/ST/FFT/inc" -I"C:/Users/Basha/Desktop/STM32CubeFGunctionPackWatson/Middlewares/Third_Parties/ARM/DSP/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


