/**
  * @file    buzzer_task.h
  * @version 1.0
*/

#ifndef __FSM_TASK_H
#define __FSM_TASK_H

void create_fsm_task();

// Defines
#define INIT_TOGGL_CNT          4
#define CORRECT_TOGGL_CNT       6

#define FINITE_BLOCKING_TIME    1
#define KEEP_OFF_INIT           500 // ms

// Handle declaration
TaskHandle_t fsm_task_handle;

// Different states
typedef enum
{
    Idle_State,
    Question_State,
    Pending_Answer_State,
    Correct_UI_State,
} eSystemState;

// Different type events
typedef enum
{
    Start_Pressed_Event = 1,
    Blue_Buzzer_Pressed_Event,
    Red_Buzzer_Pressed_Event,
    Yellow_Buzzer_Pressed_Event,
    Green_Buzzer_Pressed_Event,
    Correct_Answer_Event,
    Wrong_Answer_Event
} eSystemEvent;

#endif /* __FSM_TASK_H */
