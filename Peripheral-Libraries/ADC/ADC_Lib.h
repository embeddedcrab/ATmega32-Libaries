/*
 * ADC_Lib.h
 *
 * Created: 10/15/2016 12:12:05 PM
 *  Author: heman
 */ 


#ifndef ADC_LIB_H_
#define ADC_LIB_H_

#include <avr/io.h>

// uncomment if external voltage reference is selected
#define ADCExternalReferenceSelection		1
#define ADCLeftAdjustResult					0
#define ADCAutoTriggerEnable				0


class _ADC {
	
	private:
		// start function
		void startConversion ( void );
	
	public:
		// initialization functions
		void init ( uint8_t prescaler );
		
		// get value from adc channel function
		uint16_t getChannelValue ( uint8_t channel );
		
		// interrupt enable function
		void enableInterrupt ( void );
	};


#endif /* ADC_LIB_H_ */