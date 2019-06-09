#ifndef _SIGNAL_LIST_H_
#define _SIGNAL_LIST_H_
enum ItorAppSignals {
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

    MAX_SIG
};

#endif /* #ifndef _SIGNAL_LIST_H_ */