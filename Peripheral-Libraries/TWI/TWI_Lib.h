/*
 * TWI_Lib.h
 *
 * Created: 10/21/2016 12:48:19 PM
 *  Author: heman
 */ 


#ifndef TWI_LIB_H_
#define TWI_LIB_H_

// include avr headers
#include <avr/interrupt.h>
#define F_CPU 8000000UL

//------- defining status codes of Master and Slave for TWSR register ----------//
// Master transmit mode
#define START_SENT							( (unsigned char) 0x08 )
#define REPEATED_START_SENT					( (unsigned char) 0x10 )
#define SLA_W_ACK							( (unsigned char) 0x18 )
#define SLA_W_NACK							( (unsigned char) 0x20 )
#define DATA_SENT_ACK						( (unsigned char) 0x28 )
#define DATA_SENT_NACK						( (unsigned char) 0x30 )
#define ARBITRATION_LOST					( (unsigned char) 0x38 )

// Master receive mode
#define SLA_R_ACK							( (unsigned char) 0x40 )
#define SLA_R_NACk							( (unsigned char) 0x48 )
#define MASTER_DATA_RECEIVED_ACK_SENT		( (unsigned char) 0x50 )
#define MASTER_DATA_RECEIVED_NACK_SENT		( (unsigned char) 0x58 )

// Slave receiver mode
#define OWN_SLAVE_W_RECEIVED_ACK_SENT							( (unsigned char) 0x60 )
#define ARBITRATION_LOST_SLA_RW_as_MASTER_SLA_W_ACK__SENT		( (unsigned char) 0x68 )
#define GENERAL_CALL_ACK										( (unsigned char) 0x70 )
#define ARBITRATION_LOST_SLA_RW_as_MASTER_GEN_CALL				( (unsigned char) 0x78 )
#define SLAVE_DATA_RECEIVED_ACK_SENT							( (unsigned char) 0x80 )
#define SLAVE_DATA_RECEIVED_NACK_SENT							( (unsigned char) 0x88 )
#define GENERAL_CALL_DATA_RECEIVED_ACK_SENT						( (unsigned char) 0x90 )
#define GENERAL_CALL_DATA_RECEIVED_NACK_SENT					( (unsigned char) 0x98 )
#define STOP_REPEATED_START_RECEIVED							( (unsigned char) 0xA0 )

// Slave transmitter mode
#define SLAVE_READ_RECEIVED_ACK_SENT							( (unsigned char) 0xA8 )
#define ARBITRATION_LOST_SLA_RW_as_MASTER_SLA_R_ACK__SENT		( (unsigned char) 0xB0 )
#define TWDR_SENT_ACK											( (unsigned char) 0xB8 )
#define TWDR_SENT_NACK											( (unsigned char) 0xC0 )
#define LAST_BYTE_in_TWDR_ACK									( (unsigned char) 0xC8 )

// Miscellaneous states
#define NO_INFORMATION						( (unsigned char) 0xF8 )
#define BUS_ERROR							( (unsigned char) 0x00 )


// defining commands
#define sendStart			( TWCR |= (1<<TWSTA) | (1<<TWINT) )
#define sendStop			( TWCR |= (1<<TWSTO) | (1<<TWINT) )
#define clearTWINT			( TWCR |= (1<<TWINT) )
#define sendACK				( TWCR |= (1<<TWEA) )
#define sendNACK			( TWCR &= ~(1<<TWEA) )


// class for TWI Library
class _TWI {
	
	// public functions of class
	public:
		// initialization functions
		void init ( bool Clock, bool enableGeneralCall, unsigned char ownAddress );
		
		// master sending functions, using overloading
		void masterSend ( unsigned char slaveAddress, unsigned char data );
		void masterSend ( unsigned char slaveAddress, unsigned char *data );
		
		// master receiving functions
		unsigned char masterReceive ( unsigned char slaveAddress );
		unsigned char * masterReceiveString ( unsigned char slaveAddress );
		
		// slave transmitting functions
		void slaveSend ( unsigned char masterAddress, unsigned char data );
		void slaveSend ( unsigned char masterAddress, unsigned char *data );
		
		// slave receive functions
		unsigned char slaveReceive ( unsigned char address );
		unsigned char * slaveReceiveString ( unsigned char address );
		
		// interrupt functions
		void enableInterrupt ( void );
	
	};



#endif /* TWI_LIB_H_ */