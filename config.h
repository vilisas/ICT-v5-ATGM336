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

#define WSPR_CTC                5336   // CTC value for WSPR - 10672 @ 16Mhz //5336 @ 8Mhz //2668 @ 4Mhz //1334 @ 2Mhz //667 @ 1Mhz
#define WSPR_TONE_SPACING       146    // 146 ~1.46 Hz

//#define WSPR_FREQ     7040185UL
//#define WSPR_FREQ     10140285UL
#define WSPR_FREQ     14097192UL      // <<<<< SET TX FREQUENCY HERE


#endif /* CONFIG_H_ */
