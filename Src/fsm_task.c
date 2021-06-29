/**
  * @file    fsm_task.c
  * @version 1.0
  */

/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include <stdbool.h>
#include "main.h"
#include "fsm_task.h"
#include "config.h"
#include "task_config.h"
#include "ui_tools.h"

eSystemState eNextState = Idle_State;

static void _fsm_task(void *pvParameters);

static const uint16_t full_mask = BLUE_BUZZ_BP_Pin | RED_BUZZ_BP_Pin | YELLOW_BUZZ_BP_Pin | GREEN_BUZZ_BP_Pin;

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

eSystemState WrongAnswerHandler(uint16_t players_mask)
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

eSystemState CancelHandler(uint16_t *players_mask, uint16_t mask_save,
                           player_t *player_ans, cancel_ans_t ans_to_cancel)
{
    eSystemEvent EventToSend;

    *players_mask = mask_save;

    if (ans_to_cancel == single_ans)
        player_ans->score -= SINGLE_ANSWER;
    else if (ans_to_cancel == double_ans)
        player_ans->score -= DOUBLE_ANSWER;

    if (player_ans->buzzer == blue.buzzer)
        EventToSend = Blue_Buzzer_Pressed_Event;
    else if (player_ans->buzzer == red.buzzer)
        EventToSend = Red_Buzzer_Pressed_Event;
    else if (player_ans->buzzer == yellow.buzzer)
        EventToSend = Yellow_Buzzer_Pressed_Event;
    else if (player_ans->buzzer == green.buzzer)
        EventToSend = Green_Buzzer_Pressed_Event;

    xQueueSend(fsm_queue, &EventToSend, 0);

    return Question_State;
}

static void _fsm_task (void *pvParameters)
{
    // Init
    eSystemEvent eNewEvent;
    TickType_t time_to_wait = FINITE_BLOCKING_TIME;
    uint16_t players_mask = 0;
    player_t *player_ans = NULL;
    uint16_t mask_save = 0;
    player_t *ans_save = NULL;
    cancel_ans_t ans_valid = 0;
    bool cancel_flag = false;


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
                set_reset_all_buzzleds(GPIO_PIN_RESET);
                portEXIT_CRITICAL();

                // Keep off for a little while before next game
                HAL_Delay(KEEP_OFF_INIT);

                // Switch on all buzzers LED
                portENTER_CRITICAL();
                set_reset_all_buzzleds(GPIO_PIN_SET);
                portEXIT_CRITICAL();

                // Blink all buzzers
                blink_all_buzzleds(INIT_TOGGL_CNT, period);

                // Reset variables
                players_mask = 0;

                // Unmask all players
                EXTI->IMR |= blue.buzzer | red.buzzer | yellow.buzzer | green.buzzer;

                eNextState = StartQuestionHandler();
                break;

            case Question_State:
                if (eNewEvent == Start_Pressed_Event)
                {
                    StartButtonHandler();
                }
                else if (eNewEvent == Cancel_Event)
                {
                    if (cancel_flag == true)
                    {
                        eNextState = CancelHandler(&players_mask, mask_save, ans_save, ans_valid);
                        cancel_flag = false;
                    }
                }
                else if (eNewEvent == Blue_Buzzer_Pressed_Event)
                {
                    players_mask |= blue.buzzer;
                    player_ans = &blue;
                    eNextState = BuzzerPressedHandler();
                    xQueueOverwrite(buzzer_queue, &blue.buzz_led);
                }
                else if (eNewEvent == Red_Buzzer_Pressed_Event)
                {
                    players_mask |= red.buzzer;
                    player_ans = &red;
                    eNextState = BuzzerPressedHandler();
                    xQueueOverwrite(buzzer_queue, &red.buzz_led);
                }
                else if (eNewEvent == Yellow_Buzzer_Pressed_Event)
                {
                    players_mask |= yellow.buzzer;
                    player_ans = &yellow;
                    eNextState = BuzzerPressedHandler();
                    xQueueOverwrite(buzzer_queue, &yellow.buzz_led);
                }
                else if (eNewEvent == Green_Buzzer_Pressed_Event)
                {
                    players_mask |= green.buzzer;
                    player_ans = &green;
                    eNextState = BuzzerPressedHandler();
                    xQueueOverwrite(buzzer_queue, &green.buzz_led);
                }
                break;

            case Pending_Answer_State:
                if (eNewEvent == Start_Pressed_Event)
                {
                    StartButtonHandler();
                }
                else if (eNewEvent == Cancel_Event)
                {
                    if (cancel_flag == true)
                    {
                        eNextState = CancelHandler(&players_mask, mask_save, ans_save, ans_valid);
                        cancel_flag = false;
                    }
                }
                else if (eNewEvent == Correct_Answer_Single_Event)
                {
                    // Save context in case of "Cancel" action
                    mask_save = players_mask;
                    ans_save = player_ans;
                    ans_valid = single_ans;
                    cancel_flag = true;

                    player_ans->score += SINGLE_ANSWER;
                    if (player_ans->score > MAX_SCORE)
                        player_ans->score = MAX_SCORE;

                    eNextState = CorrectAnswerHandler();
                }
                else if (eNewEvent == Correct_Answer_Double_Event)
                {
                    // Save context in case of "Cancel" action
                    mask_save = players_mask;
                    ans_save = player_ans;
                    ans_valid = double_ans;
                    cancel_flag = true;

                    player_ans->score += SINGLE_ANSWER;
                    if (player_ans->score > MAX_SCORE)
                        player_ans->score = MAX_SCORE;

                    eNextState = CorrectAnswerHandler();
                }
                else if (eNewEvent == Wrong_Answer_Event)
                {
                    // Save context in case of "Cancel" action
                    mask_save = players_mask;
                    ans_save = player_ans;
                    ans_valid = incorrect_ans;
                    cancel_flag = true;

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
