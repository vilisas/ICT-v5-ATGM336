#include <TinyGPS++.h>
#include <TimeLib.h>
#include "TelemFunctions.h"
#include "config.h"
#include "debug.h"
#include "Si5351_control.h"

extern unsigned long freq;
extern bool telemetry_set;

#ifdef DEBUG_MODE
#include "SendOnlySoftwareSerial.h"
extern SendOnlySoftwareSerial debugPort;

unsigned long start_time;
unsigned long ms;

#endif

#ifndef USE_TEST_TIMING

void sendStandardWSPRMessage() {
#ifdef DEBUG_MODE
	debugPort.println(F("Sending WSPR msg"));
#endif
	telemetry_set = true;
	loc4calc(); 		// Get position and update 4-char locator, 6-char locator and last 2 chars of 8-char locator
	call_telem(); 		// Update WSPR telemetry callsign based on previous information : position and altitude in meters
	loc_dbm_telem();	// Update WSPR telemetry locator and dbm. Get temperature, voltage, speed in knots, GPS status and sats number
//      debugPort.println(F("Turning GPS OFF"));
	GPS_VCC_off();
	delay(10);
//      debugPort.println(F("Turning RF ON"));
	rf_on();
	freq = WSPR_FREQ;
	setModeWSPR(); 		// set WSPR standard mode
	encode(); // begin radio transmission
//      debugPort.println(F("Turning RF OFF"));
	rf_off();
	delay(5);
//      debugPort.println(F("Turning GPS ON"));
	GPS_VCC_on();
}

void sendTelemetryWSPRMessage() {
#ifdef DEBUG_MODE
	debugPort.println(F("Sending WSPR telemetry msg"));
#endif
//        debugPort.println(F("Turning GPS OFF"));
	GPS_VCC_off();
	delay(10);
	rf_on();
//      debugPort.println(F("Turning RF ON"));
	freq = WSPR_FREQ;
	setModeWSPR_telem(); 	// set WSPR telemetry mode
	encode(); 				// begin radio transmission
//      debugPort.println(F("Turning RF OFF"));
	rf_off();
	delay(5);
//      debugPort.println(F("Turning GPS ON"));
	GPS_VCC_on();

}


void TXtiming() // Timing
{
	// run additional scripts here to generate data prior to TX if there is a large delay involved.
	if ((timeStatus() == timeSet) && (second() == 0) && (minute() >= 0)) {
		setGPStime();
		if ((minute() % 10 == 0) && (second() <= 1)) // do not tx before new cycle (pos+telemetry)
				{
//			sendStandardWSPRMessage();
		}

		else if ((minute() % 10 == 2) && (second() <= 1)) // TX WSPR standard message
				{
			sendStandardWSPRMessage();
		}

		else if ((minute() % 10 == 4) && (second() <= 1))
				{
					if 	(telemetry_set == true){    		// TX WSPR telemetry message only if call sent at least once
						sendTelemetryWSPRMessage();
					} else {
						sendStandardWSPRMessage();			// and send standard msg if not
					}
		} else if ((minute() % 10 == 6) && (second() <= 1)) // TX WSPR standard message
				{
			if (minute() % 6 == 2) { // 26, 56 min expect easter eggs 10 kHz lower
				paint_picture(WSPR_FREQ - 10000);
			} else {
				sendStandardWSPRMessage();
			}
		} else if ((minute() % 10 == 8) && (second() <= 1)) // TX WSPR standard message
				{
			sendStandardWSPRMessage();
		}
	}
}
#else

// Timing2

void TXtiming() // Timing
{
	// run additional scripts here to generate data prior to TX if there is a large delay involved.
	if ((timeStatus() == timeSet) && (second() == 0) && (minute() >= 0)) {
#ifdef DEBUG_MODE
		start_time = millis();
#endif
		setGPStime();
		if ((minute() % 04 == 2) && (second() <= 2)) // TX WSPR standard message // 02, 06
				{
#ifdef DEBUG_MODE
			debugPort.println(F("Timing2. Sending standard WSPR message"));
#endif
			telemetry_set = true;
			loc4calc(); // Get position and update 4-char locator, 6-char locator and last 2 chars of 8-char locator
			call_telem(); // Update WSPR telemetry callsign based on previous information : position and altitude in meters
			loc_dbm_telem(); // Update WSPR telemetry locator and dbm. Get temperature, voltage, speed in knots, GPS status and sats number
//		      debugPort.println(F("Turning GPS OFF"));
		      GPS_VCC_off(); delay(10);
//		      debugPort.println(F("Turning RF ON"));
		      rf_on();
			freq = WSPR_FREQ;
			setModeWSPR(); // set WSPR standard mode
#ifdef DEBUG_MODE
			ms = millis();
#endif
			encode(); // begin radio transmission
//		      debugPort.println(F("Turning RF OFF"));
		      rf_off(); delay(5);
//		      debugPort.println(F("Turning GPS ON"));
		      GPS_VCC_on();
#ifdef DEBUG_MODE
			debugPort.print("Start time was: ");
			debugPort.println(ms - start_time);
#endif

		}
	}
}
#endif
