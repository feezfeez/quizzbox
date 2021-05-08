/**
  * @file    display_task.h
  * @version 1.0
*/

#ifndef __DISPLAY_TASK_H
#define __DISPLAY_TASK_H

void create_display_task();

// Defines
#define DIGIT_MAX_NUMBER    3

// Handle declaration
TaskHandle_t display_task_handle;

typedef struct
{
    uint8_t blue;
    uint8_t red;
    uint8_t yellow;
    uint8_t green;
}digit_t;

#endif /* __DISPLAY_TASK_H */
