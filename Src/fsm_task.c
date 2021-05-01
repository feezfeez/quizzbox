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
    uint32_t players_mask = 0;

    for(;;)
    {
        //Read system Events
        xQueueReceive(fsm_queue, &eNewEvent, portMAX_DELAY);
        switch(eNextState)
        {
            case Idle_State:
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
                else if(eNewEvent == Blue_Buzzer_Pressed_Event)
                {
                    players_mask |= BLUE_BUZZ_BP_Pin;
                    eNextState = BuzzerPressedHandler();
                }
                else if(eNewEvent == Red_Buzzer_Pressed_Event)
                {
                    players_mask |= RED_BUZZ_BP_Pin;
                    eNextState = BuzzerPressedHandler();
                }
                else if(eNewEvent == Yellow_Buzzer_Pressed_Event)
                {
                    players_mask |= YELLOW_BUZZ_BP_Pin;
                    eNextState = BuzzerPressedHandler();
                }
                else if(eNewEvent == Green_Buzzer_Pressed_Event)
                {
                    players_mask |= GREEN_BUZZ_BP_Pin;
                    eNextState = BuzzerPressedHandler();
                }

                xQueueOverwrite(buzzer_queue, &eNewEvent);
                break;

            case Pending_Answer_State:

                if(eNewEvent == Correct_Answer_Event)
                {
                    eNextState = CorrectAnswerHandler();
                }
                else if (eNewEvent == Wrong_Answer_Event)
                {
                    eNextState = WrongAnswerHandler(players_mask);
                }

                xQueueOverwrite(buzzer_queue, &eNewEvent);
                break;

            default:
                break;
        }
    }
}
