/*
 * ADC_Lib.cpp
 *
 * Created: 10/15/2016 12:11:28 PM
 *  Author: heman
 */ 

#include "ADC_Lib.h" 

/*
 *	
 */
void _ADC :: init ( uint8_t prescaler ) {
	
	// only accept between 0 to 7 and 0 is default that is prescaler = 2
	if ( prescaler >= 0 ) {
		if ( prescaler < 8 ) {
			switch ( prescaler ) {
				case 1:	{
					ADCSRA |= (1<<ADPS0);		// Division factor = 2
					break;
				}
				case 2:	{
					ADCSRA |= (1<<ADPS1);		// Division factor = 4
					break;
				}
				case 3:	{
					ADCSRA |= (3<<ADPS0);		// Division factor = 8
					break;
				}
				case 4: {
					ADCSRA |= (1<<ADPS2);		// Division factor = 16
					break;
				}
				case 5: {
					ADCSRA |= (5<<ADPS0);		// Division factor = 32
					break;
				}
				case 6: {
					ADCSRA |= (3<<ADPS1);		// Division factor = 64
					break;
				}
				case 7: {
					ADCSRA |= (7<<ADPS0);		// Division factor = 128
					break;
				}
				default: {
					break;
				}
			}
		}
	}// if ends
	
	// Auto enable settings, have to add SFIOR functionality also, not included in this function
	#if ADCAutoTriggerEnable == 1
		ADCSRA |= (1<<ADATE);
	#endif
	
	// Reference voltage selection
	#if ADCExternalReferenceSelection == 1
		ADMUX |= (1<<REFS0);		// AVcc with external capacitor with Aref pin
	#elif ADCExternalReferenceSelection == 0
		ADMUX |= (3<<REFS0);
	#endif
	
	#if ADCLeftAdjustResult == 1
		ADMUX |= (1<<ADLAR);
	#endif
	
	// Enable ADC
	ADCSRA |= (1<<ADEN);	
}// init ends



/*
 *	
 */
void _ADC :: startConversion ( void ) {
	// start conversion
	ADCSRA |= (1<<ADSC);	
}


/*
 *	
 */
uint16_t _ADC :: getChannelValue ( uint8_t channel ) {
	
	// get local variable
	uint16_t value = 0;
	
	// unselect all channels first
	ADMUX &= ~(0x1F);
	// check channel value must lie in between 0 to 7
	if ( channel >= 0 ) {
		if ( channel < 8 ) {
			ADMUX |= channel;
		}
	}
	
	// start conversion
	//ADCSRA |= (1<<ADSC);
	startConversion ();
	// wait while conversion if not completed
	while ( !(ADCSRA & (1<<ADIF)) );
	ADCSRA |= (1<<ADIF);
	
	#if ADCLeftAdjustResult == 1
		uint8_t temp_value;
		temp_value = ADCL;
		value = ADCH;
		value <<= 8;		// shift high bytes
		value |= temp_value;		// get lower byte  
	#else
		value = ADC;
	#endif
	
	return value;
}


/*
 *	
 */
void _ADC :: enableInterrupt ( void ) {
	
	// enable ADC conversion complete interrupt
	ADCSRA |= (1<<ADIE);
}