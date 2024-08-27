/* DataAcquisition.c
 * 
 *-----------------------------------------------------------------------------------
 * Hochschule Bremerhaven
 *----------------------------------------------------------------------------------- 
 * File Description: Read analog output voltage & send calculated temperature value.
 * Subject: Maritime Systems (Embedded Systems Design)
 * Developer: Sumit Gadhiya (Matriculation Nr: 38710)
 * Date: 13.02.2023
 *
 */ 

#define F_CPU 16000000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "fifo.h"
#include "uart.h"
#include "dataio.h"
#include "timer0interupt.h"

volatile uint16_t intnum=0;
volatile uint8_t *bufcounter;

void InitialiseHardware(void)
{
	sei();							// enables interrupts by setting the global interrupt mask
	AdcInit();						// initializes the a/d converter
	bufcounter = uart_init(19200);	// initializes the UART for the given baudrate
	PortInit();						// initializes the port settings
	StartTimer0Interrupt();			// timer 0 interrupt for 15 ms
}

int main(void)
/*
Example program for first experiments.
After initializing the interfaces and "Hello World" is send to the serial port.
In a period of a second port pin D7 is toggled and sample data are send to the 
serial port. These sample data contain an index, analog data input, digital port 
inputs and an interrupt counter.
*/
{
	char Text[64];
	uint16_t ADCValue;
	uint16_t index=0;
	float V100,V0,V_unknown, Alpha_0, Alpha_1;
	InitialiseHardware(); 
	sprintf( Text,"\r\n Temperature Measurement Experiment \n");
	uart_puts (Text); _delay_ms(1000);
	
	while(1)
    {
		TogglePortD(7);
		index++;
		ADCValue=ReadChannel(6);
		

		sprintf( Text,"\r\n To start the experiment, please press left push button. \n");
		uart_puts (Text); _delay_ms(1000);
		
		if (ReadPortD(3))
		{
			sprintf( Text,"\r\n Please dip the temperature sensor in ice water (0°C). \n");
			uart_puts (Text); _delay_ms(1000);
			sprintf( Text,"\r\n Press left push button to continue. \n");
			uart_puts (Text); _delay_ms(1000);
			while(1)
			{
				if (ReadPortD(3))
				{
					V_0 = ADCValue; 			//Output voltage at 0°C
					//V_0 = 3*ADCValue/1023		//Scaling ADCValue
					sprintf( Text,"\r\n Please dip the temperature sensor in boiling water (100°C). \n");
					uart_puts (Text); _delay_ms(1000);
					sprintf( Text,"\r\n Press left push button to continue. \n");
					uart_puts (Text); _delay_ms(1000);
					while(1)
					{
						if (ReadPortD(3))
						{
							V_100 = ADCValue;				 //Output voltage at 100°C  
							//V_100 = 3*ADCValue/1023		 //Scaling ADCValue
							Alpha_1 = -100/(V_0 - V_100);	 //Calculating coeficients value
							Alpha_0 = -Alpha_1 * V_0;		 //Calculating coeficients value
							
							sprintf( Text,"\r\n Please dip the temperature sensor in water to measure its temperature. \n");
							uart_puts (Text); _delay_ms(1000);
							sprintf( Text,"\r\n Press left push button to check the temperature of water. \n");
							uart_puts (Text); _delay_ms(1000);
							while(1)
							{
								if (ReadPortD(3))
								{	
									V_unknown = ADCValue				//Output voltage at unknown temp
									//V_unknown = 3*ADCValue/1023		//Scaling ADCValue
									Temp_unknown = (Alpha_1 * V_unknown) + Alpha_0
									sprintf( Text,"\r\n Temperature of water is %d. \n",Temp_unknown);
									uart_puts (Text); _delay_ms(1000);  

								}
							}
						}
					}
				}
			}
		}
		
		
		//sprintf( Text,"\r\n Temperature Measurement \n");
		//uart_puts (Text); _delay_ms(1000);		
		//sprintf( Text,"Examples: %d %d %d %d %d\r\n",index,ADCValue,ReadPortD(3),ReadPortD(4),intnum);
		//uart_puts (Text); _delay_ms(1000);
    }
}

ISR(TIMER0_COMP_vect)
/*
Interrupt service routine for timer 0 interrupt.
*/
{
	intnum++;
}