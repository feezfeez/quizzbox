/**
  * @file    display_task.h
  * @version 1.0
*/

#ifndef __DISPLAY_TASK_H
#define __DISPLAY_TASK_H

void create_display_task();

// Handle declaration
TaskHandle_t display_task_handle;

typedef struct
{
    uint16_t blue_score;
    uint16_t red_score;
    uint16_t yellow_score;
    uint16_t green_score;
}scores_t;

typedef struct
{
    uint8_t blue_digit;
    uint8_t red_digit;
    uint8_t yellow_digit;
    uint8_t green_digit;
}digit_t;

#endif /* __DISPLAY_TASK_H */
