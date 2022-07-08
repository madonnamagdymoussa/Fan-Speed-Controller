/******************************************************************************************************/
/* Name: temperature_sensor.c                                                                         */
/* Author: Madonna Magdy                                                                              */
/* Version: V2                                                                                        */
/* Usage: This module contains the implementation for the temperature sensor driver configurations    */
/******************************************************************************************************/


/************************************************************************/
/*                            Includes                                  */
/************************************************************************/
#include "lstd.h"
#include "adc.h"
#include "temperature_sensor.h"



/************************************************************************/
/*                            Definition                               */
/************************************************************************/


u8_t LM35_getTemperature()
{
	u8_t temp_value = 0;

	u16_t adc_value = 0;

	/* Read ADC channel where the temperature sensor is connected */
	adc_value = ADC_readChannel(MADC_CHANNEL_2);

	/* Calculate the temperature from the ADC value*/

	temp_value = (u8_t)(((u32_t)adc_value*SENSOR_MAX_TEMPERATURE*ADC_REF_VOLT_VALUE)/(ADC_MAXIMUM_VALUE*SENSOR_MAX_VOLT_VALUE));


	return temp_value;
}


