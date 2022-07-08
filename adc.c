/******************************************************************************************************/
/* Name: adc.c                                                                                        */
/* Author: Madonna Magdy                                                                              */
/* Version: V2                                                                                        */
/* Usage: This module contains the implementation for the adc peripherals configurations              */
/******************************************************************************************************/

/************************************************************************/
/*                            Includes                                  */
/************************************************************************/
#include "adc.h"
#include"adc_hardware_register.h"
#include"lbit.h"
#include"lstd.h"


/************************************************************************/
/*                            function definitions                     */
/************************************************************************/


void ADC_init(const ADC_ConfigType *Config_Ptr){

	/*Resetting the ADMUX register*/
		MADC_ADMUX=0;

		/*Resetting ADCSRA register*/
		 MADC_ADCSRA=0;

		 /*Setting the Vref and resolution modes*/
	     MADC_ADMUX |=(Config_Ptr->ref_volt);

	    /*enable the adc*/
		SET_BIT(MADC_ADCSRA,ADC_Enable);

		/*setting the pre_scalar*/
		/*for the adc will operate with a frequency ranging between 50Hz to 200Hz*/
	    MADC_ADCSRA |=(Config_Ptr->prescaler);

	/*Return from this function*/
				return;


}

u16_t ADC_readChannel(AdcChannel_t au8_adcChannel){


	au8_adcChannel &= 0x07; /* channel number must be from 0 --> 7 */

	MADC_ADMUX &= 0xE0; /*Resetting the selected ADC channel*/
	MADC_ADMUX |= au8_adcChannel; /*setting the selected ADC channel*/

    SET_BIT(MADC_ADCSRA,ADC_Start_Conversion); /*start converting the adc value */

    while (BIT_IS_CLEAR(MADC_ADCSRA,ADC_Interrupt_Flag)); // wait for the adc to complete conversion --> polling takes 13 clock cycles so it is more efficient than interrupt
    SET_BIT(MADC_ADCSRA,ADC_Interrupt_Flag); /*clear the flag bit after the conversion is complete */

    return MADC_ADC;

}

