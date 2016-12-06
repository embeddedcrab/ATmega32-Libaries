/*
 * SPI_Lib.cpp
 *
 * Created: 10/19/2016 3:21:18 PM
 *  Author: heman
 */ 


#include "SPI_Lib.h"
#include <avr/iom32.h>

void _SPI :: init ( bool mode, bool dataOrder, bool polarity, bool phase, _SPI_Clock clock ) {
	
	// define mode of SPI whether master or slave
	mode == 1 ? SPCR |= (1<<MSTR) : SPCR &= ~(1<<MSTR);
	
	// select mode of communication
	dataOrder == 1 ? SPCR |= (1<<DORD) : SPCR &= ~(1<<DORD);
	
	// select polarity of clock
	// When this bit is written to one, SCK is high when idle. When CPOL is written to zero, SCK is low when idle
	polarity == 1 ? SPCR |= (1<<CPOL) : SPCR &= ~(1<<CPOL);
	
	// select phase of clock
	phase == 1 ? SPCR |= (1<<CPHA) : SPCR &= ~(1<<CPHA);
	
	#if DoubleSPISpeed == 1
		SPSR |= (1<<SPI2X);
	#endif
	
	// select clock
	switch ( clock ) {
		case Fclk_4: {
			SPCR |= Fclk_4<<SPR0;
			break;
		}
		case Fclk_16: {
			SPCR |= Fclk_16<<SPR0;
			break;
		}
		case Fclk_64: {
			SPCR |= Fclk_64<<SPR0;
			break;
		}
		case Fclk_128: {
			SPCR |= Fclk_128<<SPR0;
			break;
		}
	}
	
	// enable SPI
	SPCR |= (1<<SPE);
	
	// set pin functionality
	# if useMISO == 1
		DDRB |= MISO;
	#endif
	
	DDRB |= MOSI | SCK;
	DDRB &= ~(SS);
	
	// make default pin as output
	DDRB |= 1<<defaultSlavePin;
	
	// set defaultSlavePin high to unselect
	setSlaveHigh( PORTB, defaultSlavePin );
	
}// init ends


unsigned char _SPI :: masterSend ( unsigned char data ) {
	
	// unselect pin to send data
	setSlaveLow( PORTB, defaultSlavePin );
	// send data to slave
	SPDR = data;
	
	// wait while transmission is not completed
	while ( !(SPSR & (1<<SPIF)) );
	// select to disable
	setSlaveHigh( PORTB, defaultSlavePin );
	return SPDR;
}

void _SPI :: send ( unsigned char data ) {
	
	// unselect pin to send data
	setSlaveLow( PORTB, defaultSlavePin );
	SPDR = data;
	// wait while transmission is not completed
	while ( !(SPSR & (1<<SPIF)) );
	// select to disable
	setSlaveHigh( PORTB, defaultSlavePin );
}

unsigned char _SPI :: receive ( void ) {
	
	// wait while transmission is not completed
	while ( !(SPSR & (1<<SPIF)) );
	return SPDR;
}


unsigned char _SPI :: masterPortSend ( unsigned char data, volatile unsigned char *port, uint8_t slavePin ) {
	
	*port &= ~(1<<slavePin);
	// send data to slave
	SPDR = data;
	// wait while transmission is not completed
	while ( !(SPSR & (1<<SPIF)) );
	*port |= (1<<slavePin);
	
	return SPDR;
}

// interrupt functions
void _SPI :: enableInterrupt ( void ) {
	
	// enable interrupt bit in SPCR
	SPCR |= (1<<SPIE);
}