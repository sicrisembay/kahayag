/*$file${components::SystemManagement::.::SysMngt.h} vvvvvvvvvvvvvvvvvvvvvvv*/
/*
* Model: kahayag_suga.qm
* File:  ${components::SystemManagement::.::SysMngt.h}
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
/*$endhead${components::SystemManagement::.::SysMngt.h} ^^^^^^^^^^^^^^^^^^^^*/
#ifndef SYS_MNGT_H
#define SYS_MNGT_H

#include "InOut.h"

#define SYS_MNGT_TICK_INTERVAL_MS        (10)
#define SYS_MNGT_USER_BTN_ID             (INPUT_ID_ONE)

/** SRS-0011 */
#define SYS_MNGT_PROV_BTN_DLY_MS         (2000)
#define SYS_MNGT_PROV_BTN_TICK_INT       (SYS_MNGT_PROV_BTN_DLY_MS / SYS_MNGT_TICK_INTERVAL_MS)


/*$declare${components::SystemManagement::AO_SysMngt} vvvvvvvvvvvvvvvvvvvvvv*/

/** Opaque pointer to SysMngt AO */
extern QActive * const AO_SysMngt;
/*$enddecl${components::SystemManagement::AO_SysMngt} ^^^^^^^^^^^^^^^^^^^^^^*/

/*$declare${components::SystemManagement::SysMgnt_ctor} vvvvvvvvvvvvvvvvvvvv*/
/*${components::SystemManagement::SysMgnt_ctor} ............................*/
void SysMgnt_ctor(void);
/*$enddecl${components::SystemManagement::SysMgnt_ctor} ^^^^^^^^^^^^^^^^^^^^*/

#endif /* SYS_MNGT_H */