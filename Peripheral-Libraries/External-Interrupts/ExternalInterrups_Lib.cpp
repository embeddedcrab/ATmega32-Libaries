/*
 * ExternalInterrups_Lib.cpp
 *
 * Created: 10/18/2016 10:20:59 AM
 *  Author: heman
 */ 

#include "ExternalInterrups_Lib.h"

void _ExternalInterrupts :: initEXT0 ( uint8_t trigger ) {
	
	// making PD2 pin for INT0 as input
	DDRD &= ~(1<<PD2);
	// define level or edge triggerence, check trigger value must be between 0 to 3
	if ( trigger >= 0 ) {
		if ( trigger < 4 ) {
			switch ( trigger ) {
				case 0: {
					MCUCR |= lowLevel<<ISC00;	// make both low
					break;
				}
				case 1: {
					MCUCR |= anyLogic<<ISC00;
					break;
				}
				case 2: {
					MCUCR |= fallingEdge<<ISC00;
					break;
				}
				case 3: {
					MCUCR |= risingEdge<<ISC00;
					break;
				}
			}
		}
	}// if ends
	
	// enable INT0
	GICR |= 1<<INT0;
}

void _ExternalInterrupts :: initEXT1 ( uint8_t trigger ) {
	
	// making PD3 pin for INT1 as input
	DDRD &= ~(1<<PD3);
	// define level or edge triggerence, check trigger value must be between 0 to 3
	if ( trigger >= 0 ) {
		if ( trigger < 4 ) {
			switch ( trigger ) {
				case 0: {
					MCUCR |= lowLevel<<ISC10;	// make both low
					break;
				}
				case 1: {
					MCUCR |= anyLogic<<ISC10;
					break;
				}
				case 2: {
					MCUCR |= fallingEdge<<ISC10;
					break;
				}
				case 3: {
					MCUCR |= risingEdge<<ISC10;
					break;
				}
			}
		}
	}// if ends
	
	// enable INT1
	GICR |= 1<<INT1;
}

// input : 1 -> rising edge and 0 -> falling edge
void _ExternalInterrupts :: initEXT2 ( bool trigger ) {
	
	// making INT2 pin PB2 as input, not necessary
	
	// it is always edge triggered
	trigger == 1 ? MCUCSR |= (1<<ISC2) : MCUCSR &= ~(1<<ISC2);
	// enable INT2
	GICR |= 1<<INT2;
}