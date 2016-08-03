/*
 * ADCSW.H
 *
 *  Created on: 2016年7月31日
 *      Author: Romeli
 */

#ifndef ADCSW_H_
#define ADCSW_H_

typedef enum _ADCCH {
	ADC1 = 1, ADC2, ADC3, ADC4, ADC5, ADC6
} ADCCH;

void ADCSW_Init();
void ADCSW_Switch(ADCCH ch);

#endif /* ADCSW_H_ */
