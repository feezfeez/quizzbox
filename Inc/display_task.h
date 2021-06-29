/**
  * @file    display_task.h
  * @version 1.0
*/

#ifndef __DISPLAY_TASK_H
#define __DISPLAY_TASK_H

void create_display_task();

// Defines
#define DIGIT_MAX_NUMBER    3

// Blue seven segments conversions
#define B_ZERO              (B_SS_A_Pin | B_SS_B_Pin | B_SS_C_Pin | B_SS_D_Pin | B_SS_E_Pin | B_SS_F_Pin)
#define B_ONE               (B_SS_B_Pin | B_SS_C_Pin)
#define B_TWO               (B_SS_A_Pin | B_SS_B_Pin | B_SS_D_Pin | B_SS_E_Pin | B_SS_G_Pin)
#define B_THREE             (B_SS_A_Pin | B_SS_B_Pin | B_SS_C_Pin | B_SS_D_Pin | B_SS_G_Pin)
#define B_FOUR              (B_SS_B_Pin | B_SS_C_Pin | B_SS_F_Pin | B_SS_G_Pin)
#define B_FIVE              (B_SS_A_Pin | B_SS_C_Pin | B_SS_D_Pin | B_SS_F_Pin | B_SS_G_Pin)
#define B_SIX               (B_SS_A_Pin | B_SS_C_Pin | B_SS_D_Pin | B_SS_E_Pin | B_SS_F_Pin | B_SS_G_Pin)
#define B_SEVEN             (B_SS_A_Pin | B_SS_B_Pin | B_SS_C_Pin)
#define B_EIGHT             (B_SS_A_Pin | B_SS_B_Pin | B_SS_C_Pin | B_SS_D_Pin | B_SS_E_Pin | B_SS_F_Pin | B_SS_G_Pin)
#define B_NINE              (B_SS_A_Pin | B_SS_B_Pin | B_SS_C_Pin | B_SS_D_Pin | B_SS_F_Pin | B_SS_G_Pin)

// Red seven segments conversions
#define R_ZERO              (R_SS_A_Pin | R_SS_B_Pin | R_SS_C_Pin | R_SS_D_Pin | R_SS_E_Pin | R_SS_F_Pin)
#define R_ONE               (R_SS_B_Pin | R_SS_C_Pin)
#define R_TWO               (R_SS_A_Pin | R_SS_B_Pin | R_SS_D_Pin | R_SS_E_Pin | R_SS_G_Pin)
#define R_THREE             (R_SS_A_Pin | R_SS_B_Pin | R_SS_C_Pin | R_SS_D_Pin | R_SS_G_Pin)
#define R_FOUR              (R_SS_B_Pin | R_SS_C_Pin | R_SS_F_Pin | R_SS_G_Pin)
#define R_FIVE              (R_SS_A_Pin | R_SS_C_Pin | R_SS_D_Pin | R_SS_F_Pin | R_SS_G_Pin)
#define R_SIX               (R_SS_A_Pin | R_SS_C_Pin | R_SS_D_Pin | R_SS_E_Pin | R_SS_F_Pin | R_SS_G_Pin)
#define R_SEVEN             (R_SS_A_Pin | R_SS_B_Pin | R_SS_C_Pin)
#define R_EIGHT             (R_SS_A_Pin | R_SS_B_Pin | R_SS_C_Pin | R_SS_D_Pin | R_SS_E_Pin | R_SS_F_Pin | R_SS_G_Pin)
#define R_NINE              (R_SS_A_Pin | R_SS_B_Pin | R_SS_C_Pin | R_SS_D_Pin | R_SS_F_Pin | R_SS_G_Pin)

// Yellow seven segments conversions
#define Y_ZERO              (Y_SS_A_Pin | Y_SS_B_Pin | Y_SS_C_Pin | Y_SS_D_Pin | Y_SS_E_Pin | Y_SS_F_Pin)
#define Y_ONE               (Y_SS_B_Pin | Y_SS_C_Pin)
#define Y_TWO               (Y_SS_A_Pin | Y_SS_B_Pin | Y_SS_D_Pin | Y_SS_E_Pin | Y_SS_G_Pin)
#define Y_THREE             (Y_SS_A_Pin | Y_SS_B_Pin | Y_SS_C_Pin | Y_SS_D_Pin | Y_SS_G_Pin)
#define Y_FOUR              (Y_SS_B_Pin | Y_SS_C_Pin | Y_SS_F_Pin | Y_SS_G_Pin)
#define Y_FIVE              (Y_SS_A_Pin | Y_SS_C_Pin | Y_SS_D_Pin | Y_SS_F_Pin | Y_SS_G_Pin)
#define Y_SIX               (Y_SS_A_Pin | Y_SS_C_Pin | Y_SS_D_Pin | Y_SS_E_Pin | Y_SS_F_Pin | Y_SS_G_Pin)
#define Y_SEVEN             (Y_SS_A_Pin | Y_SS_B_Pin | Y_SS_C_Pin)
#define Y_EIGHT             (Y_SS_A_Pin | Y_SS_B_Pin | Y_SS_C_Pin | Y_SS_D_Pin | Y_SS_E_Pin | Y_SS_F_Pin | Y_SS_G_Pin)
#define Y_NINE              (Y_SS_A_Pin | Y_SS_B_Pin | Y_SS_C_Pin | Y_SS_D_Pin | Y_SS_F_Pin | Y_SS_G_Pin)

// Green seven segments conversions
#define G_ZERO              (G_SS_A_Pin | G_SS_B_Pin | G_SS_C_Pin | G_SS_D_Pin | G_SS_E_Pin | G_SS_F_Pin)
#define G_ONE               (G_SS_B_Pin | G_SS_C_Pin)
#define G_TWO               (G_SS_A_Pin | G_SS_B_Pin | G_SS_D_Pin | G_SS_E_Pin | G_SS_G_Pin)
#define G_THREE             (G_SS_A_Pin | G_SS_B_Pin | G_SS_C_Pin | G_SS_D_Pin | G_SS_G_Pin)
#define G_FOUR              (G_SS_B_Pin | G_SS_C_Pin | G_SS_F_Pin | G_SS_G_Pin)
#define G_FIVE              (G_SS_A_Pin | G_SS_C_Pin | G_SS_D_Pin | G_SS_F_Pin | G_SS_G_Pin)
#define G_SIX               (G_SS_A_Pin | G_SS_C_Pin | G_SS_D_Pin | G_SS_E_Pin | G_SS_F_Pin | G_SS_G_Pin)
#define G_SEVEN             (G_SS_A_Pin | G_SS_B_Pin | G_SS_C_Pin)
#define G_EIGHT             (G_SS_A_Pin | G_SS_B_Pin | G_SS_C_Pin | G_SS_D_Pin | G_SS_E_Pin | G_SS_F_Pin | G_SS_G_Pin)
#define G_NINE              (G_SS_A_Pin | G_SS_B_Pin | G_SS_C_Pin | G_SS_D_Pin | G_SS_F_Pin | G_SS_G_Pin)

// Handle declaration
TaskHandle_t display_task_handle;

typedef enum
{
    UNITS = 0,
    TENS = 1,
    HUNDREDS = 2
}digits_t;

#endif /* __DISPLAY_TASK_H */
