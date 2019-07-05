#ifndef _DATA_STREAMER_H_
#define _DATA_STREAMER_H_

//*****************************************************************************
// File dependencies.
//*****************************************************************************
#include "esp_err.h"

enum stream_id {
    /* Motor One */
    STREAM_MOTOR_ONE_POSITION = 0,
    STREAM_MOTOR_ONE_SPEED,
    STREAM_MOTOR_ONE_CURRENT,
    /* Motor Two */
    STREAM_MOTOR_TWO_POSITION,
    STREAM_MOTOR_TWO_SPEED,
    STREAM_MOTOR_TWO_CURRENT,
    /* Motor Three */
    STREAM_MOTOR_THREE_POSITION,
    STREAM_MOTOR_THREE_SPEED,
    STREAM_MOTOR_THREE_CURRENT,
    /* Motor Four */
    STREAM_MOTOR_FOUR_POSITION,
    STREAM_MOTOR_FOUR_SPEED,
    STREAM_MOTOR_FOUR_CURRENT,

    STREAM_MAX
};

#if (STREAM_MAX >= 30)
#error "Exceeded Max Stream Items!"
#endif

/* Motor One */
#define STREAM_MOTOR_ONE_POSITION_MASK      (1UL << STREAM_MOTOR_ONE_POSITION)
#define STREAM_MOTOR_ONE_SPEED_MASK         (1UL << STREAM_MOTOR_ONE_SPEED)
#define STREAM_MOTOR_ONE_CURRENT_MASK       (1UL << STREAM_MOTOR_ONE_CURRENT)
/* Motor Two */
#define STREAM_MOTOR_TWO_POSITION_MASK      (1UL << STREAM_MOTOR_TWO_POSITION)
#define STREAM_MOTOR_TWO_SPEED_MASK         (1UL << STREAM_MOTOR_TWO_SPEED)
#define STREAM_MOTOR_TWO_CURRENT_MASK       (1UL << STREAM_MOTOR_TWO_CURRENT)
/* Motor Three */
#define STREAM_MOTOR_THREE_POSITION_MASK    (1UL << STREAM_MOTOR_THREE_POSITION)
#define STREAM_MOTOR_THREE_SPEED_MASK       (1UL << STREAM_MOTOR_THREE_SPEED)
#define STREAM_MOTOR_THREE_CURRENT_MASK     (1UL << STREAM_MOTOR_THREE_CURRENT)
/* Motor Four */
#define STREAM_MOTOR_FOUR_POSITION_MASK     (1UL << STREAM_MOTOR_FOUR_POSITION)
#define STREAM_MOTOR_FOUR_SPEED_MASK        (1UL << STREAM_MOTOR_FOUR_SPEED)
#define STREAM_MOTOR_FOUR_CURRENT_MASK      (1UL << STREAM_MOTOR_FOUR_CURRENT)

#define STREAM_ALL_MASK                     ((1UL << STREAM_MAX) - 1)

esp_err_t data_streamer_init(void);
esp_err_t data_streamer_enable(uint32_t streamMask, bool enable);
esp_err_t data_streamer_setInterval(uint32_t intMs);

#endif // End _DATA_STREAMER_H_
