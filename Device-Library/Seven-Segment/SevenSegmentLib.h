/*
 * SevenSegmentLib.h
 *
 * Created: 10/5/2016 9:23:47 AM
 *  Author: heman
 */ 


#ifndef SEVENSEGMENTLIB_H_
#define SEVENSEGMENTLIB_H_

// Include avr header
#include <avr/io.h>

class _SEG {
	
	public:
		void initSevenSegment ( void );
		void displaySevenSegment ( uint8_t val, uint8_t segtype );		// if type==0 -> common anode elseif type==1 -> common cathode
	};

#endif /* SEVENSEGMENTLIB_H_ */