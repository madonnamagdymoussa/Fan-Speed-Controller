/************************************************************************************/
/* Name: main.c                                                       */
/* Author: Madonna Magdy                                                            */
/* Version: V3                                                                      */

/************************************************************************************/


/************************************************************************/
/*                            Includes                                  */
/************************************************************************/


#include"dio.h"
#include"timer.h"
#include"adc.h"
#include"lcd.h"
#include"motor.h"
#include"temperature_sensor.h"


int main(void){

 	u8_t temperature; /*the temperature value will not be initialized
 	                   //because the first value read by the sensor will be it's initial value*/


    ADC_ConfigType ADC_Config={ MADC_INT_VREF_2_56V,MADC_PRE_8}; /* the values of ADC_Config could not be changed during runtime*/
 	ADC_init(&ADC_Config); /* initialize the pointer to structure */





	mtimer_init(MTIMER_CHANNEL_0, MTIMER_PWM_MODE, MTIMER_PWM_PRESCALER); /*initialize timer 0 for the pwm signals */
	mtimer_init(MTIMER_CHANNEL_1, MTIMER_DELAY_MODE, MTIMER1_DELAY_PRESCALER); /*initialize timer 1 for lcd */

	DcMotor_Init();

	LCD_init();
	LCD_clearScreen(); /* clear LCD at the beginning */

	LCD_displayStringRowColumn(0,2, "FAN is "); /* this value will be displayed during the whole program  */
	LCD_displayStringRowColumn(1,2, "Temp =    C"); /* this value will be displayed during the whole program  */



	for(; ;){


		 		temperature= LM35_getTemperature(); /* continuously reading the temperature from the sensor using adc */


		       if(temperature<30)
		 		{
		 			LCD_displayStringRowColumn(0,9, "OFF"); /* print the current state of the motor  */

		 			LCD_moveCursor(1,9);
		 			LCD_intgerToString(temperature); /* Display the current temperature  */
		 			LCD_displayStringRowColumn(1,11," ");

		 			if (temperature<10){
		 				LCD_displayStringRowColumn(1,10," ");
		 			}

		 			DcMotor_Rotate(DC_STOP,0,MTIMER_PWM_STOP);


		 		}


		 		 if((temperature>=30)&&(temperature<60))
		 		{
		 			LCD_displayStringRowColumn(0,9, "ON"); /* print the current state of the motor  */
		 			LCD_displayStringRowColumn(0,11," ");

		 			LCD_moveCursor(1,9);
		 			LCD_intgerToString(temperature); /* Display the current temperature  */
		 			LCD_displayStringRowColumn(1,11," ");

		 			DcMotor_Rotate(DC_CW,motor_speed_25,MTIMER_PWM_RUN);


		 		}

		 		 if((temperature>=60)&&(temperature<90)){
		 			LCD_displayStringRowColumn(0,9, "ON"); /* print the current state of the motor  */
		 			LCD_displayStringRowColumn(0,11," ");

		 			LCD_moveCursor(1,9);
		 			LCD_intgerToString(temperature); /* Display the current temperature  */
		 			LCD_displayStringRowColumn(1,11," ");

		 			DcMotor_Rotate(DC_CW,motor_speed_50,MTIMER_PWM_RUN);

		 		}

		 		  if((temperature>=90)&&(temperature<120)){
		 			LCD_displayStringRowColumn(0,9, "ON"); /* print the current state of the motor  */
		 			LCD_displayStringRowColumn(0,11, " ");

		 			LCD_moveCursor(1,9);
		 			LCD_intgerToString(temperature); /* Display the current temperature  */

		 			if (temperature<100){

		 				LCD_displayStringRowColumn(1,11," ");
		 			}

		 			DcMotor_Rotate(DC_CW,motor_speed_75,MTIMER_PWM_RUN);

		 		}


		 		 if (temperature>=120){
		 			LCD_displayStringRowColumn(0,9, "ON"); /* print the current state of the motor  */
		 			LCD_displayStringRowColumn(0,11, " ");

		 			LCD_moveCursor(1,9);
		 			LCD_intgerToString(temperature); /* Display the current temperature  */

		 			DcMotor_Rotate(DC_CW,motor_speed_100,MTIMER_PWM_RUN);


		 		 }

	}





}

