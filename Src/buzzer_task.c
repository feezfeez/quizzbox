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
#include "ui_tools.h"

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
    GPIO_TypeDef* buzz_led_port = 0;
    uint16_t buzz_led_pin = 0;

    // Period = 10ms
    portTickType period;
    period = (portTickType)(10/portTICK_RATE_MS);

    for(;;)
    {
        // Init
        i = 0;

        // Block until a buzzer is pressed
        xQueueReceive(buzzer_queue, &buzzer_mgmt, portMAX_DELAY);

        // Switch off all buzzers LED
        portENTER_CRITICAL();
        set_reset_all_buzzleds(GPIO_PIN_SET);
        portEXIT_CRITICAL();

        // Extract buzzer information
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

        // Blink until answer is approved (or not)
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
    }
}
