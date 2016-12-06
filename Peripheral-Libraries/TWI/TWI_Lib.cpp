/*
 * TWI_Lib.cpp
 *
 * Created: 10/21/2016 12:48:04 PM
 *  Author: heman
 */ 

// include library header
#include "TWI_Lib.h"

// declaring global variables to slaveAddress
extern unsigned char SLAVE_ADDRESS;
extern bool SINGLE_BYTE_FLAG;
extern uint8_t DATA_COUNT;


/* Name: initialization function -> init
 * Description:  initialize TWI according to clock, works for 8MHz clock source
 * input: clock -> {	100KHz, 0
						400 KHz, 1
					}
	enableACK -> controls the generation of the acknowledge pulse
	ownAddress -> while working in slave mode, needs address to communicate
 * return: void	
 */
void _TWI :: init ( bool Clock, bool enableGeneralCall, unsigned char ownAddress ) {
	
	// setting clock frequency of TWI
	TWBR = Clock == 0 ? 32 : 2;	// SCL = Fcpu/( 16 + (( 2 * TWBR ) * 4^TWPS)  )
	
	// setting address and general call bit
	ownAddress = ownAddress & 0xFE;
	TWAR = ownAddress;		// consider MSB 7 bits only
	
	enableGeneralCall == 0 ? TWAR &= ~(1<<TWGCE) : TWAR |= (1<<TWGCE);
	
	// enable TWI
	TWCR |= (1<<TWEN);
	
}


/* Name: master mode sending function -> masterSend
 * Description: send a single data to slave
 * input: slaveAddress -> to which data is to be sent
 *			data -> data to be sent
 * return: void
 */
void masterSend ( unsigned char slaveAddress, unsigned char data ) {
	
	// get slave address, send SLAVE+W
	SLAVE_ADDRESS = slaveAddress;
	
	// put data in queue and generate flag
	
	// set single byte flag
	SINGLE_BYTE_FLAG = true;
	// need to send only single Byte
	DATA_COUNT = 0;
	
	// send start condition to enter in master mode
	sendStart;
	
}