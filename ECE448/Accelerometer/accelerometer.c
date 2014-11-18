/* ADC Voltmeter
* Continuously outputs voltage over the serial line.
*/

// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>                           /* for ADC sleep mode */
#include <math.h>                           /* for round() and floor() */
#include <stdio.h>

#include "pinDefines.h"
#include "USART.h"
#include "i2c.h"

/* Note: This voltmeter is only as accurate as your reference voltage.
* If you want four digits of accuracy, need to measure your AVCC well.
* Measure either AVCC of the voltage on AREF and enter it here.
*/
#define REF_VCC 1.1

#define VOLTAGE_DIV_RES 10000

// Define registers per MMA8452Q, Rev 4.1, 08/2011 3-Axis, 12-bit/8-bit Digital Accelerometer
// Freescale Semiconductor Data Sheet
#define STATUS           0x00
#define OUT_X_MSB        0x01    
#define OUT_X_LSB        0x02
#define OUT_Y_MSB        0x03
#define OUT_Y_LSB        0x04
#define OUT_Z_MSB        0x05
#define OUT_Z_LSB        0x06
#define SYSMOD           0x0B
#define INT_SOURCE       0x0C
#define WHO_AM_I         0x0D   
#define XYZ_DATA_CFG     0x0E
#define HP_FILTER_CUTOFF 0x0F
#define PL_STATUS        0x10
#define PL_CFG           0x11
#define PL_COUNT         0x12
#define PL_BF_ZCOMP      0x13
#define P_L_THS_REG      0x14
#define FF_MT_CFG        0x15
#define FF_MT_SRC        0x16
#define FF_MT_THS        0x17
#define FF_MT_COUNT      0x18
#define TRANSIENT_CFG    0x1D
#define TRANSIENT_SRC    0x1E
#define TRANSIENT_THS    0x1F
#define TRANSIENT_COUNT  0x20
#define PULSE_CFG        0x21
#define PULSE_SRC        0x22
#define PULSE_THSX       0x23
#define PULSE_THSY       0x24
#define PULSE_THSZ       0x25
#define PULSE_TMLT       0x26
#define PULSE_LTCY       0x27
#define PULSE_WIND       0x28
#define ASLP_COUNT       0x29
#define CTRL_REG1        0x2A
#define CTRL_REG2        0x2B
#define CTRL_REG3        0x2C
#define CTRL_REG4        0x2D
#define CTRL_REG5        0x2E
#define OFF_X            0x2F
#define OFF_Y            0x30
#define OFF_Z            0x31

#define SA0 1
#if SA0
#define MMA8452_ADDRESS 0x1D  // SA0 is high, 0x1C if low
#else
#define MMA8452_ADDRESS 0x1C
#endif

// Set the scale below either 2, 4 or 8
const int SCALE = 2;  // Sets full-scale range to +/-2, 4, or 8g. Used to calc real g values.
// Set the output data rate below. Value should be between 0 and 7
const int dataRate = 3;  // 0=800Hz, 1=400, 2=200, 3=100, 4=50, 5=12.5, 6=6.25, 7=1.56


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
	float number = voltage;
	//float number = (voltage/4) * (REF_VCC/1023);
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















int readRegister(uint8_t address){
	int data;

	i2cSendStart();
	i2cWaitForComplete();

	i2cSendByte((MMA8452_ADDRESS<<1)); // Write 0xB4
	i2cWaitForComplete();

	i2cSendByte(address);	// Write register address
	i2cWaitForComplete();

	i2cSendStart();

	i2cSendByte((MMA8452_ADDRESS<<1)|0x01); // Write 0xB5
	i2cWaitForComplete();
	i2cReceiveByte(TRUE);
	i2cWaitForComplete();

	data = i2cGetReceivedByte();	// Get MSB result
	i2cWaitForComplete();
	i2cSendStop();

	cbi(TWCR, TWEN);	// Disable TWI
	sbi(TWCR, TWEN);	// Enable TWI

	return data;
}

// Writes a single int (data) into address
void writeRegister(unsigned char address, unsigned char data){
	i2cSendStart();
	i2cWaitForComplete();

	i2cSendByte((MMA8452_ADDRESS<<1)); // Write 0xB4
	i2cWaitForComplete();

	i2cSendByte(address);	// Write register address
	i2cWaitForComplete();

	i2cSendByte(data);
	i2cWaitForComplete();

	i2cSendStop();
}

void MMA8452Reset(){
	writeRegister(CTRL_REG2, 0x40); // set reset bit to 1 to assert software reset to zero at end of boot process
}

// Allow user compensation of acceleration errors
void MMA8452Offsets(){
	MMA8452Standby();  // Must be in standby to change registers
   
	// Factory settings are pretty good; the settings below produce 1 mg error or less at 2 g full scale! For the device at rest on my table 
	// these values partially compensate for the slope of the table and the slope of the sensor in my breadboard. It is a pretty stable setup!
	// For negative values use 2's complement, i.e., -2 mg = 0xFF, etc.
	writeRegister(OFF_X, 0x0F);//0xF9); // X-axis compensation; this is -14 mg
	writeRegister(OFF_Y, 0xF0);//0x01); // Y-axis compensation; this is +2 mg
	writeRegister(OFF_Z, 0x00); // z-axis compensation; this is  0 mg adjustment
   
	MMA8452Active();  // Set to active to start reading
}

void initMMA8452(int fsr, int dataRate){
	MMA8452Standby();  // Must be in standby to change registers

	// Set up the full scale range to 2, 4, or 8g.
	if ((fsr==2)||(fsr==4)||(fsr==8))
		writeRegister(XYZ_DATA_CFG, fsr >> 2);  
	else
		writeRegister(XYZ_DATA_CFG, 0);

	// Setup the 3 data rate bits, from 0 to 7
	writeRegister(CTRL_REG1, readRegister(CTRL_REG1) & ~(0x38));
	if (dataRate <= 7)
		writeRegister(CTRL_REG1, readRegister(CTRL_REG1) | (dataRate << 3));  
    
	// These settings have to do with setting up the sleep mode and should probably be broken up into a separate function
	// set Auto-WAKE sample frequency when the device is in sleep mode

	writeRegister(0x29, 0x40 ); // sleep after ~36 seconds of inactivity at 6.25 Hz ODR

	writeRegister(CTRL_REG1, readRegister(CTRL_REG1) & ~(0xC0)); // clear bits 7 and 8
	writeRegister(CTRL_REG1, readRegister(CTRL_REG1) |  (0xC0)); // select 1.56 Hz sleep mode sample frequency for low power

	// set sleep power mode scheme
	writeRegister(CTRL_REG2, readRegister(CTRL_REG2) & ~(0x18)); // clear bits 3 and 4
	writeRegister(CTRL_REG2, readRegister(CTRL_REG2) |  (0x18)); // select low power mode
     
	// Enable auto SLEEP
	writeRegister(CTRL_REG2, readRegister(CTRL_REG2) & ~(0x04)); // clear bit 2
	writeRegister(CTRL_REG2, readRegister(CTRL_REG2) |  (0x04)); // enable auto sleep mode

	// set sleep mode interrupt scheme
	writeRegister(CTRL_REG3, readRegister(CTRL_REG3) & ~(0x3C)); // clear bits 3, 4, 5, and 6
	writeRegister(CTRL_REG3, readRegister(CTRL_REG3) |  (0x3C)); // select wake on transient, orientation change, pulse, or freefall/motion detect
     
	// Enable Auto-SLEEP/WAKE interrupt
	writeRegister(CTRL_REG4, readRegister(CTRL_REG4) & ~(0x80)); // clear bit 7
	writeRegister(CTRL_REG4, readRegister(CTRL_REG4) |  (0x80)); // select  Auto-SLEEP/WAKE interrupt enable
   
	// Set up portrait/landscape registers - 4 steps:
	// 1. Enable P/L
	// 2. Set the back/front angle trigger points (z-lock)
	// 3. Set the threshold/hysteresis angle
	// 4. Set the debouce rate
	// For more info check out this app note: http://cache.freescale.com/files/sensors/doc/app_note/AN4068.pdf
	writeRegister(PL_CFG, 0x40);        // 1. Enable P/L
	// writeRegister(PL_BF_ZCOMP, 0x44); // 2. 29deg z-lock (don't think this register is actually writable)
	// writeRegister(P_L_THS_REG, 0x84); // 3. 45deg thresh, 14deg hyst (don't think this register is writable either)
	writeRegister(PL_COUNT, 0x50);      // 4. debounce counter at 100ms (at 800 hz)

	/* Set up single and double tap - 5 steps:
	1. Set up single and/or double tap detection on each axis individually.
	2. Set the threshold - minimum required acceleration to cause a tap.
	3. Set the time limit - the maximum time that a tap can be above the threshold
	4. Set the pulse latency - the minimum required time between one pulse and the next
	5. Set the second pulse window - maximum allowed time between end of latency and start of second pulse
	for more info check out this app note: http://cache.freescale.com/files/sensors/doc/app_note/AN4072.pdf */
	writeRegister(PULSE_CFG, 0x7F);  // 1. enable single/double taps on all axes
	// writeRegister(PULSE_CFS, 0x55);  // 1. single taps only on all axes
	// writeRegister(PULSE_CFS, 0x6A);  // 1. double taps only on all axes
	writeRegister(PULSE_THSX, 0x04);  // 2. x thresh at 0.25g, multiply the value by 0.0625g/LSB to get the threshold
	writeRegister(PULSE_THSY, 0x04);  // 2. y thresh at 0.25g, multiply the value by 0.0625g/LSB to get the threshold
	writeRegister(PULSE_THSZ, 0x04);  // 2. z thresh at 0.25g, multiply the value by 0.0625g/LSB to get the threshold
	writeRegister(PULSE_TMLT, 0x30);  // 3. 2.55s time limit at 100Hz odr, this is very dependent on data rate, see the app note
	writeRegister(PULSE_LTCY, 0xA0);  // 4. 5.1s 100Hz odr between taps min, this also depends on the data rate
	writeRegister(PULSE_WIND, 0xFF);  // 5. 10.2s (max value)  at 100 Hz between taps max

	// Set up motion detection
	writeRegister(FF_MT_CFG, 0x58); // Set motion flag on x and y axes
	writeRegister(FF_MT_THS, 0x84); // Clear debounce counter when condition no longer obtains, set threshold to 0.25 g
	writeRegister(FF_MT_COUNT, 0x8); // Set debounce to 0.08 s at 100 Hz

	// Set up interrupt 1 and 2
	writeRegister(CTRL_REG3, readRegister(CTRL_REG3) & ~(0x02)); // clear bits 0, 1 
	writeRegister(CTRL_REG3, readRegister(CTRL_REG3) |  (0x02)); // select ACTIVE HIGH, push-pull interrupts
     
	// writeRegister(0x2C, 0x02);  // Active high, push-pull interrupts

	writeRegister(CTRL_REG4, readRegister(CTRL_REG4) & ~(0x1D)); // clear bits 0, 3, and 4
	writeRegister(CTRL_REG4, readRegister(CTRL_REG4) |  (0x1D)); // DRDY, Freefall/Motion, P/L and tap ints enabled
   
	writeRegister(CTRL_REG5, 0x01);  // DRDY on INT1, P/L and taps on INT2

	MMA8452Active();  // Set to active to start reading
}

// Sets the MMA8452 to standby mode.
// It must be in standby to change most register settings
void MMA8452Standby(){
	int c = readRegister(0x2A);
	writeRegister(CTRL_REG1, c & ~(0x01));
}

// Sets the MMA8452 to active mode.
// Needs to be in this mode to output data
void MMA8452Active(){
	int c = readRegister(0x2A);
	writeRegister(CTRL_REG1, c | 0x01);
}

void readAccelData(int * destination){
	int rawData[6];  // x/y/z accel register data stored here

	readRegisters(0x01, 6, &rawData[0]);  // Read the six raw data registers into data array

	// Loop to calculate 12-bit ADC and g value for each axis
	for (int i=0; i<6; i+=2)
	{
		destination[i/2] = ((rawData[i] << 8) | rawData[i+1]) >> 4;  // Turn the MSB and LSB into a 12-bit value
		if (rawData[i] > 0x7F)
		{  
			// If the number is negative, we have to make it so manually (no 12-bit data type)
			destination[i/2] = ~destination[i/2] + 1;
			destination[i/2] *= -1;  // Transform into negative 2's complement #
		}
	}
}

void readRegisters(int address, int i, int * dest){
	i2cSendStart();
	i2cWaitForComplete();

	i2cSendByte((MMA8452_ADDRESS<<1)); // write 0xB4
	i2cWaitForComplete();

	i2cSendByte(address);	// write register address
	i2cWaitForComplete();

	i2cSendStart();
	i2cSendByte((MMA8452_ADDRESS<<1)|0x01); // write 0xB5
	i2cWaitForComplete();
	for (int j=0; j<i; j++)
	{
		i2cReceiveByte(TRUE);
		i2cWaitForComplete();
		dest[j] = i2cGetReceivedByte(); // Get MSB result
	}
	i2cWaitForComplete();
	i2cSendStop();

	cbi(TWCR, TWEN); // Disable TWI
	sbi(TWCR, TWEN); // Enable TWI
}

int main(void) {

    //uint8_t tempHighByte, tempLowByte;

    // -------- Inits --------- //
    //clock_prescale_set(clock_div_1);                             /* 8MHz */
    initUSART();
    //printString("\r\n====  i2c Accelerometer  ====\r\n");
    i2cInit();
	
	
	
	
	// Read the WHO_AM_I register, this is a good test of communication
	uint8_t c = readRegister(WHO_AM_I);  // Read WHO_AM_I register
	if (c == 0x2A) // WHO_AM_I should always be 0x2A
	{  
		MMA8452Reset(); // Start by resetting sensor device to default settings
		initMMA8452(SCALE, dataRate);  // init the accelerometer if communication is OK
		//printString("MMA8452Q is online...");
		MMA8452Offsets(); // User defined compensation for x/y/z acceleration errors
	}
	else
	{
		printString("Could not connect to MMA8452Q");
		// Serial.println(c, HEX);
		//while(1) ; // Loop forever if communication doesn't happen
	}
	
	int accelCount[3];  // Stores the 12-bit signed value
	float accelG[3];  // Stores the real accel value in g's
	
	

    // ------ Event loop ------ //
    while (1) {
		
		readAccelData(accelCount);  // Read the x/y/z adc values
		
		
		// Now we'll calculate the accleration value into actual g's
		for (int i=0; i<3; i++)
			accelG[i] = (float) accelCount[i]/((1<<12)/(2*SCALE));  // get actual g value, this depends on scale being set
		// Print out values
		//for (int i=0; i<3; i++)
		
		printString("X: ");
		if (accelG[0] < 0) {
			accelG[0] = -accelG[0];
			printString("-");
				
		}
		printVoltage(accelG[0]);  // Print g values to thousandths of a g
		
		printString("Y: ");		
		if (accelG[1] < 0) {
			accelG[1] = -accelG[1];
			printString("-");
				
		}
		printVoltage(accelG[1]);  // Print g values to thousandths of a g
		
		printString("Z: ");
		if (accelG[2] < 0) {
			accelG[2] = -accelG[2];
			printString("-");
				
		}
		printVoltage(accelG[2]);  // Print g values to thousandths of a g
		
		
		
		
		//{
			
   
			//}
		
		
		printString("\r\n");
		
		
		
		
		
                          /* To set register, address LM75 in write mode */
      // i2cStart();
 //      i2cSend(LM75_ADDRESS_W);
 //      i2cSend(LM75_TEMP_REGISTER);
 //      i2cStart();                      /* restart, just send start again */
 //                                /* Setup and send address, with read bit */
 //      i2cSend(LM75_ADDRESS_R);
 //                                 /* Now receive two bytes of temperature */
 //      tempHighByte = i2cReadAck();
 //      tempLowByte = i2cReadNoAck();
 //      i2cStop();
 //
 //      // Print it out nicely over serial for now...
 //      printByte(tempHighByte);
      // if (tempLowByte & _BV(7)) {
//         printString(".5\r\n");
//       }
      //else {
        // printString(".0\r\n");
      //}
                                                      /* Once per second */
			_delay_ms(1000);

    }                                                  /* End event loop */
    return (0);                            /* This line is never reached */





















	// float voltage1;
	// float voltage2;
	// float res1;
	// float res2;
	// -------- Inits --------- //
	//initUSART();
	// setupADCSleepmode();
	// printString("\r\nDigital Voltmeter\r\n\r\n");
	

	// ------ Event loop ------ //
  
	// while (1) {

		// //initADC(0);
// 		//voltage1 = oversample16x();
// 		//printString("Thermistor 1:\r\n");
// 		printFloat(0);
// 		//printVoltage(voltage1);
// 		//res1 = printThermRes(voltage1);
// 		//printTemp(res1);
// 		printString("\r\n");
//
// 		_delay_ms(100);
//
// 		//initADC(1);
// 		//voltage2 = oversample16x();
// 		//printString("Thermistor 2:\r\n");
// 		printFloat(0);
// 		//printVoltage(voltage2);
// 		//res2 = printThermRes(voltage2);
// 		//printTemp(res2);
// 		printString("\r\n");
// 		_delay_ms(500);
			//
	// }                                                  /* End event loop */
	// return (0);                            /* This line is never reached */
}
