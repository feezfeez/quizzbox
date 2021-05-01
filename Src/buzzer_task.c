/**
  * @file    buzzer_task.c
  * @version 1.0
  */

/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "main.h"
#include "fsm_task.h"
#include "config.h"
#include "buzzer_task.h"
#include "task_config.h"

static void _buzzer_task(void *pvParameters);

void create_buzzer_task(void)
{
    // Create task
    xTaskCreate(_buzzer_task, "Buzzer_Task", configMINIMAL_STACK_SIZE,
            NULL, BUZZER_TASK_PRIORITY, &buzzer_task_handle);
}

static void _buzzer_task (void *pvParameters)
{
    // Init
    uint8_t i = 0;
    uint8_t j = 0;
    eSystemEvent buzzer_mgmt;
    GPIO_TypeDef* buzz_led_port;
    uint16_t buzz_led_pin = 0;
    uint8_t correct_cycle = MAX_TOGGL_CNT;

    // XXX Period = 10ms?
    portTickType period;
    period = (portTickType)(10/portTICK_RATE_MS);

    for(;;)
    {
        // Init
        i = 0;
        correct_cycle = MAX_TOGGL_CNT;

        // Block until a buzzer is pressed
        xQueueReceive(buzzer_queue, &buzzer_mgmt, portMAX_DELAY);

        if (buzzer_mgmt == Blue_Buzzer_Pressed_Event)
        {
            buzz_led_port = BLUE_BUZZ_LED_GPIO_Port;
            buzz_led_pin = BLUE_BUZZ_LED_Pin;
        }
        else if (buzzer_mgmt == Red_Buzzer_Pressed_Event)
        {
            buzz_led_port = RED_BUZZ_LED_GPIO_Port;
            buzz_led_pin = RED_BUZZ_LED_Pin;
        }
        else if (buzzer_mgmt == Yellow_Buzzer_Pressed_Event)
        {
            buzz_led_port = YELLOW_BUZZ_LED_GPIO_Port;
            buzz_led_pin = YELLOW_BUZZ_LED_Pin;
        }
        else if (buzzer_mgmt == Green_Buzzer_Pressed_Event)
        {
            buzz_led_port = GREEN_BUZZ_LED_GPIO_Port;
            buzz_led_pin = GREEN_BUZZ_LED_Pin;
        }

        while(eNextState == Pending_Answer_State)
        {
            if (i == 0)
            {
                HAL_GPIO_TogglePin(buzz_led_port, buzz_led_pin);
                i = BLINK_PERIOD;
            }
            vTaskDelay(period);
            i--;
        }

        if (buzzer_mgmt == Correct_Answer_Event)
        {
            HAL_GPIO_WritePin(buzz_led_port, buzz_led_pin, GPIO_PIN_SET);

            for (j=0 ; j<MAX_TOGGL_LEN ; j++)
                vTaskDelay(period);

            while (correct_cycle != 0)
            {
                HAL_GPIO_TogglePin(buzz_led_port, buzz_led_pin);
                for (j=0 ; j<MAX_TOGGL_LEN ; j++)
                    vTaskDelay(period);
                correct_cycle--;
            }

            EXTI->IMR |= BLUE_BUZZ_BP_Pin | RED_BUZZ_BP_Pin | YELLOW_BUZZ_BP_Pin | GREEN_BUZZ_BP_Pin;
            correct_ans = 0;
        }

        else if (buzzer_mgmt == Wrong_Answer_Event)
        {
            // TODO Debounce à améliorer
            for (j=0 ; j<50 ; j++)
                vTaskDelay(period);
        }

        HAL_GPIO_WritePin(buzz_led_port, buzz_led_pin, GPIO_PIN_SET);
    }
}
