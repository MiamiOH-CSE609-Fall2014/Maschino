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
/* measured division by voltage divider */
#define VOLTAGE_DIV_FACTOR  1


// -------- Functions --------- //
void initADC(void) {
	ADMUX |= (0b00001111 & PC5);                      /* set mux to ADC5 */
	ADMUX |= (1 << REFS0);                  /* reference voltage on AVCC */
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
	return (oversampledValue >> 3);          /* divide back down by four */
}

void printFloat(float number) {
	number = round(number * 100) / 100; /* round off to 2 decimal places */
	transmitByte('0' + number / 10);                       /* tens place */
	transmitByte('0' + number - 10 * floor(number / 10));        /* ones */
	transmitByte('.');
	transmitByte('0' + (number * 10) - floor(number) * 10);    /* tenths */
	/* hundredths place */
	transmitByte('0' + (number * 100) - floor(number * 10) * 10);
	printString("\r\n");
}

int ADCsingleREAD(uint8_t adctouse)
{
	int ADCval;

	ADMUX = adctouse;         // use #1 ADC
	ADMUX |= (1 << REFS0);    // use AVcc as the reference
	ADMUX &= ~(1 << ADLAR);   // clear for 10 bit resolution
    
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);    // 128 prescale for 8Mhz
	ADCSRA |= (1 << ADEN);    // Enable the ADC

	ADCSRA |= (1 << ADSC);    // Start the ADC conversion

	while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish 


	ADCval = ADCL;
	ADCval = (ADCH << 8) + ADCval;    // ADCH is read so ADC can be updated again

	return ADCval;
}

int main(void) {

	float voltage;

	// -------- Inits --------- //
	initUSART();
	printString("\r\nDigital Voltmeter\r\n\r\n");
	initADC();
	setupADCSleepmode();

	// ------ Event loop ------ //
	int ADCvalue;
  
	while (1) {

		voltage = oversample16x() * VOLTAGE_DIV_FACTOR * REF_VCC / 1024;
		//printFloat(voltage);
		/*  alternatively, just print it out:
		*  printWord(voltage*100);
		*  but then you have to remember the decimal place
		*/
   
		//ADCvalue = ADCsingleREAD(1);
		// ADCvalue now contains an 10bit ADC read
		//printFloat(ADCvalue);
		
		//uint8_t number = (ADCvalue * REF_VCC * 10) / 1024;
		float number = voltage;
		
		number = round(number * 100) / 100; /* round off to 2 decimal places */
		transmitByte('0' + number / 10);
		transmitByte('0' + number - 10 * floor(number / 10));
		transmitByte('.');
		transmitByte('0' + (number * 10) - floor(number) * 10);
		transmitByte('0' + (number * 100) - floor(number * 10) * 10);
		printString("\r\n");

		_delay_ms(500);


	}                                                  /* End event loop */
	return (0);                            /* This line is never reached */
}



    

// int main(void)
// {
//     int ADCvalue;
//
//     while (1)
//     {
//             ADCvalue = ADCsingleREAD(1);
//             // ADCvalue now contains an 10bit ADC read
//     }
// }
