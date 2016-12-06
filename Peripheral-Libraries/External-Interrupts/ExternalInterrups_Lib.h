/*
 * ExternalInterrups_Lib.h
 *
 * Created: 10/18/2016 10:21:11 AM
 *  Author: heman
 */ 


#ifndef EXTERNALINTERRUPS_LIB_H_
#define EXTERNALINTERRUPS_LIB_H_

// include avr headers
//#include <avr/io.h>
#include <avr/interrupt.h>

/*
INT2 is only edge triggered interrupt

ISC11 ISC10		Description
0		0		The low level of INT1 generates an interrupt request.
0		1		Any logical change on INT1 generates an interrupt request.
1		0		The falling edge of INT1 generates an interrupt request.
1		1		The rising edge of INT1 generates an interrupt request.

ISC01 ISC00		Description
0		0		The low level of INT0 generates an interrupt request.
0		1		Any logical change on INT0 generates an interrupt request.
1		0		The falling edge of INT0 generates an interrupt request.
1		1		The rising edge of INT0 generates an interrupt request.
*/

enum ExtInt{
	// declare name for type of detections
	lowLevel = 00,
	anyLogic = 01,
	fallingEdge = 10,
	risingEdge = 11,
};

 
class _ExternalInterrupts {
	
	// declare public member functions
	public :
		void initEXT0 ( uint8_t trigger );
		void initEXT1 ( uint8_t trigger );
		/*Observe that, if enabled,
		* the interrupts will trigger even if the INT0..2 pins are configured as outputs. This feature provides
		* a way of generating a software interrupt.
		*/
		void initEXT2 ( bool trigger );
};



#endif /* EXTERNALINTERRUPS_LIB_H_ */