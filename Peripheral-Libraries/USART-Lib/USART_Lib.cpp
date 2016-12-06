/*
 * USART_Lib.cpp
 *
 * Created: 10/13/2016 12:23:09 PM
 *  Author: heman
 */ 

#include "USART_Lib.h"

// USART initialization function
void _USART :: init( uint8_t charSize, bool mode, bool parity, bool stopBits, bool polarity ) {
	
	// define baud rate
	UBRRH = BAUD>>8;
	UBRRL = BAUD;
	
	#if defined useDoubleSpeedMode
		UCSRA |= (1<<U2X);
	#endif
	
	// making high to use UCSRC register
	UCSRC |= (1<<URSEL); 
	
	// define character size to be sent
	if ( charSize > 4 ) {
		if ( charSize < 10 ) {
			switch ( charSize ) {		// see data-sheet for values
				case 5: {// Do nothing
					break;
				}
				case 6: {
					UCSRC |= (1<<UCSZ0);
					break;
				}
				case 7: {
					UCSRC |= (2<<UCSZ0);
					break;
				}
				case 8: {
					UCSRC |= (3<<UCSZ0);
					break;
				}
				case 9: {
					UCSRC |= (3<<UCSZ0);
					UCSRB |= (1<<UCSZ2);
					break;
				}
					
			}
		}
	}// if ends
	
	// set mode of communication, if true then use synchronous mode
	UCSRC |= mode == 1 ? (1<<UMSEL) : /* Do Nothing  */ UCSRC;
	if ( mode == 1 ) {
		UCSRC |= polarity == 1 ? (1<<CPOL) : /* Do Nothing */ UCSRC;
	}
	
	// set parity
	if ( parity >= 0 ) {
		if ( parity < 3 ) {
			UCSRC |= !parity ? /* Do Nothing */ UCSRC : parity==1 ? (1<<UPM1) : parity==2 ? ( (1<<UPM1) | (1<<UPM0) ) : /* Do Nothing */ UCSRC;
		}
	}
	
	// set stop bits
	UCSRC |= stopBits == 1 ? (1<<USBS) : /* Do Nothing */  UCSRC;
	
	// enable Tx and Rx
	UCSRB |= (1<<TXEN) | (1<<RXEN);
}// init ends


/*------------------- USART transmission function -----------------------------*/
void _USART :: transmit ( const char data ) {
	// check for empty buffer
	while ( !(UCSRA & (1<<UDRE))  );		// wait
	UDR = data;			// put data into buffer
	// wait while data is not sent fully
	while( !(UCSRA & (1<<TXC)) );
}

void _USART :: print ( const char *data ) {
	// send data using pointers
	for ( unsigned int i=0; data[i] != '\0' ; i++ ) {
		transmit(data[i]);
	}
}

void _USART :: nprint ( const char *data, unsigned int len ) {
	// send data using pointers
	for ( unsigned int i=0; i<len; i++ ) {
		transmit(data[i]);
	}	
}


/*---------------- USART receiving functions ----------------------*/
char _USART :: receive ( void ) {
	//wait while data is not received
	while( !(UCSRA & (1<<RXC)) );
	if ( !(UCSRA & (1<<FE)) )
	return UDR;
	return USARTDummy;
}


char * _USART :: scan ( uint8_t length ) {
	
	// declare local and a pointer
	char *temp, *retAddress = NULL;
	uint8_t len;
	
	if ( (temp = (char *) malloc( sizeof(char) * (length+1) )) != NULL ) {		// +1 for '\0' to be appended at last
		// get starting address of memory allocated
		retAddress = temp;
		// start receiving
		for ( len=0; len<length; ++len ){
			*temp++ = receive();
		}
		*temp = '\0';		// append '\0' at last
	}
	else {
		nprint ("No Memory\r\n", sizeof("NoMemory\r\n") );
	}
	
	// return address of temp
	return retAddress;
}

// receive number of characters from USART Rx pin
// have to use received buffer here itself
void _USART :: nscan ( uint8_t length ) {
	// declare character pointer
	char temp[length+1];
	//set memory to '\0'
	memset( temp, '\0', sizeof(temp) );
	uint8_t len;
	// receive while terminating character is not received
	for ( len=0; len<length; ++len ){
		temp[len] = receive();
	}
	temp[len] = '\0';		// append '\0' at last
	print (temp);
}


void _USART :: printNumDynamic ( unsigned int num )
{
	char temp[10];
	unsigned int i = 0;
	
	do {
		temp[i++] = num%10 + '0' ;
		num /= 10;
	} while (num);
	
	while ( i ) {
		transmit  ( temp[--i] );
	}
}


void _USART :: printNum ( unsigned int num ) {
	
	// convert to character and send
	if ( num >= 0 && num < 10 ) {
		transmit ( num+48 );
	}
	else if ( num > 9 && num < 100 ) {
		transmit ( (num/10)+48 );
		transmit ( (num%10)+48 );
	}
	else if ( num > 99 && num < 999 ) {
		transmit ( (num/100)+48 );
		transmit ( ((num%100)/10)+48 );
		transmit ( ((num%10)%10)+48 );
	}
}

/*------------------------ USART Interrupt enable functions -------------------------*/
// select vary between 1 to 3 to define interrupt type
void _USART :: interruptEnable ( uint8_t select ) {
	
	if ( select > 0 ) {
		if ( select < 4 ) {
			switch ( select ) {
				case 1:	{
					UCSRB |= (1<<RXCIE);		// receive complete interrupt
					break;
				}
				case 2:	{
					UCSRB |= (1<<TXCIE);		// transmission complete interrupt
					break;
				}
				case 3:	{
					UCSRB |= (1<<UDRIE);		// UDR empty interrupt
					break;
				}
			}
		}
	}
}