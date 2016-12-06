/*
 * MAX_Display_7219Lib.cpp
 *
 * Created: 10/23/2016 3:36:03 AM
 *  Author: heman
 */ 

// include header
// #include "SPI_Lib.h"		// Needs SPI library also for operation
#include "MAX_Display_72xxLib.h"

//settings to initialize MAX chip, refer data-sheet
void _MAX_72XX :: init( void ) {
	
	// shutdown settings
	send ( SHUTDOWN, NORMAL_OP, &PORTB, defaultSlavePin );
	
	// decode mode 
	send ( DECODE_MODE, CODEB_DECODE_ALL, &PORTB, defaultSlavePin );
		
	// intensity control
	send ( INTENSITY, INTENSITY_MAX, &PORTB, defaultSlavePin );
	
	// scan limit
	send ( SCAN_LIMIT, DISP_ALL, &PORTB, defaultSlavePin );
	
}


/* Send data to MAX IC, send ( unsigned char pos, unsigned char data, volatile unsigned char *port, uint8_t slavePin )
 * Description: have to send 16 bytes together to control IC, first command and data following it
 * input: pos -> position or command
 *			data -> data to be sent
 *			port -> on whicj port IC is connected
 *			slave pin -> pin number of port on which IC is connected	
 */
void _MAX_72XX :: send ( unsigned char pos, unsigned char data, volatile unsigned char *port, uint8_t slavePin ) {
	
	// select device 
	*port &= ~(1<<slavePin);
	// send data
	_SPI::transmit ( pos );
	_SPI::transmit ( data );
	// unselect device
	*port |= (1<<slavePin);
		
}