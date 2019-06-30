#ifndef TEST_MOTOR_DRIVER_H
#define TEST_MOTOR_DRIVER_H

//*****************************************************************************
// File dependencies.
//*****************************************************************************

//*****************************************************************************
// Public / Internal definitions.
//*****************************************************************************
#define ENABLE_MOTOR_DRIVER_TEST    (0)

//*****************************************************************************
// Public function prototypes.
//*****************************************************************************
#if(ENABLE_MOTOR_DRIVER_TEST != 0)
void test_motor_driver_init(void);
#endif /* #if(ENABLE_MOTOR_DRIVER_TEST != 0) */

#endif /* End TEST_MOTOR_DRIVER_H */
