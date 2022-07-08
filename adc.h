#ifndef ADC_H_
#define ADC_H_

/******************************************************************************************************/
/* Name: adc.h                                                                                        */
/* Author: Madonna Magdy                                                                              */
/* Version: V3                                                                                        */
/* Usage: This module contains the interface definitions for the adc peripheral                       */
/******************************************************************************************************/



/************************************************************************/
/*                            Includes                                  */
/************************************************************************/

#include"lstd.h"

/************************************************************************/
/*                            Macros                                    */
/************************************************************************/

/*name of each bit in adc control status register */
#define ADC_Prescaler_Select_0   (0)            /*bit0*/
#define	ADC_Prescaler_Select_1   (1)          /*bit1*/
#define	ADC_Prescaler_Select_2   (2)          /*bit2*/
#define	ADC_Interrupt_Enable     (3)         /*bit3*/
#define	ADC_Interrupt_Flag       (4)         /*bit4*/
#define	ADC_Auto_Trigger_Enable  (5)        /*bit5*/
#define	ADC_Start_Conversion     (6)         /*bit6*/
#define	ADC_Enable               (7)          /*bit7*/

#define ADC_MAXIMUM_VALUE    (1023)

/************************************************************************/
/*                            typedefs                                  */
/************************************************************************/

/**
 * Defines the number of each pre_scaler value
 */

typedef enum{

	 MADC_PRE_2 =1,
	 MADC_PRE_4,
	 MADC_PRE_8,
	 MADC_PRE_16,
	 MADC_PRE_32,
	 MADC_PRE_64,
	 MADC_PRE_128,

	 MADC_PRE_NUMBER =7    // the user must enter a number less than or equal MADC_PRE_NUMBER
} Adc_Prescaler_t;


/**
 * Defines the number of each channel value
 */
typedef enum{


	 MADC_CHANNEL_0,
	 MADC_CHANNEL_1,
	 MADC_CHANNEL_2,
	 MADC_CHANNEL_3,
	 MADC_CHANNEL_4,
     MADC_CHANNEL_5,
	 MADC_CHANNEL_6,
	 MADC_CHANNEL_7,

	 MADC_CHANNEL_NUMBER    //the number of the adc channel the user must enter a number less than or equal MADC_CHANNEL_NUMBER

} AdcChannel_t;


/**
 * Defines the  resolution values that will be inserted in the control and status register
 */
typedef enum{
	 MADC_RES_10_BITS, MADC_RES_8_BITS =0x20

} AdcResolution_t;


/**
 * Defines the  voltage reference selection values that will be inserted in the control and status register
 */
typedef enum{
 MADC_VREF_AREF_PIN,
 MADC_VREF_AVCC_PIN  =0x40,
 MADC_INT_VREF_2_56V =0xC0

}Adc_ReferenceVoltage_t;

typedef struct{

	Adc_ReferenceVoltage_t ref_volt ;
	Adc_Prescaler_t prescaler;


}ADC_ConfigType;


/* Function    : ADC_init
 *
 *INPUT:       *Config_Ptr
 * Description : This function is responsible for initializing adc driver
 *
 *PRE_CONDITION: the pointer Config_Ptr will be pointing to elements in the structure with the maximum ADC_ConfigType definition
 *
 *POST_CONDITION:the adc driver will be initialized
 *
 * Return: void
 *
 * */


void ADC_init(const ADC_ConfigType *Config_Ptr);


/* Function    : DcMotor_Rotate
 *
 * Description : This function is responsible for reading the value in adc register
 *
 *INPUT        :au8_adcChannel
 *
 *PRE_CONDITION: ADC driver must be initialized
 *
 *PRE_CONDITION: the selected au8_adcChannel  is considered within the maximum AdcChannel_t definition
  *
 *POST_CONDITION:the value related to the selected channel will be read
 *
 * Return: adc value in adc register
 *
 * */

u16_t ADC_readChannel(AdcChannel_t au8_adcChannel);

#endif /* ADC_H_ */
