/**
  * @file    ui_tools.h
  * @version 1.0
*/

#ifndef UI_TOOLS_H_
#define UI_TOOLS_H_

// Defines
#define TOGGLE_TIMING       15 // *10ms

void set_reset_all_buzzleds(GPIO_PinState set_reset);
void toggle_all_buzzleds();
void mask_buzzleds(uint32_t players_mask);
void blink_all_buzzleds(uint8_t blink_cnt, portTickType period);
void blink_single_buzzled(player_t buzzer_led, uint8_t blink_cnt, portTickType period);

#endif  /* UI_TOOLS_H_ */
