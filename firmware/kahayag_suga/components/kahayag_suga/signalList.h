/*$file${.::signalList.h} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*
* Model: kahayag_suga.qm
* File:  ${.::signalList.h}
*
* This code has been generated by QM 4.5.0 (https://www.state-machine.com/qm).
* DO NOT EDIT THIS FILE MANUALLY. All your changes will be lost.
*
* This program is open source software: you can redistribute it and/or
* modify it under the terms of the GNU General Public License as published
* by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
* or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
* for more details.
*/
/*$endhead${.::signalList.h} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
#ifndef SIGNAL_LIST_H
#define SIGNAL_LIST_H

enum testSignal {
    // Events/Signals that are published **************************************
    /* Published Sensor Signals */
    INPUT_POSITIVE_EDGE_SIG = Q_USER_SIG,
    INPUT_NEGATIVE_EDGE_SIG,

    MAX_PUB_SIG,                            // last published signal

    // Events/Signals that are posted directly *******************************
    GET_OBJECT_DICTIONARY_SIG,
    GET_FUNC_DICTIONARY_SIG,
    GET_SIGNAL_DICTIONARY_SIG,
    /* Module Generic Signal */
    TICK_SIG,
    /* Provision */
    START_PROVISION_SIG,
    AP_STARTED_SIG,
    AP_START_FAILED_SIG,
    PROV_SERVICE_STARTED_SIG,
    PROV_SERVICE_START_FAILED_SIG,
    PROV_SERVICE_STOPPED_SIG,
    PROV_SERVICE_TIMEOUT_SIG,

    MAX_SIG
};

#endif /* SIGNAL_LIST_H */