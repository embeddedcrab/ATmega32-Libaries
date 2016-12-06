/*
 * USART_Lib.h
 *
 * Created: 10/13/2016 12:23:34 PM
 *  Author: heman
 */ 


#ifndef USART_LIB_H_
#define USART_LIB_H_

// include standard headers
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <avr/io.h>
#define F_CPU	8000000UL

// uncomment to use double speed mode
//#define useDoubleSpeedMode

#define USARTDummy		( (char) '\0' )
#define BPS		9600UL
#define BAUD	( ( F_CPU / ( 16 * BPS ) ) - 1 )


// class for USART
class _USART {
	
	// declaring public functions
	public:
		
		// initialization functions
		void init( uint8_t charSize, bool mode, bool parity, bool stopBits, bool polarity = 0 );
		
		// transmission functions
		void transmit( const char data );
		void print( const char *data );
		void nprint( const char *data, unsigned int len );
		// receiving functions
		char receive( void );
		char *scan( uint8_t length );
		void nscan( uint8_t length );		// receives data till terminating character is not received and send back to tx pin
		
		void printNumDynamic ( unsigned int num );
		void printNum ( unsigned int num );
		
		// interrupt functions
		void interruptEnable ( uint8_t select );
	};

#endif /* USART_LIB_H_ */