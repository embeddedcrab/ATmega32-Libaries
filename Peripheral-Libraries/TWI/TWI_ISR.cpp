/*
 * TWI.cpp
 *
 * Created: 10/21/2016 12:45:41 PM
 * Author : heman
 */ 

// include standard headers

// include avr standard

// include library headers
#include "TWI_Lib.h"

// extern variables
unsigned char SLAVE_ADDRESS;
unsigned char DATA;
bool SINGLE_BYTE_FLAG;
uint8_t DATA_COUNT;



int main(void)
{
    
	// enable TWI interrupt
	
	// enable global interrupt flag using sei()
	
	for ( ; ; ) {
		// let controller sleep
	}
}


// ISR for TWI
ISR ( TWI_vect ) {
	
	// status variable
	unsigned char status;
	
	// reading status of TWI and masking status bits only
	status = TWSR;
	status = status & 0xF8;
	
	if ( (status != BUS_ERROR) && (status != NO_INFORMATION) ) {
		// apply switch case on status
		switch ( status ) {
			// START condition has been sent
			case START_SENT: {
				// send Slave address with read or write operation
				TWDR = SLAVE_ADDRESS;
				clearTWINT;
				
				break;
			}
			
			// Repeated START condition sent
			case REPEATED_START_SENT: {
				// perform repeated start operation, whether reading or writing
				TWDR = SLAVE_ADDRESS;
				
				break;
			}
			
			/********************** MASTER TRANSMITTER STATES *****************************/
			
			// slave operation transmitted and ACK received
			case SLA_W_ACK: {
				// send data to slave, fetch data from queue
				DATA = 0x00;
				// put fetched data into TWDR, always check TWINT flag, if low then data will be discarded and Write collision occurs
				clearTWINT;
				TWDR = DATA;	
				
				break; 
			}
			
			// slave operation transmitted and NACK
			case SLA_W_NACK: {
				// send STOP command
				sendStop;
				
				break;
			}
			
			// data sent ACK
			case DATA_SENT_ACK: {
				// check length of data i.e., single or multiple
				if ( true == SINGLE_BYTE_FLAG ) {
					// clear status and send stop condition
					sendStop;
					// clear single byte flag
					SINGLE_BYTE_FLAG = false;
				}
				else {
					if ( ++DATA_COUNT != 17 ) {
						// get data from queue
						DATA = 0x00;
						// send to slave
						clearTWINT;
						TWDR = DATA;
					}
					else {
						// send STOP command
						sendStop;
						// make data count Zero
						DATA_COUNT = 0;
					}	
				}
				
				break;
			}
			
			// data sent NACK
			case DATA_SENT_NACK: {
				// clear TWINT and send STOP
				sendStop;
				
				break;
			}
			
			// arbitration lost
			case ARBITRATION_LOST: {
				// other master  continues
				break;
			}
			
			/********************** MASTER RECEIVER STATES *****************************/
			
			// slave operation sent and ACK received
			case SLA_R_ACK: {
				// get data from TWI
				DATA = TWDR;
				// send data to queue
				
				// send ACK/NACK to slave
				if ( true == SINGLE_BYTE_FLAG ){
					sendNACK;
					SINGLE_BYTE_FLAG = false;
				}
				else {
					sendACK;
				}
				
				break;
			}
			
			// slave operation sent and NACK
			case SLA_R_NACk: {
				// send STOP
				sendStop;
				
				break;
			}
			
			// data byte received and ACK sent, read multiple bytes
			case MASTER_DATA_RECEIVED_ACK_SENT: {					
				// will receive only 16 bytes of data
				if( ++DATA_COUNT != 17 ){
					// read data
					DATA = TWDR;
					// put data into queue
					
					// send ACK to slave
					sendACK;
				}
					
				else {
					// make data count Zero and send NACK to slave
					DATA_COUNT = 0;
					// send NACK to stop receiving, overflow in receive
					sendNACK;
				}
				
				break;
			}
			
			// data byte received and NACK sent
			case MASTER_DATA_RECEIVED_NACK_SENT: {
				// send STOP
				sendStop;
				
				break;
			}
		
		}// switch ends
		
	}// if ends
	
	// BUS Error or No Information
	else if ( BUS_ERROR == status ) {
		// clear STOP and TWINT
		clearTWINT;
		TWCR |= (1<<TWSTO);
	}
	
	// clear TWINT flag to continue TWI process
	clearTWINT;
}