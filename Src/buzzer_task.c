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
    eSystemEvent buzzer_mgmt;
    GPIO_TypeDef* buzz_led_port;
    uint16_t buzz_led_pin = 0;
    uint8_t correct_cycles = MAX_TOGGL_CNT;

    // Period = 10ms
    portTickType period;
    period = (portTickType)(10/portTICK_RATE_MS);

    for(;;)
    {
        // Init
        i = 0;
        correct_cycles = MAX_TOGGL_CNT;

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
                portENTER_CRITICAL();
                HAL_GPIO_TogglePin(buzz_led_port, buzz_led_pin);
                portEXIT_CRITICAL();
                i = PEND_ANS_PERIOD;
            }
            vTaskDelay(period);
            i--;
        }

        if (buzzer_mgmt == Correct_Answer_Event)
        {
            portENTER_CRITICAL();
            HAL_GPIO_WritePin(buzz_led_port, buzz_led_pin, GPIO_PIN_SET);
            portEXIT_CRITICAL();

            for (i=0 ; i<MAX_TOGGL_LEN ; i++)
                vTaskDelay(period);

            while (correct_cycles != 0)
            {
                portENTER_CRITICAL();
                HAL_GPIO_TogglePin(buzz_led_port, buzz_led_pin);
                portEXIT_CRITICAL();
                for (i=0 ; i<MAX_TOGGL_LEN ; i++)
                    vTaskDelay(period);
                correct_cycles--;
            }
        }

        else if (buzzer_mgmt == Wrong_Answer_Event)
        {
            // TODO Debounce à améliorer
            for (i=0 ; i<50 ; i++)
                vTaskDelay(period);
        }

        portENTER_CRITICAL();
        HAL_GPIO_WritePin(buzz_led_port, buzz_led_pin, GPIO_PIN_SET);
        portEXIT_CRITICAL();
    }
}
