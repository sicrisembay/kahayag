#ifndef ENCODER_H
#define ENCODER_H

//*****************************************************************************
// File dependencies.
//*****************************************************************************
#include "stdint.h"
#include "stdbool.h"
#include "fix16.h"
#include "test/test_encoder.h"

//*****************************************************************************
// Public / Internal definitions.
//*****************************************************************************
/*!
 * @brief Selection of all available Encoder ID
 */
typedef enum {
    ENCODER_ID_1 = 0,       /*!< Encoder 1 */
    ENCODER_ID_2,           /*!< Encoder 2 */
    ENCODER_ID_3,           /*!< Encoder 3 */
    ENCODER_ID_4,           /*!< Encoder 4 */
    ENCODER_ID_MAX
} encoder_id_t;

/*!
 * @brief Selection of all available Encoder decoding mode
 */
typedef enum {
    ENCODER_MODE_1X = 0,    /*!< 1X Decoding */
    ENCODER_MODE_2X = 1,    /*!< 2X Decoding */
    ENCODER_MODE_4X = 2,    /*!< 4X Decoding */
    ENCODER_MODE_MAX
} encoder_decode_mode_t;

/*!
 * @brief Selection of all available Encoder Type
 */
typedef enum {
    ENCODER_TYPE_SINGLE_CH = 0, /*!< Single Channel Encoder */
    ENCODER_TYPE_QUAD,          /*!< Quadrature Channel Encoder */
    ENCODER_TYPE_MAX
} encoder_type_t;

#if(ENABLE_ENCODER_TEST != 0)
#define ENC_UPDATE(x)
#else
#define ENC_UPDATE(x)      encoder_update(x)
#endif /* #if(ENABLE_ENCODER_TEST != 0) */

//*****************************************************************************
// Public function prototypes.
//*****************************************************************************
void encoder_init(void);
void encoder_deinit(void);
void encoder_update(encoder_id_t id);
int32_t encoder_getCount(encoder_id_t id);
void encoder_setCount(encoder_id_t id, int32_t count);
void encoder_set_position_value(encoder_id_t id, fix16_t value);
fix16_t encoder_get_position(encoder_id_t id);
fix16_t encoder_get_speed(encoder_id_t id);
bool encoder_IsValid(encoder_id_t id);

#endif // End ENCODER_H
