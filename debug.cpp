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

#endif

void debug(const String &tekstas) {
#ifdef DEBUG_MODE
	debugPort.println(tekstas);
#endif

}

