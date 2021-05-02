/**
  * @file    config.h
  * @version 1.0
*/

#ifndef __CONFIG_H
#define __CONFIG_H

// Global configuration ==========================

#define BUZZ_ID_QUEUE_LEN   1
#define EXTI_QUEUE_LEN      3
#define FSM_QUEUE_LEN       3

typedef struct
{
    GPIO_TypeDef* buzz_led_port;
    uint16_t buzz_led_pin;
    uint16_t score;
}player_t;

// Extern declarations
extern eSystemState eNextState;

extern xQueueHandle buzzer_queue;
extern xQueueHandle exti_queue;
extern xQueueHandle fsm_queue;

#endif /* __CONFIG_H */
