/**
  * @file    ui_tools.h
  * @version 1.0
*/

#ifndef UI_TOOLS_H_
#define UI_TOOLS_H_

// Defines
#define TOGGLE_TIMING       15 // *10ms

// Seven segments digit values
typedef enum
{
    SS_ZERO = 0,
    SS_ONE = 1,
    SS_TWO = 2,
    SS_THREE = 3,
    SS_FOUR = 4,
    SS_FIVE = 5,
    SS_SIX = 6,
    SS_SEVEN = 7,
    SS_EIGHT = 8,
    SS_NINE = 9,
} sevenseg_digit_t;

typedef struct
{
    uint16_t blue;
    uint16_t red;
    uint16_t yellow;
    uint16_t green;

}sevenseg_data_t;

void set_reset_all_buzzleds(GPIO_PinState set_reset);
void toggle_all_buzzleds();
void mask_buzzleds(uint32_t players_mask);
void blink_all_buzzleds(uint8_t blink_cnt, portTickType period);
uint16_t num_to_sevenseg(sevenseg_digit_t digit, uint16_t player);


#endif  /* UI_TOOLS_H_ */
