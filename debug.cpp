/*
 * debug.cpp
 *
 *  Created on: Mar 19, 2021
 *      Author: LY3FF
 */

#include <Arduino.h>
#include "config.h"
#include "debug.h"
#ifdef DEBUG_MODE
# include <SendOnlySoftwareSerial.h>
# include <Wire.h>
# include "Sodaq_wdt.h"
# include "Si5351_control.h"

extern SendOnlySoftwareSerial debugPort;

#endif

void debugI2CScanner()
{
#ifdef DEBUG_MODE
  byte error, address;
  int nDevices;
  digitalWrite(2, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  delay(100);

  debugPort.println(F("Scanning I2C devices..."));

  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
//  	debugPort.println(address);

    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
    	debugPort.print(F("I2C device found at address 0x"));
      if (address<16)
        debugPort.print("0");
      debugPort.print(address,HEX);
      debugPort.println("  !");

      nDevices++;
    }
    else if (error==4)
    {
    	debugPort.print(F("Unknown error at address 0x"));
      if (address<16)
    	  debugPort.print("0");
      debugPort.println(address,HEX);
    }
  }
  if (nDevices == 0)
	  debugPort.println(F("No I2C devices found"));
  else
	  debugPort.println(F("done"));

  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);

#endif
}

void testCW() {
#ifdef DEBUG_MODE
	unsigned long freq = WSPR_FREQ - 10000;
	set_PTT_on(freq);
	set_tone_on();

	sodaq_wdt_reset();
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 3000; i += 10) {
			set_tx_frequency(freq + i);
			delay(2);
		}
		sodaq_wdt_reset();
		for (int i = 3000; i > 0; i -= 10) {
			set_tx_frequency(freq + i);
			delay(2);
		}
		sodaq_wdt_reset();

	}
	set_tone_off();
	set_PTT_off();

#endif
}
