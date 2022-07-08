
#ifndef TIMER_H_
#define TIMER_H_

/******************************************************************************************************/
/* Name: timer.h                                                                                      */
/* Author: Madonna Magdy                                                                              */
/* Version: V2                                                                                        */
/* Usage: This module contains the interface definitions for the timer peripheral                     */
/******************************************************************************************************/


/************************************************************************/
/*                            Includes                                  */
/************************************************************************/
#include"lstd.h"

/************************************************************************/
/*                           Interfacing macros                         */
/************************************************************************/

/*Timer channels*/
#define MTIMER_CHANNEL_0        (0)
#define MTIMER_CHANNEL_1        (1)
#define MTIMER_CHANNEL_2        (2)

/*Timer0 prescalers and Timer1 prescalers*/
#define MTIMER_NO_PRESCALING    (0xF8)
#define MTIMER_PRESCALER_1      (1)
#define MTIMER_PRESCALER_8      (2)
#define MTIMER_PRESCALER_64     (3)
#define MTIMER_PRESCALER_256    (4)
#define MTIMER_PRESCALER_1024   (5)

/*Delay pre-scaler*/
#define MTIMER1_DELAY_PRESCALER  (MTIMER_PRESCALER_8)
#define MTIMER2_DELAY_PRESCALER  (MTIMER_PRESCALER_8)

/*PWM Frequencies pre-scalers*/
#define MTIMER_PWM_PRESCALER    (MTIMER_PRESCALER_8)

/*Input capture unit pre-scaler*/
#define MTIMER_ICU_PRESCALER    (MTIMER_PRESCALER_64)


/*Fast PWM frequencies*/
#define MTIMER_FREQ_4_KHz       (MTIMER_PRESCALER_1)
#define MTIMER_FREQ_500_Hz      (MTIMER_PRESCALER_8)
#define MTIMER_FREQ_61_Hz       (MTIMER_PRESCALER_64)
#define MTIMER_FREQ_244_Hz      (MTIMER_PRESCALER_256)




/*Timer PWM operations*/
#define MTIMER_PWM_RUN          (1)
#define MTIMER_PWM_STOP         (0)

/*pwm duty cycle*/
#define DUTY_CYCLE_25_PERCENT    (64)
#define DUTY_CYCLE_50_PERCENT    (128)
#define DUTY_CYCLE_75_PERCENT    (193)
#define DUTY_CYCLE_100_PERCENT   (255)



/*Timer modes*/
#define MTIMER_DELAY_MODE       (0)
#define MTIMER_PWM_MODE         (1)
#define MTIMER_INPUT_CAPT_MODE  (2)


/*timer counter control register bits number --> TCCR0   */

#define TCCR0_CLOCK_SELECT_00        (0)
#define TCCR0_CLOCK_SELECT_01        (1)
#define TCCR0_CLOCK_SELECT_02        (2)
#define TCCR0_WAVE_GENERATION_PWM    (3)
#define TCCR0_COMPARE_MATCH_00       (4)
#define TCCR0_COMPARE_MATCH_01       (5)
#define TCCR0_WAVE_GENERATION_CTC    (6)
#define TCCR0_FORCE_OUTPUT_COMPARE   (7)


/*timer counter control register bits number --> TCCR1A   */

#define TCCR1A_WAVE_GENERATION_PWM10         (0)
#define TCCR1A_WAVE_GENERATION_PWM11         (1)
#define TCCR1A_FORCE_OUTPUT_COMPARE_CHANNELB (2)
#define TCCR1A_FORCE_OUTPUT_COMPARE_CHANNELA (3)
#define TCCR1A_COMPARE_OUTPUT_CHANNELB0      (4)
#define TCCR1A_COMPARE_OUTPUT_CHANNELB1      (5)
#define TCCR1A_COMPARE_OUTPUT_CHANNELA0      (6)
#define TCCR1A_COMPARE_OUTPUT_CHANNELA1      (7)

/*timer counter control register bits number --> TCCR1B   */

#define TCCR1B_CLOCK_SELECT_10               (0)
#define TCCR1B_CLOCK_SELECT_11               (1)
#define TCCR1B_CLOCK_SELECT_12               (2)
#define TCCR1B_WAVE_GENERATION_12            (3)
#define TCCR1B_WAVE_GENERATION_13            (4)



/*Function id for ISR*/
#define TIMER0_ID   (0)
#define TIMER1_ID   (1)
#define TIMER2_ID   (2)

#define NULL ( (void *) 0)

/*the size of the array function handlers*/
#define FUNC_REGISTER_SIZE   (3)

/************************************************************************/
/*                           typedefs                                   */
/************************************************************************/

/*declaring a function pointer*/
typedef   void(*CallbackFunc_t)(void);

typedef struct {
    u8_t function_id;
    CallbackFunc_t gp_timer_callback_func;
} function_register_t;


/************************************************************************/
/*                           Functions' prototypes                      */
/************************************************************************/


/*This function is used to initialize a specific timer channel with prescaler and mode*/
void mtimer_init(u8_t au8_timerChannel, u8_t au8_timerMode, u8_t au8_timerPrescaler);

/*This function is used to make a delay in an asynchronous fashion*/
void mtimer_delayMs_async(u8_t au8_timerChannel, u16_t au16_timerInMillis, void (*timer_func)(void));

/*This function is used to make a delay in an synchronous fashion*/
void mtimer_delayMs_sync(u8_t au8_timerChannel, u16_t au16_timerInMillis);

/*This function is used to generate hardware PWM*/
void mtimer_pwmGenerate(u8_t au8_timerChannel, u8_t au8_pwmOperation, u8_t au8_dutyCycle);

/*This function is used to get the PWM frequency and duty cycle*/
void mtimer_getPwmStatus(u8_t* pu8_dutyCycle, u32_t* pu32_frequency);


#endif /* TIMER_H_ */
