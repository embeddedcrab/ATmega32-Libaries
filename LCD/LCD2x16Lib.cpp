/*
 * LCD_2x16Lib.cpp
 *
 * Created: 10/3/2016 2:02:14 PM
 * Author : heman
 */ 

// Include headers
#include "LCD_2x16Lib.h"

void _LCD :: putChar( unsigned char ch, unsigned int type )
{
	LCDRegisterSelect ( type );		// set registers for data or command
	//LCDReadWriteSelect ( 0 );
	
	// send data/command as per input
	// send MSB
	LCDDataClear;
	LCDPORT |= ( ch & 0xF0 );
	LCDEnable ( 1 );	
	_delay_ms(1);
	LCDEnable ( 0 );
	// send LSB
	LCDDataClear;
	LCDPORT |= ( ch & 0x0F ) << 4;
	LCDEnable ( 1 );
	_delay_ms(1);
	LCDEnable ( 0 );
}

void _LCD :: string ( unsigned char *ch, unsigned int len )
{
	for ( unsigned int i=0; i<len; ++i ) {
		putChar( ch[i], 1 );
	}
}

void _LCD :: init ( void )
{
	DDRB |= LCDpins;
	putChar ( 0x02, 0 );		// return home
	putChar ( 0x28, 0 );		// set data bits and size of character block
	putChar ( 0x06, 0 );
	putChar ( 0x0f, 0 );		// set cursor settings
	putChar ( 0x01, 0 );		// clear screen
	putChar ( 0x80, 0 );		// set positions
}

void _LCD :: clear ( void )
{
	putChar ( 0x01, 0 );		// clear screen
}

void _LCD :: printString ( unsigned char *data, unsigned int len, unsigned int lin, unsigned int pos )
{
	/*if ( lin == 1 && pos >= 0 && pos <= 15 ) {
		putChar ( (0x80 + pos), 0 );
	}
	else if ( lin == 2 && pos >= 0 && pos <= 15 ) {
		putChar ( (0xc0 + pos), 0 );
	}
	string ( data, len );*/
	
	// check for line
	if ( lin > 0 ) {	
		if ( lin < 3 ) {
			// check for position
			if ( pos >= 0 ) {
				if ( pos <= 15 ) {
					if ( lin == 1 ) {
							putChar ( (0x80 + pos), 0 );
					}
					else if ( lin == 2 ) {
						putChar ( (0xc0 + pos), 0 );
					}
					// send data
					string ( data, len );
				}
			}
		}
	}
	
}

void _LCD :: printNumDynamic ( unsigned int num, unsigned int lin, unsigned int pos )
{
	unsigned char temp[10];
	unsigned int i = 0;
	
	do {
		temp[i++] = num%10 + '0' ;
		num /= 10;
	} while (num);
	
	if ( lin == 1 && pos >= 0 && pos <= 15 ) {
		putChar ( (0x80 + pos), 0 );
	}
	else if ( lin == 2 && pos >= 0 && pos <= 15 ) {
		putChar ( (0xC0 + pos), 0 );
	}
	
	while ( i ) {
		putChar ( temp[--i], 1 );
	}
}


void _LCD :: printNum ( unsigned int num, unsigned int lin, unsigned int pos ) {
	
	// define line and position of cursor
	if ( lin == 1 && pos >= 0 && pos <= 15 ) {
		putChar ( (0x80 + pos), 0 );
	}
	else if ( lin == 2 && pos >= 0 && pos <= 15 ) {
		putChar ( (0xC0 + pos), 0 );
	}
	
	// convert to character and send
	if ( num >= 0 && num < 10 ) {
		putChar ( num+48, 1 );
	}
	else if ( num > 9 && num < 100 ) {
		putChar ( (num/10)+48, 1 );
		putChar ( (num%10)+48, 1 );
	}
	else if ( num > 99 && num < 999 ) {
		putChar ( (num/100)+48, 1 );
		putChar ( ((num%100)/10)+48, 1 );
		putChar ( ((num%10)%10)+48, 1 );
	}
}
