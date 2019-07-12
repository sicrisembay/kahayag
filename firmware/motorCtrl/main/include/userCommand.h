#ifndef _USER_COMMAND_H_
#define _USER_COMMAND_H_

//*****************************************************************************
// File dependencies.
//*****************************************************************************

//*****************************************************************************
// Public / Internal definitions.
//*****************************************************************************

// Response Status ************************************************************
//! \enum RESPONSE_STATUS
enum RESPONSE_STATUS {
    RESPONSE_OK = 0,    //!< Value: 0x00. Response OK. Command has been accepted
    RESPONSE_INVALID    //!< Value: 0x01. Response for Invalid Command Parameters
};

// Events *********************************************************************

//*****************************************************************************
// CmdId : CMD_MOTOR_STOP                       (0x10)
// param1: Motor ID (0: MOTOR_ONE; 1: MOTOR_TWO; 2: MOTOR_THREE; 3: MOTOR_FOUR)
// param2: Unused
// param3: Unused
//*****************************************************************************
#define CMD_MOTOR_STOP                          (0x10)
//*****************************************************************************
// CmdId : CMD_MOTOR_RUN                        (0x11)
// param1: Motor ID (0: MOTOR_ONE; 1: MOTOR_TWO; 2: MOTOR_THREE; 3: MOTOR_FOUR)
// param2: Motor Reference Speed in radian per second (Q16 format)
// param3: Unused
//*****************************************************************************
#define CMD_MOTOR_RUN                           (0x11)
//*****************************************************************************
// CmdId : CMD_MOTOR_MOVE                       (0x12)
// param1: Motor ID (0: MOTOR_ONE; 1: MOTOR_TWO; 2: MOTOR_THREE; 3: MOTOR_FOUR)
// param2: Motor Reference Position in radian (Q16 format)
// param3: Motor Jog Speed in radian/second (Q16 format)
//*****************************************************************************
#define CMD_MOTOR_MOVE                          (0x12)
//*****************************************************************************
// CmdId : CMD_MOTOR_OPEN_LOOP
// param1: Motor ID (0: MOTOR_ONE; 1: MOTOR_TWO; 2: MOTOR_THREE; 3: MOTOR_FOUR)
// param2: Open Loop Value
// param3: Unused
//*****************************************************************************
#define CMD_MOTOR_OPEN_LOOP                     (0x13)
//*****************************************************************************
// CmdId : CMD_MOTOR_GET_CTRL_PARAM
// param1: Motor ID (0: MOTOR_ONE; 1: MOTOR_TWO; 2: MOTOR_THREE; 3: MOTOR_FOUR)
// param2: Unused
// param3: Unused
//*****************************************************************************
#define CMD_MOTOR_GET_CTRL_PARAM                (0x14)
//*****************************************************************************
// CmdId : CMD_MOTOR_SET_SPEED_COEFFA
// param1: Motor ID (0: MOTOR_ONE; 1: MOTOR_TWO; 2: MOTOR_THREE; 3: MOTOR_FOUR)
// param2: Value of Control Coefficient A (Fixed Pt Q16)
// param3: Unused
//*****************************************************************************
#define CMD_MOTOR_SET_SPEED_COEFFA              (0x15)
//*****************************************************************************
// CmdId : CMD_MOTOR_SET_SPEED_COEFFB
// param1: Motor ID (0: MOTOR_ONE; 1: MOTOR_TWO; 2: MOTOR_THREE; 3: MOTOR_FOUR)
// param2: Value of Control Coefficient B (Fixed Pt Q16)
// param3: Unused
//*****************************************************************************
#define CMD_MOTOR_SET_SPEED_COEFFB              (0x16)
//*****************************************************************************
// CmdId : CMD_MOTOR_SET_SPEED_COEFFC
// param1: Motor ID (0: MOTOR_ONE; 1: MOTOR_TWO; 2: MOTOR_THREE; 3: MOTOR_FOUR)
// param2: Value of Control Coefficient C (Fixed Pt Q16)
// param3: Unused
//*****************************************************************************
#define CMD_MOTOR_SET_SPEED_COEFFC              (0x17)
//*****************************************************************************
// CmdId : CMD_MOTOR_SET_POS_KP
// param1: Motor ID (0: MOTOR_ONE; 1: MOTOR_TWO; 2: MOTOR_THREE; 3: MOTOR_FOUR)
// param2: Value of Control Kp (Fixed Pt Q16)
// param3: Unused
//*****************************************************************************
#define CMD_MOTOR_SET_POS_KP                    (0x18)
//*****************************************************************************
// CmdId : CMD_MOTOR_SET_DRV_CONV_FACTOR
// param1: Motor ID (0: MOTOR_ONE; 1: MOTOR_TWO; 2: MOTOR_THREE; 3: MOTOR_FOUR)
// param2: Value (Fixed Pt Q16)
// param3: Unused
//*****************************************************************************
#define CMD_MOTOR_SET_DRV_CONV_FACTOR           (0x19)
//*****************************************************************************
// CmdId : CMD_MOTOR_SET_POSITION_VALUE
// param1: Motor ID (0: MOTOR_ONE; 1: MOTOR_TWO; 2: MOTOR_THREE; 3: MOTOR_FOUR)
// param2: Value (Fixed Pt Q16)
// param3: Unused
//*****************************************************************************
#define CMD_MOTOR_SET_POSITION_VALUE            (0x1A)

//*****************************************************************************
// CmdId : CMD_DATA_STREAM_SET_FLAG             (0x30)
// param1: StreamFlagMask
// param2: 0: Disable, 1: Enable
// param3: Unused
//*****************************************************************************
#define CMD_DATA_STREAM_SET_FLAG                (0x30)

#endif // End _USER_COMMAND_H_
