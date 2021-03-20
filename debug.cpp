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
extern SendOnlySoftwareSerial debugPort;
extern int board_temperature;
extern int board_voltage_mv;

#endif

void debug(const String &tekstas) {
#ifdef DEBUG_MODE
	debugPort.println(tekstas);
#endif
}
#ifdef DEBUG_MODE
void debugReadBoardSensors(){
	  int wADC = 0;
//	  int board_temperature = 0;
	  float volt = 0;
	  int sensorVolt = 0;
	  ADMUX = (_BV(REFS1) | _BV(REFS0) | _BV(MUX3));
	  ADCSRA |= _BV(ADEN);
	  delay(20);
	  for (int i=0;i<5;i++)
	  {
	    ADCSRA |= _BV(ADSC);
	    while (bit_is_set(ADCSRA, ADSC));
	    wADC = wADC + ADCW;
	    delay(20);
	  }

	  wADC = wADC / 5;
	  board_temperature = (wADC - 304.21 ) / 1.124;
	  delay(20);
	  analogReference(INTERNAL);
	  for (int i=0;i<5;i++)
	  {
	    sensorVolt = sensorVolt + analogRead(3); //analogRead(0) for the old boards
	  }
//	  sensorVolt = sensorVolt / 5;
	  volt = (sensorVolt / 5.0) * 1.1f;
	  volt = volt / 1023.0f;
	  volt = volt * 4.18f;
	  board_voltage_mv = volt * 100;
}

#endif


