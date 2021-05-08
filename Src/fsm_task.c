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

        // Unmask buzzers who haven't answered yet during the game
        EXTI->IMR |= ~(players_mask) & (blue.buzzer | red.buzzer | yellow.buzzer | green.buzzer);
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
    uint16_t players_mask = 0;
    uint16_t player_ans = 0;

    // Period = 10ms
    portTickType period;
    period = (portTickType)(10/portTICK_RATE_MS);

    for(;;)
    {
        time_to_wait = portMAX_DELAY;
        if (eNextState == Idle_State)
            time_to_wait = FINITE_BLOCKING_TIME; // Set to a finite number to run Idle State without external event

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

                // Blink all buzzers
                blink_all_buzzleds(INIT_TOGGL_CNT, period);

                // Reset variables
                players_mask = 0;
                player_ans = 0;
                // Unmask all players
                EXTI->IMR |= blue.buzzer | red.buzzer | yellow.buzzer | green.buzzer;

                eNextState = StartQuestionHandler();
                break;

            case Question_State:
                if (eNewEvent == Start_Pressed_Event)
                {
                    StartButtonHandler();
                }
                else if (eNewEvent == Blue_Buzzer_Pressed_Event)
                {
                    players_mask |= blue.buzzer;
                    player_ans = blue.buzzer;
                    eNextState = BuzzerPressedHandler();
                    xQueueOverwrite(buzzer_queue, &blue.buzz_led);
                }
                else if (eNewEvent == Red_Buzzer_Pressed_Event)
                {
                    players_mask |= red.buzzer;
                    player_ans = red.buzzer;
                    eNextState = BuzzerPressedHandler();
                    xQueueOverwrite(buzzer_queue, &red.buzz_led);
                }
                else if (eNewEvent == Yellow_Buzzer_Pressed_Event)
                {
                    players_mask |= yellow.buzzer;
                    player_ans = yellow.buzzer;
                    eNextState = BuzzerPressedHandler();
                    xQueueOverwrite(buzzer_queue, &yellow.buzz_led);
                }
                else if (eNewEvent == Green_Buzzer_Pressed_Event)
                {
                    players_mask |= green.buzzer;
                    player_ans = green.buzzer;
                    eNextState = BuzzerPressedHandler();
                    xQueueOverwrite(buzzer_queue, &green.buzz_led);
                }
                break;

            case Pending_Answer_State:
                if (eNewEvent == Start_Pressed_Event)
                {
                    StartButtonHandler();
                }
                else if (eNewEvent == Correct_Answer_Single_Event)
                {
                    if (player_ans == blue.buzzer)
                        blue.score += SINGLE_ANSWER;
                    else if (player_ans == red.buzzer)
                        red.score += SINGLE_ANSWER;
                    else if (player_ans == yellow.buzzer)
                        yellow.score += SINGLE_ANSWER;
                    else if (player_ans == green.buzzer)
                        green.score += SINGLE_ANSWER;

                    eNextState = CorrectAnswerHandler();
                }
                else if (eNewEvent == Correct_Answer_Double_Event)
                {
                    if (player_ans == blue.buzzer)
                        blue.score += DOUBLE_ANSWER;
                    else if (player_ans == red.buzzer)
                        red.score += DOUBLE_ANSWER;
                    else if (player_ans == yellow.buzzer)
                        yellow.score += DOUBLE_ANSWER;
                    else if (player_ans == green.buzzer)
                        green.score += DOUBLE_ANSWER;

                    eNextState = CorrectAnswerHandler();
                }
                else if (eNewEvent == Wrong_Answer_Event)
                {
                    eNextState = WrongAnswerHandler(players_mask);
                }
                break;

            case Correct_UI_State:
                if (eNewEvent == Start_Pressed_Event)
                {
                    StartButtonHandler();
                }
                if (eNewEvent == End_Of_Correct_UI_Event)
                {
                    eNextState = ReadyToRestartHandler();
                }
                break;

            default:
                break;
        }
    }
}
