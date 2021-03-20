#include <TinyGPS++.h>
#include <TimeLib.h>
#include "TelemFunctions.h"
#include "config.h"
#include "debug.h"
extern unsigned long freq;
extern bool telemetry_set;


#ifndef USE_TEST_TIMING

void TXtiming() // Timing
    {
    // run additional scripts here to generate data prior to TX if there is a large delay involved.
    if ((timeStatus() == timeSet) && (second() == 0) && (minute() >= 0)) 
    {
    setGPStime();
    if ((minute() % 10 == 0) && (second() <= 0)) // TX WSPR standard message
    {
    	debug(F("Sending standard WSPR message #1"));
      telemetry_set = true;
      loc4calc(); // Get position and update 4-char locator, 6-char locator and last 2 chars of 8-char locator
      call_telem(); // Update WSPR telemetry callsign based on previous information : position and altitude in meters
      loc_dbm_telem(); // Update WSPR telemetry locator and dbm. Get temperature, voltage, speed in knots, GPS status and sats number
//      debug(F("Turning GPS OFF"));
      GPS_VCC_off(); delay(10);
//      debug(F("Turning RF ON"));
      rf_on();
      freq = WSPR_FREQ;
      setModeWSPR(); // set WSPR standard mode
      encode(); // begin radio transmission
//      debug(F("Turning RF OFF"));
      rf_off(); delay(5);
//      debug(F("Turning GPS ON"));
      GPS_VCC_on();
    }
    
    else if ((minute() % 10 == 2) && (second() <= 0) && (telemetry_set == true))    // TX WSPR telemetry message
    {
    	debug(F("Sending WSPR telemetry message"));
//        debug(F("Turning GPS OFF"));
      GPS_VCC_off(); delay(10); 
      rf_on();
//      debug(F("Turning RF ON"));
      freq = WSPR_FREQ;
      setModeWSPR_telem(); // set WSPR telemetry mode
      encode(); // begin radio transmission
//      debug(F("Turning RF OFF"));
      rf_off(); delay(5);
//      debug(F("Turning GPS ON"));
      GPS_VCC_on();
    }
    
    else if ((minute() % 10 == 4) && (second() <= 0) && (telemetry_set == true))    // TX WSPR standard message
    {
    	debug(F("Sending standard WSPR message #2"));
//        debug(F("Turning GPS OFF"));
        GPS_VCC_off(); delay(10);
//        debug(F("Turning RF ON"));
        rf_on();
      freq = WSPR_FREQ;
      setModeWSPR(); // set WSPR standard mode
      encode(); // begin radio transmission
//      debug(F("Turning RF OFF"));
      rf_off(); delay(5);
//      debug(F("Turning GPS ON"));
      GPS_VCC_on();
    }
    
    else if ((minute() % 10 == 6) && (second() <= 0) && (telemetry_set == true))    // TX WSPR standard message
    {
    	debug(F("Sending standard WSPR message #3"));
//        debug(F("Turning GPS OFF"));
        GPS_VCC_off(); delay(10);
//        debug(F("Turning RF ON"));
        rf_on();
      freq = WSPR_FREQ;
      setModeWSPR(); // set WSPR standard mode
      encode(); // begin radio transmission
//      debug(F("Turning RF OFF"));
      rf_off(); delay(5);
//      debug(F("Turning GPS ON"));
      GPS_VCC_on();
      telemetry_set = false;
    }
    }
    }
#else

// Timing2

void TXtiming() // Timing
{
	// run additional scripts here to generate data prior to TX if there is a large delay involved.
	if ((timeStatus() == timeSet) && (second() == 0) && (minute() >= 0)) {
		setGPStime();
		if ((minute() % 02 == 0) && (second() <= 2)) // TX WSPR standard message
				{
	    	debug(F("Timing2. Sending standard WSPR message"));
			telemetry_set = true;
			loc4calc(); // Get position and update 4-char locator, 6-char locator and last 2 chars of 8-char locator
			call_telem(); // Update WSPR telemetry callsign based on previous information : position and altitude in meters
			loc_dbm_telem(); // Update WSPR telemetry locator and dbm. Get temperature, voltage, speed in knots, GPS status and sats number
//		      debug(F("Turning GPS OFF"));
		      GPS_VCC_off(); delay(10);
//		      debug(F("Turning RF ON"));
		      rf_on();
			freq = WSPR_FREQ;
			setModeWSPR(); // set WSPR standard mode
			encode(); // begin radio transmission
//		      debug(F("Turning RF OFF"));
		      rf_off(); delay(5);
//		      debug(F("Turning GPS ON"));
		      GPS_VCC_on();
		}
	}
}

#endif
