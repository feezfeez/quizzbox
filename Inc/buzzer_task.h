/**
  * @file    buzzer_task.h
  * @version 1.0
*/

#ifndef __BUZZER_TASK_H
#define __BUZZER_TASK_H

void create_buzzer_task();

#define PEND_ANS_PERIOD     50 // *10ms = 500ms per state = 1s period

// Handle declaration
TaskHandle_t buzzer_task_handle;

#endif /* __BUZZER_TASK_H */
