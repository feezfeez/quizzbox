/**
  * @file    ui_tools.c
  * @version 1.0
  */

/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "main.h"
#include "fsm_task.h"
#include "config.h"
#include "ui_tools.h"


void set_reset_all_buzzleds(GPIO_PinState set_reset)
{
    HAL_GPIO_WritePin(BLUE_BUZZ_LED_GPIO_Port, BLUE_BUZZ_LED_Pin, set_reset);
    HAL_GPIO_WritePin(RED_BUZZ_LED_GPIO_Port, RED_BUZZ_LED_Pin, set_reset);
    HAL_GPIO_WritePin(YELLOW_BUZZ_LED_GPIO_Port, YELLOW_BUZZ_LED_Pin, set_reset);
    HAL_GPIO_WritePin(GREEN_BUZZ_LED_GPIO_Port, GREEN_BUZZ_LED_Pin, set_reset);
}

void toggle_all_buzzleds(void)
{
    HAL_GPIO_TogglePin(BLUE_BUZZ_LED_GPIO_Port, BLUE_BUZZ_LED_Pin);
    HAL_GPIO_TogglePin(RED_BUZZ_LED_GPIO_Port, RED_BUZZ_LED_Pin);
    HAL_GPIO_TogglePin(YELLOW_BUZZ_LED_GPIO_Port, YELLOW_BUZZ_LED_Pin);
    HAL_GPIO_TogglePin(GREEN_BUZZ_LED_GPIO_Port, GREEN_BUZZ_LED_Pin);
}

void mask_buzzleds(uint32_t players_mask)
{
    if ((players_mask & BLUE_BUZZ_BP_Pin) == BLUE_BUZZ_BP_Pin)
        HAL_GPIO_WritePin(BLUE_BUZZ_LED_GPIO_Port, BLUE_BUZZ_LED_Pin, GPIO_PIN_SET);
    else
        HAL_GPIO_WritePin(BLUE_BUZZ_LED_GPIO_Port, BLUE_BUZZ_LED_Pin, GPIO_PIN_RESET);

    if ((players_mask & RED_BUZZ_BP_Pin) == RED_BUZZ_BP_Pin)
        HAL_GPIO_WritePin(RED_BUZZ_LED_GPIO_Port, RED_BUZZ_LED_Pin, GPIO_PIN_SET);
    else
        HAL_GPIO_WritePin(RED_BUZZ_LED_GPIO_Port, RED_BUZZ_LED_Pin, GPIO_PIN_RESET);

    if ((players_mask & YELLOW_BUZZ_BP_Pin) == YELLOW_BUZZ_BP_Pin)
        HAL_GPIO_WritePin(YELLOW_BUZZ_LED_GPIO_Port, YELLOW_BUZZ_LED_Pin, GPIO_PIN_SET);
    else
        HAL_GPIO_WritePin(YELLOW_BUZZ_LED_GPIO_Port, YELLOW_BUZZ_LED_Pin, GPIO_PIN_RESET);

    if ((players_mask & GREEN_BUZZ_BP_Pin) == GREEN_BUZZ_BP_Pin)
        HAL_GPIO_WritePin(GREEN_BUZZ_LED_GPIO_Port, GREEN_BUZZ_LED_Pin, GPIO_PIN_SET);
    else
        HAL_GPIO_WritePin(GREEN_BUZZ_LED_GPIO_Port, GREEN_BUZZ_LED_Pin, GPIO_PIN_RESET);

}

void blink_all_buzzleds(uint8_t blink_cnt, portTickType period)
{
    uint8_t i = 0;

    for (i=0 ; i<BLINK_TOGGLE_TIMING ; i++)
        vTaskDelay(period);

    while (blink_cnt != 0)
    {
        portENTER_CRITICAL();
        toggle_all_buzzleds();
        portEXIT_CRITICAL();

        for (i=0 ; i<BLINK_TOGGLE_TIMING ; i++)
            vTaskDelay(period);

        blink_cnt--;
    }
}

uint16_t num_to_sevenseg(sevenseg_digit_t digit, uint16_t player)
{
    uint16_t seven_seg_value = 0;

    switch (digit)
    {
        case SS_ZERO:
            if (player == blue.buzzer)
                seven_seg_value = B_SS_A_Pin | B_SS_B_Pin | B_SS_C_Pin |
                                  B_SS_D_Pin | B_SS_E_Pin | B_SS_F_Pin;
            else if (player == red.buzzer)
                seven_seg_value = R_SS_A_Pin | R_SS_B_Pin | R_SS_C_Pin |
                                  R_SS_D_Pin | R_SS_E_Pin | R_SS_F_Pin;
            else if (player == yellow.buzzer)
                seven_seg_value = Y_SS_A_Pin | Y_SS_B_Pin | Y_SS_C_Pin |
                                  Y_SS_D_Pin | Y_SS_E_Pin | Y_SS_F_Pin;
            else if (player == green.buzzer)
                seven_seg_value = G_SS_A_Pin | G_SS_B_Pin | G_SS_C_Pin |
                                  G_SS_D_Pin | G_SS_E_Pin | G_SS_F_Pin;
            break;

        case SS_ONE:
            if (player == blue.buzzer)
                seven_seg_value = B_SS_B_Pin | B_SS_C_Pin;
            else if (player == red.buzzer)
                seven_seg_value = R_SS_B_Pin | R_SS_C_Pin;
            else if (player == yellow.buzzer)
                seven_seg_value = Y_SS_B_Pin | Y_SS_C_Pin;
            else if (player == green.buzzer)
                seven_seg_value = G_SS_B_Pin | G_SS_C_Pin;
            break;

        case SS_TWO:
            if (player == blue.buzzer)
                seven_seg_value = B_SS_A_Pin | B_SS_B_Pin | B_SS_D_Pin |
                                  B_SS_E_Pin | B_SS_G_Pin;
            else if (player == red.buzzer)
                seven_seg_value = R_SS_A_Pin | R_SS_B_Pin | R_SS_D_Pin |
                                  R_SS_E_Pin | R_SS_G_Pin;
            else if (player == yellow.buzzer)
                seven_seg_value = Y_SS_A_Pin | Y_SS_B_Pin | Y_SS_D_Pin |
                                  Y_SS_E_Pin | Y_SS_G_Pin;
            else if (player == green.buzzer)
                seven_seg_value = G_SS_A_Pin | G_SS_B_Pin | G_SS_D_Pin |
                                  G_SS_E_Pin | G_SS_G_Pin;
            break;

        case SS_THREE:
            if (player == blue.buzzer)
                seven_seg_value = B_SS_A_Pin | B_SS_B_Pin | B_SS_C_Pin |
                                  B_SS_D_Pin | B_SS_G_Pin;
            else if (player == red.buzzer)
                seven_seg_value = R_SS_A_Pin | R_SS_B_Pin | R_SS_C_Pin |
                                  R_SS_D_Pin | R_SS_G_Pin;
            else if (player == yellow.buzzer)
                seven_seg_value = Y_SS_A_Pin | Y_SS_B_Pin | Y_SS_C_Pin |
                                  Y_SS_D_Pin | Y_SS_G_Pin;
            else if (player == green.buzzer)
                seven_seg_value = G_SS_A_Pin | G_SS_B_Pin | G_SS_C_Pin |
                                  G_SS_D_Pin | G_SS_G_Pin;
            break;

        case SS_FOUR:
            if (player == blue.buzzer)
                seven_seg_value = B_SS_B_Pin | B_SS_C_Pin | B_SS_F_Pin | B_SS_G_Pin;
            else if (player == red.buzzer)
                seven_seg_value = R_SS_B_Pin | R_SS_C_Pin | R_SS_F_Pin | R_SS_G_Pin;
            else if (player == yellow.buzzer)
                seven_seg_value = Y_SS_B_Pin | Y_SS_C_Pin | Y_SS_F_Pin | Y_SS_G_Pin;
            else if (player == green.buzzer)
                seven_seg_value = G_SS_B_Pin | G_SS_C_Pin | G_SS_F_Pin | G_SS_G_Pin;
            break;

        case SS_FIVE:
            if (player == blue.buzzer)
                seven_seg_value = B_SS_A_Pin | B_SS_C_Pin | B_SS_D_Pin |
                                  B_SS_F_Pin | B_SS_G_Pin;
            else if (player == red.buzzer)
                seven_seg_value = R_SS_A_Pin | R_SS_C_Pin | R_SS_D_Pin |
                                  R_SS_F_Pin | R_SS_G_Pin;
            else if (player == yellow.buzzer)
                seven_seg_value = Y_SS_A_Pin | Y_SS_C_Pin | Y_SS_D_Pin |
                                  Y_SS_F_Pin | Y_SS_G_Pin;
            else if (player == green.buzzer)
                seven_seg_value = G_SS_A_Pin | G_SS_C_Pin | G_SS_D_Pin |
                                  G_SS_F_Pin | G_SS_G_Pin;
            break;

        case SS_SIX:
            if (player == blue.buzzer)
                seven_seg_value = B_SS_A_Pin | B_SS_C_Pin | B_SS_D_Pin |
                                  B_SS_E_Pin | B_SS_F_Pin | B_SS_G_Pin;
            else if (player == red.buzzer)
                seven_seg_value = R_SS_A_Pin | R_SS_C_Pin | R_SS_D_Pin |
                                  R_SS_E_Pin | R_SS_F_Pin | R_SS_G_Pin;
            else if (player == yellow.buzzer)
                seven_seg_value = Y_SS_A_Pin | Y_SS_C_Pin | Y_SS_D_Pin |
                                  Y_SS_E_Pin | Y_SS_F_Pin | Y_SS_G_Pin;
            else if (player == green.buzzer)
                seven_seg_value = G_SS_A_Pin | G_SS_C_Pin | G_SS_D_Pin |
                                  G_SS_E_Pin | G_SS_F_Pin | G_SS_G_Pin;
            break;

        case SS_SEVEN:
            if (player == blue.buzzer)
                seven_seg_value = B_SS_A_Pin | B_SS_B_Pin | B_SS_C_Pin;
            else if (player == red.buzzer)
                seven_seg_value = R_SS_A_Pin | R_SS_B_Pin | R_SS_C_Pin;
            else if (player == yellow.buzzer)
                seven_seg_value = Y_SS_A_Pin | Y_SS_B_Pin | Y_SS_C_Pin;
            else if (player == green.buzzer)
                seven_seg_value = G_SS_A_Pin | G_SS_B_Pin | G_SS_C_Pin;
            break;

        case SS_EIGHT:
            if (player == blue.buzzer)
                seven_seg_value = B_SS_A_Pin | B_SS_B_Pin | B_SS_C_Pin | B_SS_D_Pin |
                                  B_SS_E_Pin | B_SS_F_Pin | B_SS_G_Pin;
            else if (player == red.buzzer)
                seven_seg_value = R_SS_A_Pin | R_SS_B_Pin | R_SS_C_Pin | R_SS_D_Pin |
                                  R_SS_E_Pin | R_SS_F_Pin | R_SS_G_Pin;
            else if (player == yellow.buzzer)
                seven_seg_value = Y_SS_A_Pin | Y_SS_B_Pin | Y_SS_C_Pin | Y_SS_D_Pin |
                                  Y_SS_E_Pin | Y_SS_F_Pin | Y_SS_G_Pin;
            else if (player == green.buzzer)
                seven_seg_value = G_SS_A_Pin | G_SS_B_Pin | G_SS_C_Pin | G_SS_D_Pin |
                                  G_SS_E_Pin | G_SS_F_Pin | G_SS_G_Pin;
            break;

        case SS_NINE:
            if (player == blue.buzzer)
                seven_seg_value = B_SS_A_Pin | B_SS_B_Pin | B_SS_C_Pin |
                                  B_SS_D_Pin |B_SS_F_Pin | B_SS_G_Pin;
            else if (player == red.buzzer)
                seven_seg_value = R_SS_A_Pin | R_SS_B_Pin | R_SS_C_Pin |
                                  R_SS_D_Pin | R_SS_F_Pin | R_SS_G_Pin;
            else if (player == yellow.buzzer)
                seven_seg_value = Y_SS_A_Pin | Y_SS_B_Pin | Y_SS_C_Pin |
                                  Y_SS_D_Pin | Y_SS_F_Pin | Y_SS_G_Pin;
            else if (player == green.buzzer)
                seven_seg_value = G_SS_A_Pin | G_SS_B_Pin | G_SS_C_Pin |
                                  G_SS_D_Pin | G_SS_F_Pin | G_SS_G_Pin;
            break;

        default:
            break;
    }

    return seven_seg_value;
}
