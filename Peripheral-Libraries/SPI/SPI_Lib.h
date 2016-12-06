/*
 * SPI_Lib.h
 *
 * Created: 10/19/2016 3:21:32 PM
 *  Author: heman
 */ 


#ifndef SPI_LIB_H_
#define SPI_LIB_H_

#include <avr/interrupt.h>
#define F_CPU 8000000UL

#define dummy			( (unsigned char) 0x00 )
#define DoubleSPISpeed	1						// Set as 1 to make speed double using SPI2X bit in SPSR register
#define useMISO			0

// define SPI pins
#define MOSI			(1<<PB5)
#define MISO			(1<<PB6)
#define SCK				(1<<PB7)
#define SS				(1<<PB4)

// define Slave pins
#define setSlaveLow( port, x )		( port &= ~(1<<x) )
#define setSlaveHigh( port, x )		( port |= (1<<x) )

#define defaultSlavePin		0

// declare enum for frequency set
enum _SPI_Clock {
	Fclk_4 = 0,
	Fclk_16 = 1,
	Fclk_64 = 2,
	Fclk_128 = 3
};


class _SPI {
	// declaring public member functions
	public:
		void init ( bool mode, bool dataOrder, bool polarity, bool phase, _SPI_Clock clock );
		unsigned char masterSend ( unsigned char data );
		void send ( unsigned char data );
		unsigned char receive ( void );
		
		// master port send
		// accept PORTA/B/C/D as second argument and pin
		unsigned char masterPortSend ( unsigned char data, volatile unsigned char *port, uint8_t slavePin );
		
		// interrupt functions
		void enableInterrupt ( void );	
		
	};


#endif /* SPI_LIB_H_ */