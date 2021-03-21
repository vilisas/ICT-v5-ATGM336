################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include libraries/Wire/src/utility/subdir.mk
-include libraries/Wire/src/subdir.mk
-include libraries/TinyGPSPlus-1.0.2/src/subdir.mk
-include libraries/Time-master/subdir.mk
-include libraries/Sodaq_wdt/src/subdir.mk
-include libraries/SendOnlySoftwareSerial/subdir.mk
-include libraries/JTEncode-master/src/subdir.mk
-include libraries/Etherkit_Si5351-2.1.4/src/subdir.mk
-include core/core/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
/home/vilisas/balionai/LKB-4/ICT-v5-ATGM336/Release/arduino.ar \

ELF += \
LKB4.elf \

HEX += \
LKB4.hex \


# All Target
all: LKB4

# Tool invocations
LKB4: $(HEX)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"/opt/eclipse//arduinoPlugin/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/bin/avr-size" -A "/home/vilisas/balionai/LKB-4/ICT-v5-ATGM336/Release/LKB4.elf"
	@echo 'Finished building target: $@'
	@echo ' '

/home/vilisas/balionai/LKB-4/ICT-v5-ATGM336/Release/arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"/opt/eclipse//arduinoPlugin/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/bin/avr-gcc-ar" rcs     /home/vilisas/balionai/LKB-4/ICT-v5-ATGM336/Release/arduino.ar $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

LKB4.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"/opt/eclipse//arduinoPlugin/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/bin/avr-gcc" -Wall -Wextra -Os -g -flto -fuse-linker-plugin -Wl,--gc-sections -mmcu=atmega328p   -o "/home/vilisas/balionai/LKB-4/ICT-v5-ATGM336/Release/LKB4.elf"   $(LINK_OBJ)    /home/vilisas/balionai/LKB-4/ICT-v5-ATGM336/Release/arduino.ar  "-L/home/vilisas/balionai/LKB-4/ICT-v5-ATGM336/Release" -lm
	@echo 'Finished building: $@'
	@echo ' '

LKB4.hex: $(ELF)
	@echo 'Do all objcopy commands'
	"/opt/eclipse//arduinoPlugin/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/bin/avr-objcopy" -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0  "/home/vilisas/balionai/LKB-4/ICT-v5-ATGM336/Release/LKB4.elf" "/home/vilisas/balionai/LKB-4/ICT-v5-ATGM336/Release/LKB4.eep"
	"/opt/eclipse//arduinoPlugin/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/bin/avr-objcopy" -O ihex -R .eeprom  "/home/vilisas/balionai/LKB-4/ICT-v5-ATGM336/Release/LKB4.elf" "/home/vilisas/balionai/LKB-4/ICT-v5-ATGM336/Release/LKB4.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(PDE_DEPS)$(C_DEPS)$(AR)$(CC_DEPS)$(AR_OBJ)$(C++_DEPS)$(LINK_OBJ)$(CXX_DEPS)$(ASM_DEPS)$(HEX)$(INO_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(ELF)$(CPP_DEPS)
	-@echo ' '

.PHONY: all clean dependents

-include ../makefile.targets
