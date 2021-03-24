/*
 * debug.cpp
 *
 *  Created on: Mar 19, 2021
 *      Author: LY3FF
 */

#include <Arduino.h>
#include "config.h"

#ifdef DEBUG_MODE
# include <SendOnlySoftwareSerial.h>
# include <Wire.h>
extern SendOnlySoftwareSerial debugPort;
extern int board_temperature;
extern int board_voltage_mv;

#endif

#ifdef DEBUG_MODE

//long readVcc() {
//  long result;
//  // Read 1.1V reference against AVcc
//  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
//  delay(2); // Wait for Vref to settle
//  ADCSRA |= _BV(ADSC); // Convert
//  while (bit_is_set(ADCSRA,ADSC));
//  result = ADCL;
//  result |= ADCH<<8;
//  result = 1125300L / result; // Back-calculate AVcc in mV
//  return result;
//}
//
//void debugReadBoardSensors(){
//	  int wADC = 0;
////	  int board_temperature = 0;
////	  float volt = 0;
////	  int sensorVolt = 0;
//	  ADMUX = (_BV(REFS1) | _BV(REFS0) | _BV(MUX3));
//	  ADCSRA |= _BV(ADEN);
//	  delay(20);
//	  for (int i=0;i<5;i++)
//	  {
//	    ADCSRA |= _BV(ADSC);
//	    while (bit_is_set(ADCSRA, ADSC));
//	    wADC = wADC + ADCW;
//	    delay(20);
//	  }
//
//	  wADC = wADC / 5;
//	  board_temperature = (wADC - 304.21 ) / 1.124;
//	  board_voltage_mv = readVcc();
//}

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
