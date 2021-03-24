/*
 * config.h
 *
 *  Created on: Mar 18, 2021
 *      Author: LY3FF
 */

#ifndef CONFIG_H_
#define CONFIG_H_
#include "local_config.h"


#ifndef CONFIG_CALLSIGN
#define CONFIG_CALLSIGN "N0CALL" // set your callsign in local_config.h file
#endif

//#define WSPR_CTC_SET 5336 // CTC value for WSPR - 10672 @ 16Mhz //5336 @ 8Mhz //2668 @ 4Mhz //1334 @ 2Mhz //667 @ 1Mhz
//
//// required TX length (seconds)
//#define WSPR_TX_LENGTH		110		// 110.6
//// measured TX length (seconds)
//#define WSPR_TX_LENGTH_MEASURED	110
//
//#define WSPR_TX_LENGTH_DIFF_PCT (WSPR_TX_LENGTH_MEASURED / WSPR_TX_LENGTH)
////time_diff_pct = time_measured / time_req
//
//#define WSPR_ADJUSTED_CTC WSPR_CTC_SET + ((WSPR_CTC_SET / 100) * WSPR_TX_LENGTH_DIFF_PCT) - (1/WSPR_CTC_SET)    // 5388


/*
 * WSPR_CTC korekcija:
 * Turima default reiksme: 5336 prie 8 MHz
 * WSPR paketo TX trukme: 110 sek - 1:50
 *
 * ziurim i debug arba radija ir ismatuojam laika nuo tx pradzios iki pabaigos su isoriniu sekundometru
 * gaunam pvz 1:48  = 108 sekundes - per greitai issiuncia paketa!
 * 108 / 110 ~= 0.98(18) %   - tiek reikia pailginti tx trukme, tuo paciu ir simbolio trukme
 * 5336 + 0.9818% ~= 5388
 *
 * 5336 + 0,976491862568 % = 5388
 *
 */
//#define WSPR_CTC                5336   // CTC value for WSPR - 10672 @ 16Mhz //5336 @ 8Mhz //2668 @ 4Mhz //1334 @ 2Mhz //667 @ 1Mhz
#define WSPR_CTC				5388  // 	korekcija: 0,976491862568%
#define WSPR_TONE_SPACING       146    // 146 ~1.46 Hz

#define WSPR_FREQ_OFFSET 2111UL

//#define WSPR_FREQ     7040185UL
//#define WSPR_FREQ     10140285UL
#define WSPR_FREQ     (WSPR_FREQ_OFFSET + 14097192UL)      // <<<<< SET TX FREQUENCY HERE


#ifdef DEBUG_MODE
# define PIN_SOFTSERIAL_TX 11 // PIN_SPI_MOSI
# ifndef DEBUG_BAUDRATE
#  define DEBUG_BAUDRATE 9600
# endif

// For testing purposes you can ignore gps fix. Locator and timing will be wrong,
// because of incorrect (unknown) location and time.
//#define IGNORE_GPS_FIX
#endif

// debug wspr routines, print symbol timing
//#define DEBUG_WSPR 1

// uncomment this to enable TX every 2 mins (test timing) or define it in local_config.h
//#define USE_TEST_TIMING 1

// waterfall painting parameters
#define PAINT_REPEAT_TIMES 4
#define PAINT_BIT_DELAY  (2500 / PAINT_REPEAT_TIMES)
#define PAINT_BIT_WIDTH 200



#endif /* CONFIG_H_ */
