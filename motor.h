/******************************************************************************************************/
/* Name: motor.h                                                                                       */
/* Author: Madonna Magdy                                                                              */
/* Version: V2                                                                                        */
/* Usage: This module contains the interface definitions for the motor driver                         */
/******************************************************************************************************/



#ifndef MOTOR_H_
#define MOTOR_H_

/************************************************************************/
/*                            Includes                                  */
/************************************************************************/
#include"timer.h"

/************************************************************************/
/*                           MACROS                                     */
/************************************************************************/

#define motor_speed_25  (DUTY_CYCLE_25_PERCENT)
#define motor_speed_50   (DUTY_CYCLE_50_PERCENT)
#define motor_speed_75  (DUTY_CYCLE_75_PERCENT)
#define motor_speed_100  (DUTY_CYCLE_100_PERCENT)


/************************************************************************/
/*                            typedefs                                  */
/************************************************************************/

typedef enum{
	DC_CW,
	DC_ACW,
	DC_STOP

}DcMotorState_t;

/* possible states for the dc motor */


/************************************************************************/
/*                           prototypes                                */
/************************************************************************/

//void volatile ( *volatile pointer_dcmotor_state[3])(void);


/* Function    : DcMotor_Init
 *
 * Description : This function is responsible initializing the dc motor
 *
 * INPUT: VOID
 *
 *PRE_CONDITION: the digital input/output driver must be configured
 *
 *POST_CONDITION: the motor will be stopped as an initial value for direction
 *POST_CONDITION: pin0 and pin1 will be have an output direction
 *
 * Return: void
 *
 * */


void DcMotor_Init(void);


/* Function    : DcMotor_Rotate
 *
 * Description : This function is responsible for rotating the dc motor
 *
 *PRE_CONDITION: DC motor must be initialized
 *
 *PRE_CONDITION: the selected state or pin is considered within the maximum DcMotorState_t definition
 *PRE_CONDITION: the selected speed is considered within the maximum definition of macros duty cycles
 *PRE_CONDITION: the selected au8_Operation is considered MTIMER_PWM_STOP or MTIMER_PWM_RUN
 *
 *POST_CONDITION:the motor will be rotating with Speed equal to u8_t speed and in direction based on DcMotorState_t state
 *
 * Return: void
 *
 * */

void DcMotor_Rotate(DcMotorState_t state,u8_t speed,u8_t au8_Operation);



#endif /* MOTOR_H_ */
