/**
  * @file    fsm_task.c
  * @version 1.0
  */

/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "main.h"
#include "fsm_task.h"
#include "config.h"
#include "task_config.h"
#include "ui_tools.h"

eSystemState eNextState = Idle_State;

static void _fsm_task(void *pvParameters);

static const uint32_t full_mask = BLUE_BUZZ_BP_Pin | RED_BUZZ_BP_Pin | YELLOW_BUZZ_BP_Pin | GREEN_BUZZ_BP_Pin;

void create_fsm_task(void)
{
    // Create task
    xTaskCreate(_fsm_task, "FSM_Task", configMINIMAL_STACK_SIZE,
            NULL, FSM_TASK_PRIORITY, &fsm_task_handle);
}

//Prototype of eventhandlers
eSystemState StartQuestionHandler(void)
{
    return Question_State;
}

eSystemState BuzzerPressedHandler(void)
{
    return Pending_Answer_State;
}

eSystemState CorrectAnswerHandler(void)
{
    return Correct_UI_State;
}

eSystemState ReadyToRestartHandler(void)
{
    return Idle_State;
}

eSystemState WrongAnswerHandler(uint32_t players_mask)
{
    if (players_mask == full_mask)
    {
        return Idle_State;
    }
    else
    {
        portENTER_CRITICAL();
        mask_buzzleds(players_mask);
        portEXIT_CRITICAL();

        EXTI->IMR |= ~(players_mask) & (BLUE_BUZZ_BP_Pin | RED_BUZZ_BP_Pin | YELLOW_BUZZ_BP_Pin | GREEN_BUZZ_BP_Pin);
        return Question_State;
    }
}

eSystemState StartButtonHandler(void)
{
    return Idle_State;
}

static void _fsm_task (void *pvParameters)
{
    // Init
    eSystemEvent eNewEvent;
    TickType_t time_to_wait = FINITE_BLOCKING_TIME;
    uint32_t players_mask = 0;
    buzz_led_t player_ans;

    // Period = 10ms
    portTickType period;
    period = (portTickType)(10/portTICK_RATE_MS);

    for(;;)
    {
        time_to_wait = portMAX_DELAY;
        if (eNextState == Idle_State)
            time_to_wait = FINITE_BLOCKING_TIME;

        //Read system events
        xQueueReceive(fsm_queue, &eNewEvent, time_to_wait);

        switch(eNextState)
        {
            case Idle_State:
                // Switch off all buzzers LED
                portENTER_CRITICAL();
                set_reset_all_buzzleds(GPIO_PIN_SET);
                portEXIT_CRITICAL();

                // Keep off for a little while before next game
                HAL_Delay(KEEP_OFF_INIT);

                // Switch on all buzzers LED
                portENTER_CRITICAL();
                set_reset_all_buzzleds(GPIO_PIN_RESET);
                portEXIT_CRITICAL();

                blink_all_buzzleds(INIT_TOGGL_CNT, period);

                // Reset Mask
                players_mask = 0;
                // Unmask all players
                EXTI->IMR |= BLUE_BUZZ_BP_Pin | RED_BUZZ_BP_Pin | YELLOW_BUZZ_BP_Pin | GREEN_BUZZ_BP_Pin;

                eNextState = StartQuestionHandler();
                break;

            case Question_State:
                if (eNewEvent == Start_Pressed_Event)
                {
                    StartButtonHandler();
                }
                else if (eNewEvent == Blue_Buzzer_Pressed_Event)
                {
                    players_mask |= BLUE_BUZZ_BP_Pin;
                    player_ans.buzz_led_port = BLUE_BUZZ_LED_GPIO_Port;
                    player_ans.buzz_led_pin = BLUE_BUZZ_LED_Pin;
                    eNextState = BuzzerPressedHandler();
                    xQueueOverwrite(buzzer_queue, &eNewEvent);
                }
                else if (eNewEvent == Red_Buzzer_Pressed_Event)
                {
                    players_mask |= RED_BUZZ_BP_Pin;
                    player_ans.buzz_led_port = RED_BUZZ_LED_GPIO_Port;
                    player_ans.buzz_led_pin = RED_BUZZ_LED_Pin;
                    eNextState = BuzzerPressedHandler();
                    xQueueOverwrite(buzzer_queue, &eNewEvent);
                }
                else if (eNewEvent == Yellow_Buzzer_Pressed_Event)
                {
                    players_mask |= YELLOW_BUZZ_BP_Pin;
                    player_ans.buzz_led_port = YELLOW_BUZZ_LED_GPIO_Port;
                    player_ans.buzz_led_pin = YELLOW_BUZZ_LED_Pin;
                    eNextState = BuzzerPressedHandler();
                    xQueueOverwrite(buzzer_queue, &eNewEvent);
                }
                else if (eNewEvent == Green_Buzzer_Pressed_Event)
                {
                    players_mask |= GREEN_BUZZ_BP_Pin;
                    player_ans.buzz_led_port = GREEN_BUZZ_LED_GPIO_Port;
                    player_ans.buzz_led_pin = GREEN_BUZZ_LED_Pin;
                    eNextState = BuzzerPressedHandler();
                    xQueueOverwrite(buzzer_queue, &eNewEvent);
                }
                break;

            case Pending_Answer_State:
                if (eNewEvent == Correct_Answer_Event)
                {
                    eNextState = CorrectAnswerHandler();
                    xQueueOverwrite(buzzer_queue, &eNewEvent);
                }
                else if (eNewEvent == Wrong_Answer_Event)
                {
                    eNextState = WrongAnswerHandler(players_mask);
                }
                break;

            case Correct_UI_State:
                portENTER_CRITICAL();
                HAL_GPIO_WritePin(player_ans.buzz_led_port, player_ans.buzz_led_pin, GPIO_PIN_SET);
                portEXIT_CRITICAL();

                blink_single_buzzled(player_ans, CORRECT_TOGGL_CNT, period);

                eNextState = ReadyToRestartHandler();
                break;

            default:
                break;
        }
    }
}
