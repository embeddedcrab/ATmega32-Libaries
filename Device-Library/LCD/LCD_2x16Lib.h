/*
 * LCD_2x16Lib.h
 *
 * Created: 10/3/2016 2:03:44 PM
 *  Author: heman
 */ 


#ifndef LCD_2X16LIB_H_
#define LCD_2X16LIB_H_

#include <avr/io.h>
#define F_CPU	8000000UL
#include <util/delay.h>

// Define LCD pins
#define RegisterSelectPin		1
#define ReadWritePin			2
#define EnablePin				3
#define DataPins				( (1<<PB4) | (1<<PB5) | (1<<PB6) | (1<<PB7) )
// Define LCD port
#define LCDPORT					PORTB
#define LCDpins					( (1<<PB1) | (1<<PB2) | (1<<PB3) | (1<<PB4) | (1<<PB5) | (1<<PB6) | (1<<PB7) )
#define RegisterSelectMask		( 1<<RegisterSelectPin )
#define ReadWriteMask			( 1<<ReadWritePin )
#define EnableMask				( 1<<EnablePin )
#define LCDDataClear			( LCDPORT &= ~(DataPins) )
// LCD register commands
#define LCDRegisterSelect(x)			( x==1 ?  LCDPORT |= RegisterSelectMask : LCDPORT &= ~RegisterSelectMask )		// if x == 1 -> send data else send command
#define LCDReadWriteSelect(x)			( x==1 ? LCDPORT |= ReadWriteMask : LCDPORT &= ~ReadWriteMask )		// x must always be zero	
#define LCDEnable(x)					( x==1 ? LCDPORT |= EnableMask : LCDPORT &= ~EnableMask )


class _LCD {
	public :
	
		void init ( void );
		void putChar ( unsigned char ch, unsigned int type  );
		void string ( unsigned char *ch, unsigned int len );
		void clear ( void );
		void printString ( unsigned char *data, unsigned int len, unsigned int lin, unsigned int pos );
		void printNumDynamic ( unsigned num, unsigned int lin, unsigned int pos );
		void printNum ( unsigned num, unsigned int lin, unsigned int pos );
	
	};// class ends


#endif /* LCD_2X16LIB_H_ */