#ifndef _USER_COMMAND_H_
#define _USER_COMMAND_H_

//*****************************************************************************
// File dependencies.
//*****************************************************************************

//*****************************************************************************
// Public / Internal definitions.
//*****************************************************************************
// Message Types **************************************************************
//! \enum MESSAGE_TAG
enum MESSAGE_TAG {
    STREAM_TAG = 0xFF,      //!< Value: 0xFF.  Tag used for stream-type message.
    EVENT_TAG = 0xFE,       //!< Value: 0xFE.  Tag used for event-type message.
    RESPONSE_TAG = 0xFD     //!< Value: 0xFD.  Tag used for response-type message.
};

// Response Status ************************************************************
//! \enum RESPONSE_STATUS
enum RESPONSE_STATUS {
    RESPONSE_OK = 0,    //!< Value: 0x00. Response OK. Command has been accepted
    RESPONSE_INVALID    //!< Value: 0x01. Response for Invalid Command Parameters
};

// Events *********************************************************************
// MOTOR EVENT TAGS
#define EVENT_MOTOR_POSITION_REACHED            (0x00)
#define EVENT_MOTOR_STOPPED                     (0x01)

//*****************************************************************************
// CmdId : CMD_MOTOR_STOP                       (0x20)
// param1: Motor ID (0: MOTOR_ONE; 1: MOTOR_TWO; 2: MOTOR_THREE; 3: MOTOR_FOUR)
// param2: Unused
// param3: Unused
//*****************************************************************************
#define CMD_MOTOR_STOP                          (0x20)
//*****************************************************************************
// CmdId : CMD_MOTOR_RUN                        (0x21)
// param1: Motor ID (0: MOTOR_ONE; 1: MOTOR_TWO; 2: MOTOR_THREE; 3: MOTOR_FOUR)
// param2: Motor Reference Speed in radian per second (Q16 format)
// param3: Unused
//*****************************************************************************
#define CMD_MOTOR_RUN                           (0x21)
//*****************************************************************************
// CmdId : CMD_MOTOR_MOVE                       (0x22)
// param1: Motor ID (0: MOTOR_ONE; 1: MOTOR_TWO; 2: MOTOR_THREE; 3: MOTOR_FOUR)
// param2: Motor Reference Position in radian (Q16 format)
// param3: Motor Jog Speed in radian/second (Q16 format)
//*****************************************************************************
#define CMD_MOTOR_MOVE                          (0x22)

#endif // End _USER_COMMAND_H_
