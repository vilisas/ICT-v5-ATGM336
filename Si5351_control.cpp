/*
 * Si5351_control.cpp
 *
 *  Created on: Mar 24, 2021
 *      Author: LY3FF
 */

#include <Arduino.h>
#include "config.h"
#include <si5351.h>
#include "Si5351_control.h"
#include "Sodaq_wdt.h"

#ifdef DEBUG_MODE
//#include "SendOnlySoftwareSerial.h"
//extern SendOnlySoftwareSerial debugPort;

#endif

extern Si5351 si5351;

//const unsigned int paint_data[] PROGMEM =  {
//		0b1111111111111111,
//		0b1000000000000001,
//		0b1000000000000001,
//		0b1000000000000001,
//		0b1000000000000001,
//		0b1000000000000001,
//		0b1000000000000001,
//		0b1000000000000001,
//		0b1000000000000001,
//		0b1000000000000001,
//		0b1000000000000001,
//		0b1000000000000001,
//		0b1000000000000001,
//		0b1000000000000001,
//		0b1000000000000001,
//		0b1111111111111111
//};


const unsigned int paint_data[] PROGMEM =  {
		0b0001111111100000,
		0b0110001000011000,
		0b1100000000001100,
		0b1100000000000110,
		0b1100000000000110,
		0b1100000000000110,
		0b1100000000000110,
		0b0110000000001100,
		0b0011000000011000,
		0b0001111001110000,
		0b0000011111000000,
		0b0000001100000000,
		0b0000011000000011,
		0b0000110000000110,
		0b0000011100001100,
		0b0000001111111000
};

const int paint_size = 16;

bool ptt_is_on = 0;

void set_PTT_on(unsigned long frequency_hz){
	  digitalWrite(2, HIGH);
	  digitalWrite(4, HIGH);
	  digitalWrite(5, HIGH);
	  digitalWrite(6, HIGH);
	  digitalWrite(7, HIGH);
	  delay(2);

	  si5351.init(SI5351_CRYSTAL_LOAD_0PF, 27000000, 0); // TCXO 27MHz
	  si5351.set_clock_pwr(SI5351_CLK1, 0);  // Turn off the CLK1 clock
	  si5351.output_enable(SI5351_CLK1, 0);  // Turn off the CLK1 output
	  si5351.set_clock_pwr(SI5351_CLK2, 0);  // Turn off the CLK2 clock
	  si5351.output_enable(SI5351_CLK2, 0);  // Turn off the CLK2 output
	  si5351.drive_strength(SI5351_CLK0, SI5351_DRIVE_8MA); // Set for max power if desired. Check datasheet.
	  si5351.set_freq((frequency_hz * 100),SI5351_CLK0);
	  si5351.output_enable(SI5351_CLK0, 0);  // Disable the clock initially

	  ptt_is_on = 1;

}
void set_PTT_off(){
	  digitalWrite(2, LOW);
	  digitalWrite(4, LOW);
	  digitalWrite(5, LOW);
	  digitalWrite(6, LOW);
	  digitalWrite(7, LOW);
	  ptt_is_on = 0;
}

void set_tx_frequency(unsigned long frequency_hz){
	if (!ptt_is_on) return;
	  si5351.set_freq((frequency_hz * 100),SI5351_CLK0);
}

void set_tone_on() // Turn on the high-side switch, activating the transmitter
{
	if (!ptt_is_on) return;
	  si5351.output_enable(SI5351_CLK0, 1);  // Disable the clock initially
}

void set_tone_off() // Turn off the high-side switch
{
	if (!ptt_is_on) return;
	  si5351.output_enable(SI5351_CLK0, 0);  // Disable the clock initially
}

void paint_picture(unsigned long frequency_hz) {
	unsigned int data;
	set_PTT_on(frequency_hz);
	for (int i = paint_size; i > 0; i--) {	// bottom to top
		sodaq_wdt_reset();
		data = pgm_read_word_near(paint_data + i-1);
//		debugPort.println(data);
		for (int times = 0; times < PAINT_REPEAT_TIMES; times++) {	// kiek kartu kartosim eilute
			for (int j = 16; j > 0; j--) {		// right to left
				if ((data) & (1 << (j-1))) {
					set_tx_frequency(frequency_hz + ((16-j) * PAINT_BIT_WIDTH));	// freq + (offset*step_size)
					set_tone_on();
					delayMicroseconds(PAINT_BIT_DELAY);// pixel time = ((1 / waterfall speed) / line_width_in_bits ) * repeat_times
				} else {
					set_tone_off();
					delayMicroseconds(PAINT_BIT_DELAY);
				}
			}
		}
	}
	set_tone_off();
	set_PTT_on(frequency_hz);

}

