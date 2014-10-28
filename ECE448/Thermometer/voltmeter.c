/* ADC Voltmeter
* Continuously outputs voltage over the serial line.
*/

// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>                           /* for ADC sleep mode */
#include <math.h>                           /* for round() and floor() */
#include <stdio.h>

#include "pinDefines.h"
#include "USART.h"

/* Note: This voltmeter is only as accurate as your reference voltage.
* If you want four digits of accuracy, need to measure your AVCC well.
* Measure either AVCC of the voltage on AREF and enter it here.
*/
#define REF_VCC 1.1

#define VOLTAGE_DIV_RES 10000


// -------- Functions --------- //
void initADC(int n) {
	switch(n) {
		case 0x0:
			ADMUX = 0b00000011;                     /* set mux to ADC3 */
			break;
		case 0x1:
			ADMUX = 0b00000010;                      /* set mux to ADC2 */
			break;
	}
	//ADMUX |= (0b00001111 & PC3);                      /* set mux to ADC5 */
	ADMUX |= (1 << REFS1) | (1 << REFS0);                  /* set reference voltage to internal 1.1v */
	ADCSRA |= (1 << ADPS1) | (1 << ADPS2);    /* ADC clock prescaler /64 */
	ADCSRA |= (1 << ADEN);                                 /* enable ADC */
}

void setupADCSleepmode(void) {
	set_sleep_mode(SLEEP_MODE_ADC);            /* defined in avr/sleep.h */
	ADCSRA |= (1 << ADIE);                       /* enable ADC interrupt */
	sei();                                   /* enable global interrupts */
}

EMPTY_INTERRUPT(ADC_vect);

uint16_t oversample16x(void) {
	uint16_t oversampledValue = 0;
	uint8_t i;
	for (i = 0; i < 16; i++) {
		sleep_mode();                   /* chip to sleep, takes ADC sample */
		oversampledValue += ADC;                        /* add them up 16x */
	}
	return (oversampledValue >> 2);          /* divide back down by four */
}

void printFloat(float voltage) {
	float number = voltage/4;
	//transmitByte('0' + floor(10*((number/100000)-floor(number/100000))));
	transmitByte('0' + floor(10*((number/10000)-floor(number/10000))));
	transmitByte('0' + floor(10*((number/1000)-floor(number/1000))));
	transmitByte('0' + floor(10*((number/100)-floor(number/100))));
	transmitByte('0' + ((number/10) - floor(number/10))*10);
	transmitByte('.');
	transmitByte('0' + floor(10*((number-floor(number)))));
	printString("\r\n");
}

void printVoltage(float voltage) {
	float number = (voltage/4) * (REF_VCC/1023);
	transmitByte('0' + ((number/10) - floor(number/10))*10);
	transmitByte('.');
	transmitByte('0' + floor(10*((number-floor(number)))));
	transmitByte('0' + floor(10*(((number*10)-floor(number*10)))));
	transmitByte('0' + floor(10*(((number*100)-floor(number*100)))));
	transmitByte('0' + floor(10*(((number*1000)-floor(number*1000)))));
	printString("\r\n");
}

float printThermRes(float voltage) {
	voltage = (voltage/4) * (REF_VCC/1023);
	float R_T = (REF_VCC/voltage)*(VOLTAGE_DIV_RES-((voltage*VOLTAGE_DIV_RES)/REF_VCC));
	float number = R_T;
	transmitByte('0' + floor(10*((number/100000)-floor(number/100000))));
	transmitByte('0' + floor(10*((number/10000)-floor(number/10000))));
	transmitByte('0' + floor(10*((number/1000)-floor(number/1000))));
	transmitByte('0' + floor(10*((number/100)-floor(number/100))));
	transmitByte('0' + ((number/10) - floor(number/10))*10);
	transmitByte('.');
	transmitByte('0' + floor(10*((number-floor(number)))));
	printString("\r\n");
	return R_T;
}

void printTemp(float R_T) {
	float T_0 = 298.15;
	float B = 3977;
	float R_0 = 10000;
	float temp = 1/(1/T_0 + (1/B)*log(R_T/R_0));
	
	temp = temp - 273.15;
	float number = temp;
	
	//Celsius
	transmitByte('0' + floor(10*((number/100)-floor(number/100))));
	transmitByte('0' + ((number/10) - floor(number/10))*10);
	transmitByte('.');
	transmitByte('0' + floor(10*((number-floor(number)))));
	transmitByte('0' + floor(10*(((number*10)-floor(number*10)))));
	transmitByte('0' + floor(10*(((number*100)-floor(number*100)))));
	printString(" C\r\n");
	
	number = (1.8*temp + 32);
	//Fahrenheit
	transmitByte('0' + floor(10*((number/100)-floor(number/100))));
	transmitByte('0' + ((number/10) - floor(number/10))*10);
	transmitByte('.');
	transmitByte('0' + floor(10*((number-floor(number)))));
	transmitByte('0' + floor(10*(((number*10)-floor(number*10)))));
	transmitByte('0' + floor(10*(((number*100)-floor(number*100)))));
	printString(" F\r\n");
	
}

int main(void) {

	float voltage1;
	float voltage2;
	float res1;
	float res2;
	// -------- Inits --------- //
	initUSART();
	setupADCSleepmode();
	printString("\r\nDigital Voltmeter\r\n\r\n");
	

	// ------ Event loop ------ //
  
	while (1) {

		initADC(0);
		voltage1 = oversample16x();
		printString("Thermistor 1:\r\n");
		printFloat(voltage1);
		//printVoltage(voltage1);
		//res1 = printThermRes(voltage1);
		//printTemp(res1);
		printString("\r\n");
		
		_delay_ms(100);

		initADC(1);
		voltage2 = oversample16x();
		printString("Thermistor 2:\r\n");
		printFloat(voltage2);
		//printVoltage(voltage2);
		//res2 = printThermRes(voltage2);
		//printTemp(res2);
		printString("\r\n");
		_delay_ms(500);
		
	}                                                  /* End event loop */
	return (0);                            /* This line is never reached */
}
