################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/opt/Arduino/libraries/SendOnlySoftwareSerial/SendOnlySoftwareSerial.cpp 

LINK_OBJ += \
./libraries/SendOnlySoftwareSerial/SendOnlySoftwareSerial.cpp.o 

CPP_DEPS += \
./libraries/SendOnlySoftwareSerial/SendOnlySoftwareSerial.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/SendOnlySoftwareSerial/SendOnlySoftwareSerial.cpp.o: /opt/Arduino/libraries/SendOnlySoftwareSerial/SendOnlySoftwareSerial.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/opt/eclipse//arduinoPlugin/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega328p -DF_CPU=8000000L -DARDUINO=10812 -DARDUINO_AVR_PRO -DARDUINO_ARCH_AVR     -I"/opt/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.8.3/cores/arduino" -I"/opt/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.8.3/variants/eightanaloginputs" -I"/opt/eclipse/arduinoPlugin/libraries/Sodaq_wdt/1.0.2/src" -I"/opt/Arduino/libraries/TinyGPSPlus-1.0.2/src" -I"/opt/Arduino/libraries/JTEncode-master/src" -I"/opt/Arduino/libraries/Time-master" -I"/opt/Arduino/libraries/SendOnlySoftwareSerial" -I"/opt/Arduino/libraries/Etherkit_Si5351-2.1.4/src" -I"/opt/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.8.3/libraries/Wire/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -D__IN_ECLIPSE__=1 -x c++ "$<"   -o "$@"
	@echo 'Finished building: $<'
	@echo ' '


