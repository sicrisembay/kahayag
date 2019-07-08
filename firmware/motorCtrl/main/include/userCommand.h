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

#define CMD_MOTOR_OPEN_LOOP                     (0x13)
#define CMD_MOTOR_SET_SPEED_COEFFA              (0x14)
#define CMD_MOTOR_SET_SPEED_COEFFB              (0x15)
#define CMD_MOTOR_SET_SPEED_COEFFC              (0x16)
#define CMD_MOTOR_SET_POS_KP                    (0x17)
//*****************************************************************************
// CmdId : CMD_DATA_STREAM_SET_FLAG             (0x30)
// param1: StreamFlagMask
// param2: 0: Disable, 1: Enable
// param3: Unused
//*****************************************************************************
#define CMD_DATA_STREAM_SET_FLAG                (0x30)

#endif // End _USER_COMMAND_H_
