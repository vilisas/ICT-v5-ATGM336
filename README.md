# ICT-v5-ATGM336
Ads support for WDT and switching on GPS only mode on the gps for powersaving

Ads support for WDT - Watch Dog Timer to prevent the program running in the 328 to freeze or lock up.          
Switching on GPS only mode on the gps for powersaving (BDS off), saves about 4-5mA 


## Configuration
Configuration should be done in local_config.h

Set valid callsign in local_config.h:
 #define CONFIG_CALLSIGN "N0CALL"

To enable test TX timing every 2 mins define next line in config:
 #define USE_TEST_TIMING 1

to enable debug output define DEBUG_MODE:
 #define DEBUG_MODE 1

when debug mode is enabled, it will print out some info via MOSI pin at 9600 BPS by default.
