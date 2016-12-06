/*
 * SevenSegmentLib.cpp
 *
 * Created: 10/5/2016 9:23:02 AM
 * Author : heman
 */ 

#include "SevenSegmentLib.h"

// Define PORT to be used
#define SEVENSEGMENTPORTB

void _SEG :: initSevenSegment ( void )
{
	#ifdef	SEVENSEGMENTPORTA
		#define SegmentPORT		PORTA
		DDRA = 0xFF;
	#endif

	#ifdef	SEVENSEGMENTPORTB
		#define SegmentPORT		PORTB
		DDRB = 0xFF;
	#endif

	#ifdef	SEVENSEGMENTPORTC
		#define SegmentPORT		PORTC
		DDRC = 0xFF;
	#endif

	#ifdef	SEVENSEGMENTPORTD
		#define SegmentPORT		PORTD
		DDRD = 0xFF;
	#endif
/*
	#ifdef	SEVENSEGMENTPORTA
		DDRA = 0xFF;
	#endif
	#ifdef	SEVENSEGMENTPORTB
		DDRB = 0xFF;
	#endif
	#ifdef	SEVENSEGMENTPORTC
		DDRC = 0xFF;
	#endif
	#ifdef	SEVENSEGMENTPORTD
		DDRD = 0xFF;
	#endif*/
}

// Data must lie between 0 to 9 and if type==0 -> common anode elseif type==1 -> common cathode
void _SEG :: displaySevenSegment ( uint8_t val, uint8_t segtype )
{
	if ( val >= 0 ) {
		if ( val <= 9 ) {
			// send data in common anode form
			if ( !segtype ) {
				switch ( val ) {
					case 0: SegmentPORT = 0xC0;
						break;
					case 1: SegmentPORT = 0xF9;
						break;
					case 2: SegmentPORT = 0xA4;
						break;
					case 3: SegmentPORT = 0xB0;
						break;
					case 4: SegmentPORT = 0x99;
						break;
					case 5: SegmentPORT = 0x92;
						break;
					case 6: SegmentPORT = 0x82;
						break;
					case 7: SegmentPORT = 0xF8;
						break;
					case 8:	SegmentPORT = 0x80;
						break;
					case 9: SegmentPORT = 0x90;
						break;
					default : // DO NOTHING
						break;
				}
			}
			else if ( 1 == segtype ) {
				switch ( val ) {
					case 0: SegmentPORT = ~0xC0;
						break;
					case 1: SegmentPORT = ~(0xF9);
						break;
					case 2: SegmentPORT = ~(0xA4);
						break;
					case 3: SegmentPORT = ~(0xB0);
						break;
					case 4: SegmentPORT = ~(0x99);
						break;
					case 5: SegmentPORT = ~(0x92);
						break;
					case 6: SegmentPORT = ~(0x82);
						break;
					case 7: SegmentPORT = ~(0xF8);
						break;
					case 8:	SegmentPORT = ~(0x80);
						break;
					case 9: SegmentPORT = ~(0x90);
						break;
					default : // DO NOTHING
						break;
				}
			}
		}	
	}
}


