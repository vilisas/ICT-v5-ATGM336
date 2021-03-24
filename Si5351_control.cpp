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

extern Si5351 si5351;
bool ptt_is_on = 0;

void PTT_on(unsigned long frequency_hz){
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
void PTT_off(){
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

void tone_on() // Turn on the high-side switch, activating the transmitter
{
	if (!ptt_is_on) return;
	  si5351.output_enable(SI5351_CLK0, 1);  // Disable the clock initially

}

void tone_off() // Turn off the high-side switch
{
	if (!ptt_is_on) return;
	  si5351.output_enable(SI5351_CLK0, 0);  // Disable the clock initially
}

