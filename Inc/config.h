/**
  * @file    config.h
  * @version 1.0
*/

#ifndef __CONFIG_H
#define __CONFIG_H

// Global configuration ==========================

#define BUZZ_ID_QUEUE_LEN       1
#define EXTI_QUEUE_LEN          3
#define FSM_QUEUE_LEN           3

#define SINGLE_ANSWER           5 // points
#define DOUBLE_ANSWER           10 // points
#define MAX_SCORE               999

#define BLINK_TOGGLE_TIMING     15 // *10ms

typedef struct
{
    GPIO_TypeDef* port;
    uint16_t pin;
}led_t;

typedef struct
{
    uint16_t buzzer;
    led_t buzz_led;
    led_t front_led;
    led_t top_panel_led;
    uint16_t score;
}player_t;

// Extern declarations
extern eSystemState eNextState;

extern xQueueHandle buzzer_queue;
extern xQueueHandle exti_queue;
extern xQueueHandle fsm_queue;

extern player_t blue, red, yellow, green;

#endif /* __CONFIG_H */
