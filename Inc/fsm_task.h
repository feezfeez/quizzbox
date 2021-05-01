/**
  * @file    buzzer_task.h
  * @version 1.0
*/

#ifndef __FSM_TASK_H
#define __FSM_TASK_H

void create_fsm_task();

// Handle declaration
TaskHandle_t fsm_task_handle;

// Different states
typedef enum
{
    Idle_State,
    Question_State,
    Pending_Answer_State,
} eSystemState;

// Different type events
    typedef enum
    {
        Buzzer_Pressed_Event,
        Correct_Answer_Event,
        Wrong_Answer_Event
    } eSystemEvent;

#endif /* __FSM_TASK_H */
