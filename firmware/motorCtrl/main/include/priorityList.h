#ifndef _PRIORITY_LIST_H_
#define _PRIORITY_LIST_H_

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "qpc.h"

enum task_priority {
    PRIORITY_WORKER = tskIDLE_PRIORITY + 1,
    PRIORITY_QSPY,
    PRIORITY_DATA_STREAMER,
    PRIORITY_MPU9250,
    PRIORITY_MOTOR_ONE,
    PRIORITY_MOTOR_TWO,
    PRIORITY_MOTOR_THREE,
    PRIORITY_MOTOR_FOUR,
    PRIORITY_MAX
};

/* freeRTOS task priority should be less than configMAX_PRIORITIES
 * as defined in FreeRTOSConfig.h
 */
Q_ASSERT_COMPILE(PRIORITY_MAX < configMAX_PRIORITIES);

#endif /* _PRIORITY_LIST_H_ */
