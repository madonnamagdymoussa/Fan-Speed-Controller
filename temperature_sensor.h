/******************************************************************************************************/
/* Name: dio.h                                                                                        */
/* Author: Madonna Magdy                                                                              */
/* Version: V2                                                                                        */
/* Usage: This module contains the interface definitions for the timer driver                       */
/******************************************************************************************************/


#ifndef TEMPERATURE_SENSOR_H_
#define TEMPERATURE_SENSOR_H_

/************************************************************************/
/*                            Includes                                  */
/************************************************************************/
#include "lstd.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define	SENSOR_MAX_TEMPERATURE   (150)

#define SENSOR_MAX_VOLT_VALUE    (1.5)


#define ADC_REF_VOLT_VALUE       (2.56)

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/* Function    : LM35_getTemperature
 *
 * Description : Function responsible for calculate the temperature from the ADC digital value.
 *
 * INPUT: VOID
 *
 *PRE_CONDITION: the adc driver must be configured
 *
 *PRE_CONDITION: the selected channel must be within the maximum definition of AdcChannel_t
 *POST_CONDITION: the value of the temp will be calculated
 *
 * Return: the calculated value of type u8_t
 *
 * */
u8_t LM35_getTemperature();



#endif /* TEMPERATURE_SENSOR_H_ */
