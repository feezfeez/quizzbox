/**
  * @file    buzzer_task.h
  * @version 1.0
*/

#ifndef __HALL_SENSOR_TASK_H
#define __HALL_SENSOR_TASK_H

void create_buzzer_task();

#define BLINK_PERIOD        50 // *10ms = 500ms per state = 1s period
#define MAX_TOGGL_CNT       6
#define MAX_TOGGL_LEN       15 // *10ms

// Handle declaration
TaskHandle_t buzzer_task_handle;

#endif /* __HALL_SENSOR_TASK_H */
