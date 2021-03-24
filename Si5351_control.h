/*
 * Si5351_control.h
 *
 *  Created on: Mar 24, 2021
 *      Author: vilisas
 */

#ifndef SI5351_CONTROL_H_
#define SI5351_CONTROL_H_

void set_tone_on();
void set_tone_off();
void set_PTT_on(unsigned long frequency_hz);
void set_PTT_off();
void set_tx_frequency(unsigned long frequency_hz);
void paint_picture(unsigned long frequency_hz);




#endif /* SI5351_CONTROL_H_ */
