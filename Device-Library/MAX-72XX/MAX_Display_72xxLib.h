/*
 * MAX_Display_72xxLib.h
 *
 * Created: 10/23/2016 3:36:33 AM
 *  Author: heman
 */ 


#ifndef MAX_DISPLAY_72XXLIB_H_
#define MAX_DISPLAY_72XXLIB_H_

// include required headers
#include "SPI_Lib.h"

//***** Settings *****//
#define DECODE_MODE				( (unsigned char) 0x09)
#define CODEB_DECODE_ALL		( (unsigned char) 0xFF)
#define NO_DECODE				( (unsigned char) 0x00)
#define SHUTDOWN				( (unsigned char) 0x0C)
#define NORMAL_OP				( (unsigned char) 0x01)

//***** INTENSITY CONTROL ******//
#define INTENSITY				( (unsigned char) 0x0A)
#define INTENSITY_MAX			( (unsigned char) 0x0F)

//***** SCAN LIMIT CONTROL ******//
#define SCAN_LIMIT				( (unsigned char) 0x0B)
#define DISP0					( (unsigned char) 0x00)
#define DISP1					( (unsigned char) 0x01)
#define DISP2					( (unsigned char) 0x02)
#define DISP3					( (unsigned char) 0x03)
#define DISP4					( (unsigned char) 0x04)
#define DISP5					( (unsigned char) 0x05)
#define DISP6					( (unsigned char) 0x06)
#define DISP_ALL				( (unsigned char) 0x07)

//***** DISPLAY CONTROL ******//
#define DISP_TEST				( (unsigned char) 0x0F)
#define DISP_TEST_MODE			( (unsigned char) 0x01)
#define DISP_NORMAL_OP			( (unsigned char) 0x00)

//******* ADDRESS REGISTERS FOR NO DECODE ********//
#define NO_OP					( (unsigned char) 0x00)
#define DIGIT0					( (unsigned char) 0x01)
#define DIGIT1					( (unsigned char) 0x02)
#define DIGIT2					( (unsigned char) 0x03)
#define DIGIT3					( (unsigned char) 0x04)
#define DIGIT4					( (unsigned char) 0x05)
#define DIGIT5					( (unsigned char) 0x06)
#define DIGIT6					( (unsigned char) 0x07)
#define DIGIT7					( (unsigned char) 0x08)

//******* REGISTER DATA FOR CODEB FONT ********//
#define CB0						( (unsigned char) 0x00)
#define CB1						( (unsigned char) 0x01)
#define CB2						( (unsigned char) 0x02)
#define CB3						( (unsigned char) 0x03)
#define CB4						( (unsigned char) 0x04)
#define CB5						( (unsigned char) 0x05)
#define CB6						( (unsigned char) 0x06)
#define CB7						( (unsigned char) 0x07)
#define CB8						( (unsigned char) 0x08)
#define CB9						( (unsigned char) 0x09)
#define CB_						( (unsigned char) 0x0A)
#define CBE						( (unsigned char) 0x0B)
#define CBH						( (unsigned char) 0x0C)
#define CBL						( (unsigned char) 0x0D)
#define CBP						( (unsigned char) 0x0E)
#define CB_BLANK				( (unsigned char) 0x0F)


//******* DATA REGISTERS ********//
#define D0						( (unsigned char) 0x00)
#define D1						( (unsigned char) 0x01)
#define D2						( (unsigned char) 0x02)
#define D3						( (unsigned char) 0x03)
#define D4						( (unsigned char) 0x04)
#define D5						( (unsigned char) 0x05)
#define D6						( (unsigned char) 0x06)
#define D7						( (unsigned char) 0x07)
#define D8						( (unsigned char) 0x08)
#define D9						( (unsigned char) 0x09)
#define HF						( (unsigned char) 0x0A)		// hi-fen
#define E						( (unsigned char) 0x0B)
#define H						( (unsigned char) 0x0C)
#define L						( (unsigned char) 0x0D)
#define P						( (unsigned char) 0x0E)
#define BLANK					( (unsigned char) 0x0F)


// connecting at 0th pin
#define MAX_Pin					0

class _MAX_72XX {
	
	// declare public functions
	public:
		void init ( void );
		void send ( unsigned char pos, unsigned char data , volatile unsigned char *port, uint8_t slavePin );
	};
	
/*
// default transmit function, used in send function
void _SPI :: transmit ( unsigned char data ) {
	
	// load data in register
	SPDR = data;
	// wait while transmission is not completed
	while ( !(SPSR & (1<<SPIF)) );
}
 */



#endif /* MAX_DISPLAY_72XXLIB_H_ */