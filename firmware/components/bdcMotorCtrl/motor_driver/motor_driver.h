#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

//*****************************************************************************
// File dependencies.
//*****************************************************************************
#include "fix16.h"

//*****************************************************************************
// Public / Internal definitions.
//*****************************************************************************
/*!
 * @brief Selection of all available motor driver ID
 */
typedef enum {
    MOTOR_DRIVER_ID_1 = 0,      /*!< Motor Driver 1 */
    MOTOR_DRIVER_ID_2,          /*!< Motor Driver 2 */
    MOTOR_DRIVER_ID_3,          /*!< Motor Driver 3 */
    MOTOR_DRIVER_ID_4,          /*!< Motor Driver 4 */
    MOTOR_DRIVER_MAX
} motor_driver_id_t;

/*!
 * @brief Selection of all available motor drive mode
 */
typedef enum {
    MOTOR_DRIVER_MODE_CONST_CURRENT = 0,/*!< PWM Constant Current Control */
    MOTOR_DRIVER_MODE_EXT_PWM,          /*!< External PWM */
	MOTOR_DRIVER_MODE_MAX
} motor_driver_mode_t;

//*****************************************************************************
// Public function prototypes.
//*****************************************************************************

void motor_driver_init(void);
void motor_driver_safe_state(void);
void motor_driver_set_extPwm(motor_driver_id_t id, fix16_t value);
void motor_driver_set_current(motor_driver_id_t id, fix16_t value);
fix16_t motor_driver_get_extPwm(motor_driver_id_t id);
fix16_t motor_driver_get_currentRef(motor_driver_id_t id);
motor_driver_mode_t motor_driver_get_mode(motor_driver_id_t id);
fix16_t motor_driver_get_posLimit(motor_driver_id_t id);
fix16_t motor_driver_get_negLimit(motor_driver_id_t id);

#endif // End MOTOR_DRIVER_H
