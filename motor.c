/*********************************************************************************************/
/* Name: motor.c                                                                             */
/* Author: Madonna Magdy                                                                     */
/* Version: V2                                                                               */
/* Usage: This module contains the implementation for the dc motor driver configurations     */
/*********************************************************************************************/


#ifndef MOTOR_C_
#define MOTOR_C_

/************************************************************************/
/*                            Includes                                  */
/************************************************************************/
#include"lstd.h"
#include "dio.h"
#include"timer.h"

#include"motor.h"
/************************************************************************/
/*                             static functions                         */
/************************************************************************/


/* these functions are static because it is not allowded to be called by other files
 * it can be only called by other functions in this folder by using pointer to function or by normal calling of the function*/


void static  DC_MOTOR_CLOCK_WISE(void){

	 mdio_setPinValue(PORTB_ID, PIN0_ID, DIO_HIGH_OUTPUT);  /* the output value of pin0  is 1 ---> INT1   */
	 mdio_setPinValue(PORTB_ID, PIN1_ID, DIO_LOW_OUTPUT);   /* the output value of pin1  is 0 ---> INT2   */

      return;/* return from this function*/

}



void static  DC_MOTOR_ANTI_CLOCK_WISE(void){

	mdio_setPinValue(PORTB_ID, PIN0_ID, DIO_LOW_OUTPUT);/* the output value of pin0  is 0 ---> INT1  */
	mdio_setPinValue(PORTB_ID, PIN1_ID, DIO_HIGH_OUTPUT);/* the output value of pin1  is 1 ---> INT2   */

    return;/* return from this function*/
}




void static DC_MOTOR_STOP(void){

	mdio_setPinValue(PORTB_ID,PIN0_ID, DIO_LOW_OUTPUT); /* the output value of pin0  is 0 ---> INT1  */
	mdio_setPinValue(PORTB_ID,PIN1_ID, DIO_LOW_OUTPUT);  /* the output value of pin1  is 0 ---> INT2   */

	return;/* return from this function*/
}




/************************************************************************/
/*                           constant  pointers to functions            */
/************************************************************************/

/*

void  (* const pointer_dcmotor_state[3])(void)={
	DC_MOTOR_CLOCK_WISE,
	DC_MOTOR_ANTI_CLOCK_WISE,
	DC_MOTOR_STOP
};

*/

void (* const pointer_dcmotor_pwmspeed)(u8_t au8_timerChannel,u8_t au8_pwmOperation,u8_t au8_dutyCycle)=mtimer_pwmGenerate;
/* constant pointer to function ----> the pointer is constant because the pointer will not point to  another address of a function
 * if the developer tried to change the value of it , the compiler will give error
 * the pointer will be initialized with mtimer_pwmGenerate in the timer driver  */
/* the input will be the duty cycle and the channel needed for selecting the pwm
 *  and the operation of the timer ---> start or stop it  */



void (*const pointer_clockWise)(void)=DC_MOTOR_CLOCK_WISE;

/*initialize that pointer with the DC_MOTOR_CLOCK_WISE*/
/* the pointer is constant to make sure that it is pointing (DC_MOTOR_CLOCK_WISE) only
 * and not pointing to another function and if the developer tried to change the value of it , the compiler will give error*/


void (*const pointer_antiClockWise)(void)=DC_MOTOR_ANTI_CLOCK_WISE;

/*initialize that pointer with the DC_MOTOR_ANTI_CLOCK_WISE*/
/* the pointer is constant to make sure that it is pointing (DC_MOTOR_CLOCK_WISE) only
 * and not pointing to another function and if the developer tried to change the value of it , the compiler will give error*/


void (*const pointer_stop)(void)=DC_MOTOR_STOP;

/*initialize that pointer with the DC_MOTOR_STOP*/
/* the pointer is constant to make sure that it is pointing (DC_MOTOR_CLOCK_WISE) only
 * and not pointing to another function and if the developer tried to change the value of it , the compiler will give error*/




/************************************************************************/
/*                             function definitions                     */
/************************************************************************/

void DcMotor_Init(void){

	mdio_setPinStatus(PORTB_ID,PIN0_ID, DIO_OUTPUT_PIN);
	mdio_setPinStatus(PORTB_ID,PIN1_ID, DIO_OUTPUT_PIN); /* the micro-controller supply voltage or current  to l23D so
	                                                         the direction of pins will be output*/

	(*pointer_stop)(); /*pointer to function for stopping the motor*/

	}


void DcMotor_Rotate(DcMotorState_t state,u8_t speed,u8_t au8_Operation)
{

	 (*pointer_dcmotor_pwmspeed)(MTIMER_CHANNEL_0,au8_Operation,speed);
	 //pointer_dcmotor_state[state];

    switch(state){

    case DC_CW:
    	(*pointer_clockWise)();/*pointer to function for rotating the  motor in clockwise direction*/
    	//pointer_dcmotor_state[DC_CW];

    	break; /* break from this case */

   case DC_ACW:
    	(*pointer_antiClockWise)(); /*pointer to function for rotating the  motor in anti-clockwise direction*/
	   //pointer_dcmotor_state[DC_ACW];

    	break;/* break from this case */

    case DC_STOP:
    	 (*pointer_stop)();         /*pointer to function for stopping the motor*/
    	//pointer_dcmotor_state[DC_STOP];

         break;/* break from this case */

        }

	 }

#endif /* MOTOR_C_ */


