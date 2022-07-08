#ifndef ADC_HARDWARE_REGISTER_H_
#define ADC_HARDWARE_REGISTER_H_

/************************************************************************/
/*                            ADC Registers                             */
/************************************************************************/

#define MADC_ADMUX     (*(volatile u8_t* const)(0x27))
#define MADC_ADCSRA    (*(volatile u8_t* const)(0x26))
//#define MADC_ADCH     (*(volatile u8_t* const)(0x25))
//#define MADC_ADCL     (*(volatile u8_t* const)(0x24))
#define MADC_ADC        (*(volatile u16_t* const)(0x24))


#endif /* ADC_HARDWARE_REGISTER_H_ */
