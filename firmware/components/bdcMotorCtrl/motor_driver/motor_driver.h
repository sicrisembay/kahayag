#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

//*****************************************************************************
// File dependencies.
//*****************************************************************************

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

//*****************************************************************************
// Public function prototypes.
//*****************************************************************************


#endif // End MOTOR_DRIVER_H
