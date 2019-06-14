################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include STM32F401RE_IKS01A1/Middlewares/Third_Parties/MQTT-Paho/Utils/subdir.mk
-include STM32F401RE_IKS01A1/Middlewares/Third_Parties/MQTT-Paho/Porting/subdir.mk
-include STM32F401RE_IKS01A1/Middlewares/Third_Parties/MQTT-Paho/MQTTPacket/subdir.mk
-include STM32F401RE_IKS01A1/Middlewares/Third_Parties/MQTT-Paho/MQTTClient-C/subdir.mk
-include STM32F401RE_IKS01A1/Middlewares/ST/lib_NDEF/subdir.mk
-include STM32F401RE_IKS01A1/Middlewares/ST/STM32_SPWF01SA/Utils/subdir.mk
-include STM32F401RE_IKS01A1/Middlewares/ST/STM32_SPWF01SA/subdir.mk
-include STM32F401RE_IKS01A1/Example/User/subdir.mk
-include STM32F401RE_IKS01A1/Example/SW4STM32/subdir.mk
-include STM32F401RE_IKS01A1/Drivers/STM32F4xx_HAL_Driver/subdir.mk
-include STM32F401RE_IKS01A1/Drivers/CMSIS/subdir.mk
-include STM32F401RE_IKS01A1/Drivers/BSP/X_NUCLEO_IKS01A2/subdir.mk
-include STM32F401RE_IKS01A1/Drivers/BSP/X-NUCLEO-NFC01A1/subdir.mk
-include STM32F401RE_IKS01A1/Drivers/BSP/X-NUCLEO-IDW01M1/subdir.mk
-include STM32F401RE_IKS01A1/Drivers/BSP/STM32F4xx-Nucleo/subdir.mk
-include STM32F401RE_IKS01A1/Drivers/BSP/Components/subdir.mk
-include Middlewares/Third_Parties/MQTT-Paho/Utils/subdir.mk
-include Middlewares/Third_Parties/MQTT-Paho/Porting/subdir.mk
-include Middlewares/Third_Parties/MQTT-Paho/MQTTPacket/subdir.mk
-include Middlewares/Third_Parties/MQTT-Paho/MQTTClient-C/subdir.mk
-include Middlewares/Third_Parties/ARM/DSP/subdir.mk
-include Middlewares/ST/lib_NDEF/subdir.mk
-include Middlewares/ST/STM32_SPWF01SA/Utils/subdir.mk
-include Middlewares/ST/STM32_SPWF01SA/subdir.mk
-include Middlewares/ST/FFT/subdir.mk
-include Example/User/subdir.mk
-include Example/SW4STM32/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/subdir.mk
-include Drivers/CMSIS/subdir.mk
-include Drivers/BSP/X_NUCLEO_IKS01A1/subdir.mk
-include Drivers/BSP/X-NUCLEO-NFC01A1/subdir.mk
-include Drivers/BSP/X-NUCLEO-IDW01M1/subdir.mk
-include Drivers/BSP/STM32F4xx-Nucleo/subdir.mk
-include Drivers/BSP/Components/subdir.mk
-include Doc/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: STM32F4xx-Nucleo-MQTT_IBM.elf

# Tool invocations
STM32F4xx-Nucleo-MQTT_IBM.elf: $(OBJS) $(USER_OBJS) ../LinkerScript.ld
	@echo 'Building target: $@'
	@echo 'Invoking: MCU GCC Linker'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -specs=nano.specs -T"../LinkerScript.ld" -Wl,-Map=output.map -Wl,--gc-sections -o "STM32F4xx-Nucleo-MQTT_IBM.elf" @"objects.list" $(USER_OBJS) $(LIBS) -lm
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

post-build:
	-@echo 'Generating binary:'
	arm-none-eabi-objcopy -O ihex "STM32F4xx-Nucleo-MQTT_IBM.elf" "STM32F4xx-Nucleo-MQTT_IBM.hex"
	arm-none-eabi-size "STM32F4xx-Nucleo-MQTT_IBM.elf"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
