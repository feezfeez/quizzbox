/**
  * @file    task_config.h
  * @author  C. Feeser
  * @version 1.0
  * @date    2020
  * @brief   Task Configuration prototypes and constants.
*/

#ifndef __TASK_CONFIG_H
#define __TASK_CONFIG_H

/*
 * Define tasks priorities
 */

#define BUZZER_TASK_PRIORITY        (tskIDLE_PRIORITY + 1)
#define HANDLER_TASK_PRIORITY       (tskIDLE_PRIORITY + 2)
#define FSM_TASK_PRIORITY           (tskIDLE_PRIORITY + 3)

#endif /* __TASK_CONFIG_H */
