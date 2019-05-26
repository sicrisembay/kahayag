/*$file${components::SystemManagement::components::provision::.::Provision.h} */
/*
* Model: kahayag_suga.qm
* File:  ${components::SystemManagement::components::provision::.::Provision.h}
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
/*$endhead${components::SystemManagement::components::provision::.::Provision.h} */
#ifndef __KAHAYAG_PROVISION_H__
#define __KAHAYAG_PROVISION_H__

#define MAX_PROV_SSID_LEN        (16)
#define MAX_PROV_PASS_LEN        (32)

/*$declare${components::SystemManagement::components::provision::Prov_ctor} */
/*${components::SystemManagement::components::provision::Prov_ctor} ........*/
QHsm * Prov_ctor(QHsm * parent);
/*$enddecl${components::SystemManagement::components::provision::Prov_ctor} */

#endif /* __KAHAYAG_PROVISION_H__ */