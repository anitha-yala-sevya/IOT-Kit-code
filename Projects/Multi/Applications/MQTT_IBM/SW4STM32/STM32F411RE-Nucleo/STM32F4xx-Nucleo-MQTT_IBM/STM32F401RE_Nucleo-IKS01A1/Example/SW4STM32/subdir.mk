################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
C:/Users/SevyaMM/Pictures/STM32CubeFGunctionPackWatson/Projects/Multi/Applications/MQTT_IBM/SW4STM32/STM32F411RE-Nucleo/startup_stm32f401xe.s 

OBJS += \
./Example/SW4STM32/startup_stm32f401xe.o 


# Each subdirectory must supply rules for building sources it contributes
Example/SW4STM32/startup_stm32f401xe.o: C:/Users/SevyaMM/Pictures/STM32CubeFGunctionPackWatson/Projects/Multi/Applications/MQTT_IBM/SW4STM32/STM32F411RE-Nucleo/startup_stm32f401xe.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -I../../../../Inc -I../../../../../../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../../../../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../../../../../../Drivers/BSP/STM32F4xx-Nucleo -I../../../../../../../../Drivers/CMSIS/Include -I../../../../../../../../Drivers/BSP/Components/Common -I../../../../../../../../Drivers/BSP/Components/hts221 -I../../../../../../../../Drivers/BSP/Components/lis3mdl -I../../../../../../../../Drivers/BSP/Components/lps25h -I../../../../../../../../Drivers/BSP/Components/lsm6ds0 -I../../../../../../../../Drivers/BSP/X_NUCLEO_IKS01A1 -I../../../../../../../../Drivers/BSP/Components/M24SR -I../../../../../../../../Drivers/BSP/X-NUCLEO-NFC01A1 -I../../../../../../../../Drivers/BSP/X-NUCLEO-IDW01M1 -I../../../../../../../../Middlewares/ST/lib_NDEF/inc -I../../../../../../../../Middlewares/ST/STM32_SPWF01SA/Inc -I../../../../../../../../Middlewares/ST/STM32_SPWF01SA/Utils -I../../../../../../../../Middlewares/Third_Parties/MQTT-Paho/MQTTClient-C/src -I../../../../../../../../Middlewares/Third_Parties/MQTT-Paho/MQTTPacket/src -I../../../../../../../../Middlewares/Third_Parties/MQTT-Paho/Utils -I../../../../../../../../Middlewares/Third_Parties/MQTT-Paho/Porting -I../../../../../../../../Drivers/BSP/Components/lps25hb -I../../../../../../../../Drivers/BSP/Components/lsm6ds3 -I../../../../../../../../Drivers/BSP/Components/lps22hb -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


