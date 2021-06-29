/**
  * @file    handler_task.c
  * @version 1.0
  */

/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "main.h"
#include "fsm_task.h"
#include "config.h"
#include "handler_task.h"
#include "task_config.h"

static void _handler_task(void *pvParameters);

void create_handler_task(void)
{
    // Create task
    xTaskCreate(_handler_task, "Handler_Task", configMINIMAL_STACK_SIZE,
            NULL, HANDLER_TASK_PRIORITY, handler_task_handle);
}

static void _handler_task (void *pvParameters)
{
    // Init
    uint16_t exti_pin = 0;
    fsm_input_t event_to_send;

    for(;;)
    {
        // Reset variables
        event_to_send.player = NULL;

        // Block until interrupt on external input occurs
        xQueueReceive(exti_queue, &exti_pin, portMAX_DELAY);

        if (eNextState == Idle_State)
            continue;

        if (exti_pin == blue.buzzer)
        {
            EXTI->IMR &= ~(blue.buzzer) & ~(red.buzzer) &
                         ~(yellow.buzzer) & ~(green.buzzer);

            event_to_send.event = Buzzer_Pressed_Event;
            event_to_send.player = &blue;
        }
        else if (exti_pin == red.buzzer)
        {
            EXTI->IMR &= ~(blue.buzzer) & ~(red.buzzer) &
                         ~(yellow.buzzer) & ~(green.buzzer);

            event_to_send.event = Buzzer_Pressed_Event;
            event_to_send.player = &red;
        }
        else if (exti_pin == yellow.buzzer)
        {
            EXTI->IMR &= ~(blue.buzzer) & ~(red.buzzer) &
                         ~(yellow.buzzer) & ~(green.buzzer);

            event_to_send.event = Buzzer_Pressed_Event;
            event_to_send.player = &yellow;
        }
        else if (exti_pin == green.buzzer)
        {
            EXTI->IMR &= ~(blue.buzzer) & ~(red.buzzer) &
                         ~(yellow.buzzer) & ~(green.buzzer);

            event_to_send.event = Buzzer_Pressed_Event;
            event_to_send.player = &green;
        }
        else if (exti_pin == OK_SINGLE_BP_Pin)
        {
            event_to_send.event = Correct_Answer_Single_Event;
        }
        else if (exti_pin == OK_DOUBLE_BP_Pin)
        {
            event_to_send.event = Correct_Answer_Double_Event;
        }
        else if (exti_pin == KO_BP_Pin)
        {
            event_to_send.event = Wrong_Answer_Event;
        }
        else if (exti_pin == START_BP_Pin)
        {
            event_to_send.event = Start_Pressed_Event;
        }
        else if (exti_pin == CANCEL_BP_Pin)
        {
            EXTI->IMR &= ~(blue.buzzer) & ~(red.buzzer) &
                         ~(yellow.buzzer) & ~(green.buzzer);
            event_to_send.event = Cancel_Event;
        }

        xQueueSend(fsm_queue, &event_to_send, 0);
    }
}
