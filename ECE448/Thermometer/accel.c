/* ADC Voltmeter
* Continuously outputs voltage over the serial line.
*/

// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <avr/sleep.h>                           /* for ADC sleep mode */
#include <math.h>                           /* for round() and floor() */
#include <stdio.h>

#include "pinDefines.h"
#include "USART.h"
#include "i2c.h"

#define ADDRESS_W		0b00111001
#define ADDRESS_R		0b00111000

void printFloat(float voltage) {
	float number = voltage;
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

	uint8_t tempHighByte, tempLowByte;

	// -------- Inits --------- //
	//clock_prescale_set(clock_div_1); 
	initUSART();
	printString("\r\n====  i2c Accelerometer  ====\r\n");
	initI2C();
	
	// ------ Event loop ------ //
	while (1) {

		i2cStart();
		i2cSend(ADDRESS_W);
		i2cSend(0b00000000);
		i2cStart();
		/* restart, just send start again */
		/* Setup and send address, with read bit */
		i2cSend(ADDRESS_R);
		/* Now receive two bytes of temperature */
		tempHighByte = i2cReadAck();
		tempLowByte = i2cReadNoAck();
		i2cStop();

		// Print it out nicely over serial for now...
		printFloat(tempHighByte);

		_delay_ms(1000);

	}                                                  /* End event loop */
	return (0);                            /* This line is never reached */
}
