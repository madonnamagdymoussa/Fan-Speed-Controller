
/*********************************************************************************************/
/* Name: timer.c                                                                             */
/* Author: Madonna Magdy                                                                     */
/* Version: V2                                                                               */
/* Usage: This module contains the implementation for the timer peripheral configurations    */
/*********************************************************************************************/




/************************************************************************/
/*                            Includes                                  */
/************************************************************************/

#include"dio.h"
#include <avr/interrupt.h>
#include"lbit.h"
#include"timer_hardware_register.h"

#include"timer.h"

/************************************************************************/
/*                            Timer global variables                    */
/************************************************************************/

/*Global variable used to hold the selected timer0 prescaler*/
static u8_t gu8_timerSelectedPrescaler0;

/*Global variable used to hold the selected timer1 prescaler*/
static u8_t gu8_timerSelectedPrescaler1;

/*Global variable used to hold the selected timer2 prescaler*/
static u8_t gu8_timerSelectedPrescaler2;

/*It is not preferable to start the timer at the initialization function
 * once there is a selected pre-scaler inserted in the timer control register the timer will start counting
 * It is more preferable to have a function for starting the timer and for stopping the timer
 * so the value of the selected  pre-scaler will be copied into a global variable that hold the value of the pre-scaler
 * the global variable that hold the selected pre-scaler will be inserted into the timer counter control register in the
 * function of start timing and stop timing
 *
 */


/*Global variable used to indicate whether timer pwm is running or not*/
static u8_t gu8_pwmTimerIsRunning;

/*Global variable used to set the delay time in milliseconds for timer0*/
static u16_t gu16_delayTimeInMillis0;

/*Global variable used to set the delay time in milliseconds for timer1*/
static u16_t gu16_delayTimeInMillis1;

/*Global variable used to set the delay time in milliseconds for timer2*/
static u16_t gu16_delayTimeInMillis2;



/* An array of functions handlers each with an id.*/
 function_register_t volatile func_register[FUNC_REGISTER_SIZE];

/************************************************************************/
/*                          Functions' definitions                      */
/************************************************************************/

 void RegisterCallback (u8_t function_id, CallbackFunc_t p_callback_func ) {


     if ((0 < function_id) && (function_id <= FUNC_REGISTER_SIZE)) {

                     func_register[function_id].function_id = function_id;
                     func_register[function_id].gp_timer_callback_func = p_callback_func;
            }
 }




ISR(TIMER0_COMP_vect)
     {
     	func_register[TIMER0_ID].gp_timer_callback_func;
     }


 ISR(TIMER1_COMPA_vect)
 {
 	func_register[TIMER1_ID].gp_timer_callback_func;
 }


 ISR(TIMER2_COMP_vect)
     {
     	func_register[TIMER2_ID].gp_timer_callback_func;
     }


 void static mtimer_start(u8_t au8_timerChannel)
{
	/*Switching over timer channels*/
	switch(au8_timerChannel)
	{
		/*In case of choosing timer channel 0*/
		case MTIMER_CHANNEL_0:

			/*Resetting the timer counter*/
			MTIMER_TCNT0 = 0;

			/*Adding the previous selected timer prescaler*/
			MTIMER_TCCR0 |= gu8_timerSelectedPrescaler0;

			/*Break from this case*/
			break;

		/*In case of choosing timer channel 1*/
		case MTIMER_CHANNEL_1:

            /*Reset the timer counter*/
            MTIMER_TCNT1 = 0;

			/*Adding the previous selected timer prescaler*/
            MTIMER_TCCR1B |= gu8_timerSelectedPrescaler1;

			/*Break from this case*/
			break;

		/*In case of choosing timer channel 2*/
		case MTIMER_CHANNEL_2:

			/*Break from this case*/
			break;
	}

	/*Return from this function*/
	return;
}

 void static mtimer_stop(u8_t au8_timerChannel)
{
	/*Switching over timer channels*/
	switch(au8_timerChannel)
	{
		/*In case of choosing timer channel 0*/
		case MTIMER_CHANNEL_0:

			/*Stopping the timer by removing the prescaler value*/
			MTIMER_TCCR0 &= MTIMER_NO_PRESCALING;

			/*Break from this case*/
			break;

		/*In case of choosing timer channel 1*/
		case MTIMER_CHANNEL_1:

            /*Stopping the timer by removing the prescaler value*/
			MTIMER_TCCR1B &= (0xF8);

            /*Break from this case*/
			break;

		/*In case of choosing timer channel 2*/
		case MTIMER_CHANNEL_2:

			/*Break from this case*/
			break;
	}

	/*Return from this function*/
	return;
}

void mtimer_init(u8_t au8_timerChannel, u8_t au8_timerMode, u8_t au8_timerPrescaler)
{
	/*Switching over timer channels*/
	switch(au8_timerChannel)
	{
		/*In case of choosing timer channel 0*/
		case MTIMER_CHANNEL_0:

			/*Switching over timer modes*/
			switch(au8_timerMode)
			{
				/*In case of delay mode*/
				case MTIMER_DELAY_MODE:

					/*Setting the OCR0 value to create 1ms of delay
					 * MTIMER_DELAY_PRESCALER is equal to (MTIMER_PRESCALER_8)
					 * so  the frequency will be (10^6)/8 = 125,000
					 * the tick time is equal to 8*(10^-6)
					 *   125 * tick time = 1ms of delay
					 *
					 * */
					MTIMER_OCR0 = 125;

					/*Setting the CTC mode and stopping the timer*/
					MTIMER_TCCR0 = (1<<TCCR0_WAVE_GENERATION_CTC) | (1<<TCCR0_FORCE_OUTPUT_COMPARE);

					/*Break from this case --> delay mode*/
					break;

                /*In case of PWM mode*/
				case MTIMER_PWM_MODE:

               /*Setting Fast PWM with non inverting mode*/
                  MTIMER_TCCR0 = (1<<(TCCR0_WAVE_GENERATION_PWM))|(1<<(TCCR0_COMPARE_MATCH_01))|(1<<(TCCR0_WAVE_GENERATION_CTC));

                  mdio_setPinStatus(PORTB_ID, PIN3_ID, DIO_OUTPUT_PIN);
                  mdio_setPinValue(PORTB_ID, PIN3_ID, DIO_HIGH_OUTPUT);


                  /*Break from this case --> pwm mode*/
                  break;


			}

            /*Setting the timer0 prescaler*/
			gu8_timerSelectedPrescaler0 = au8_timerPrescaler;

			/*Break from this case  ---> Channel 0 */
			break;




		/*In case of choosing timer channel 1*/
		case MTIMER_CHANNEL_1:

			/*Switching over timer modes*/
			switch(au8_timerMode)
			{
				/*In case of delay mode*/
				case MTIMER_DELAY_MODE:

					/*Setting the OCR0 value to create 1ms of delay
					 * MTIMER_DELAY_PRESCALER is equal to (MTIMER_PRESCALER_8)
					 * so  the frequency will be (10^6)/8 = 125,000
					 * the tick time is equal to 8*(10^-6)
					 *   125 * tick time = 1ms of delay
					 *
					 * */
					 MTIMER_OCR1A = 125;

					 /*non-pwm mode*/
					 SET_BIT(MTIMER_TCCR1A ,TCCR1A_FORCE_OUTPUT_COMPARE_CHANNELA);

                     SET_BIT(MTIMER_TCCR1B,TCCR1B_WAVE_GENERATION_12);

					/*Break from this case*/
					break;

                /*In case of PWM mode*/
				case MTIMER_PWM_MODE:


                    /*Breaking from this case*/
                    break;

                /*In case of Input capture mode*/
				case MTIMER_INPUT_CAPT_MODE:

                    /*Setting the timer to operate at normal mode and ICU operates at falling edge (default)*/
                    MTIMER_TCCR1 = 0;

                    /*Breaking from this case --> input capture mode*/
                    break;

			}

			/*Setting the timer1 prescaler*/
			gu8_timerSelectedPrescaler1 = au8_timerPrescaler;

			/*Break from this case*/
			break;

		/*In case of choosing timer channel 2*/
		case MTIMER_CHANNEL_2:

			/*Setting the timer2 prescaler*/
			gu8_timerSelectedPrescaler2 = au8_timerPrescaler;

			/*Break from this case*/
			break;
	}

	/*Return from this function*/
	return;
}

void mtimer_delayMs_async(u8_t au8_timerChannel, u16_t au16_timerInMillis,CallbackFunc_t p_callback_func)
{
	/*Starting the timer with specific channel*/
	mtimer_start(au8_timerChannel);

	/*Enable the global interrupts*/
	SET_BIT(SREG, 7);

	/*Switching over timer channels*/
	switch(au8_timerChannel)
	{
		/*In case of choosing timer channel 0*/
		case MTIMER_CHANNEL_0:

			/*Setting the delay time to be used in ISR*/
			gu16_delayTimeInMillis0 = au16_timerInMillis;

			/*Setting the timer0 callback function*/
			 RegisterCallback (TIMER0_ID, p_callback_func );

			/*Enabling the OC interrupt*/
			SET_BIT(MTIMER_TIMSK, 1);

			/*Break from this case*/
			break;

		/*In case of choosing timer channel 1*/
		case MTIMER_CHANNEL_1:

			/*Setting the delay time to be used in ISR*/
			gu16_delayTimeInMillis1 = au16_timerInMillis;

			/*Setting the timer1 callback function*/
			RegisterCallback (TIMER1_ID, p_callback_func );

			/*Break from this case*/
			break;

		/*In case of choosing timer channel 2*/
		case MTIMER_CHANNEL_2:

			/*Setting the delay time to be used in ISR*/
			gu16_delayTimeInMillis2 = au16_timerInMillis;

			/*Setting the timer2 callback function*/
			RegisterCallback (TIMER2_ID, p_callback_func );

			/*Break from this case*/
			break;
	}

	/*Return from this function*/
	return;
}

void mtimer_delayMs_sync(u8_t au8_timerChannel, u16_t au16_timerInMillis)
{
	/*Starting the timer with specific channel*/
	mtimer_start(au8_timerChannel);

	/*Switching over timer channels*/
	switch(au8_timerChannel)
	{
		/*In case of choosing timer channel 0*/
		case MTIMER_CHANNEL_0:

			/*Looping over the time in millis*/
			while(au16_timerInMillis--)
			{
				/*Waiting for timer compare match to happen*/
				while(GET_BIT(MTIMER_TIFR, 1) == 0);

				/*Clearing the OCF0 flag*/
				SET_BIT(MTIMER_TIFR, 1);
			}

			/*Break from this case*/
			break;

		/*In case of choosing timer channel 1*/
		case MTIMER_CHANNEL_1:
			/*Looping over the time in millis*/
						while(au16_timerInMillis--)
						{
							/*Waiting for timer compare match to happen*/
							while(GET_BIT(MTIMER_TIFR, 4) == 0);

							/*Clearing the OCF0 flag*/
							SET_BIT(MTIMER_TIFR, 4);
						}



			/*Break from this case*/
			break;

		/*In case of choosing timer channel 2*/
		case MTIMER_CHANNEL_2:

			/*Break from this case*/
			break;
	}

	/*Stopping the started timer channel*/
	mtimer_stop(au8_timerChannel);

	/*Return from this function*/
	return;
}

void mtimer_pwmGenerate(u8_t au8_timerChannel, u8_t au8_pwmOperation, u8_t au8_dutyCycle)
{
    /*Switching over PWM operation*/
    switch(au8_pwmOperation)
    {
        /*Running the PWM*/
        case MTIMER_PWM_RUN:

            /*Checking if the timer has started once or not*/
            if(gu8_pwmTimerIsRunning == 0)
            {
                /*Starting a specific timer channel*/
                mtimer_start(au8_timerChannel);

                /*Increase the timer is running variable*/
                gu8_pwmTimerIsRunning++;
            }
            else
            {
                /*Do nothing*/
            }

            /*Break from this case*/
            break;

        /*Stopping the PWM*/
        case MTIMER_PWM_STOP:

            /*Stopping the timer*/
            mtimer_stop(au8_timerChannel);

            /*Reset the timer is running variable*/
            gu8_pwmTimerIsRunning = 0;

            /*Break from this case*/
            break;
    }


	/*Switching over timer channels*/
	switch(au8_timerChannel)
	{
		/*In case of choosing timer channel 0*/
		case MTIMER_CHANNEL_0:

            /*Setting the duty cycle value (0 - 255)*/
            MTIMER_OCR0 = au8_dutyCycle;

             //mdio_setPinStatus(PORTB_ID, PIN3_ID, DIO_OUTPUT_PIN);
             //mdio_setPinValue(PORTB_ID, PIN3_ID, DIO_HIGH_OUTPUT);

			/*Break from this case*/
			break;

		/*In case of choosing timer channel 1*/
		case MTIMER_CHANNEL_1:

			/*Setting the duty cycle value (0 - 255)*/
			MTIMER_OCR1A = au8_dutyCycle;

			/*Break from this case*/
			break;

		/*In case of choosing timer channel 2*/
		case MTIMER_CHANNEL_2:

			/*Break from this case*/
			break;
	}

	/*Return from this function*/
	return;
}

void mtimer_getPwmStatus(u8_t* pu8_dutyCycle, u32_t* pu32_frequency)
{
    /*Local variables used to get PWM signal time stamps*/
    u16_t au16_t1;
    u16_t au16_t2;
    u16_t au16_t3;

    /*Trigger ICU at rising edge */
    SET_BIT(MTIMER_TCCR1, 6);

    /*Start timer channel 1*/
    mtimer_start(MTIMER_CHANNEL_1);

    /*Waiting for selected edge to trigger ICU*/
    while(GET_BIT(MTIMER_TIFR, 5) == 0);

    /*Clearing ICF1 flag*/
    SET_BIT(MTIMER_TIFR, 5);

    /*Get the first time stamp*/
    au16_t1 = MTIMER_ICR1;

    /*Trigger ICU at falling edge */
    CLEAR_BIT(MTIMER_TCCR1, 6);

    /*Waiting for selected edge to trigger ICU*/
    while(GET_BIT(MTIMER_TIFR, 5) == 0);

    /*Clearing ICF1 flag*/
    SET_BIT(MTIMER_TIFR, 5);

    /*Get the second time stamp*/
    au16_t2 = MTIMER_ICR1;

    /*Trigger ICU at rising edge */
    SET_BIT(MTIMER_TCCR1, 6);

    /*Waiting for selected edge to trigger ICU*/
    while(GET_BIT(MTIMER_TIFR, 5) == 0);

    /*Clearing ICF1 flag*/
    SET_BIT(MTIMER_TIFR, 5);

    /*Get the third time stamp*/
    au16_t3 = MTIMER_ICR1;

    /*Stop timer channel 1*/
    mtimer_stop(MTIMER_CHANNEL_1);

    /*Getting the duty cycle in %*/
    *pu8_dutyCycle = (u8_t)(( (f32_t)(au16_t2 - au16_t1) / (f32_t)(au16_t3 - au16_t1)) * 100.0);

    /*Getting the frequency in Hz*/
    *pu32_frequency = 250000 / (au16_t3 - au16_t1);

	/*Return from this function*/
	return;
}

