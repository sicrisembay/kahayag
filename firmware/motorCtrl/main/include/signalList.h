#ifndef _SIGNAL_LIST_H_
#define _SIGNAL_LIST_H_

enum appSignals {
    // Events/Signals that are published **************************************
    // Published BDC Motor Signal
    BDC_MOTOR_READY_SIG,
    BDC_MOTOR_MOVE_DONE_SIG,
    BDC_MOTOR_STOPPED_SIG,
    BDC_MOTOR_ERROR_SIG,

    MAX_PUB_SIG,                            // last published signal

    // Events/Signals that are posted directly *******************************
    TIMEOUT_SIG,
    TICK_SIG,
    GET_OBJECT_DICTIONARY_SIG,
    GET_FUNC_DICTIONARY_SIG,
    GET_SIGNAL_DICTIONARY_SIG,
    // Signals in BDC Motor
    BDC_MOTOR_CTRL_TIMEOUT_SIG,
    BDC_MOTOR_STOP_SIG,
    BDC_MOTOR_OPEN_LOOP_SIG,
    BDC_MOTOR_SPEED_RUN_SIG,
    BDC_MOTOR_POSITION_MOVE_SIG,


    MAX_SIG
};

enum appRecords {
    RECORD_MOTOR = QS_USER,
    RECORD_STREAM,
};

/* TAG Definitions */
// Message Types **************************************************************
//! \enum MESSAGE_TAG
enum MESSAGE_TAG {
    STREAM_TAG = 0xFF,      //!< Value: 0xFF.  Tag used for stream-type message.
    EVENT_TAG = 0xFE,       //!< Value: 0xFE.  Tag used for event-type message.
    RESPONSE_TAG = 0xFD     //!< Value: 0xFD.  Tag used for response-type message.
};

#endif /* #ifndef _SIGNAL_LIST_H_ */
