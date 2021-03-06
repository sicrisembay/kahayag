/*$file${components::SystemManagement::components::wifi::.::Wifi.c} vvvvvvvv*/
/*
* Model: kahayag_suga.qm
* File:  ${components::SystemManagement::components::wifi::.::Wifi.c}
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
/*$endhead${components::SystemManagement::components::wifi::.::Wifi.c} ^^^^^*/
#include "qpc.h"
#include "Wifi.h"
#include "string.h"

#include "esp_log.h"
#include "esp_wifi.h"
#include "nvs_flash.h"

/*$declare${components::SystemManagement::components::wifi::Wifi} vvvvvvvvvv*/
/*${components::SystemManagement::components::wifi::Wifi} ..................*/
typedef struct {
/* protected: */
    QHsm super;

/* private: */
    QHsm * pParent;
    Wifi_HookFunction hookFunc[MAX_WIFI_HOOK];
} Wifi;

/* protected: */
static QState Wifi_initial(Wifi * const me, QEvt const * const e);
static QState Wifi_TOP(Wifi * const me, QEvt const * const e);
/*$enddecl${components::SystemManagement::components::wifi::Wifi} ^^^^^^^^^^*/

static Wifi l_Wifi;

/*$skip${QP_VERSION} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/* Check for the minimum required QP version */
#if (QP_VERSION < 650U) || (QP_VERSION != ((QP_RELEASE^4294967295U) % 0x3E8U))
#error qpc version 6.5.0 or higher required
#endif
/*$endskip${QP_VERSION} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*$define${components::SystemManagement::components::wifi::TAG} vvvvvvvvvvvv*/
/*${components::SystemManagement::components::wifi::TAG} ...................*/
static const char * TAG ="WIFI_QHSM";
/*$enddef${components::SystemManagement::components::wifi::TAG} ^^^^^^^^^^^^*/

/*$define${components::SystemManagement::components::wifi::Wifi_ctor} vvvvvv*/
/*${components::SystemManagement::components::wifi::Wifi_ctor} .............*/
QHsm * Wifi_ctor(QHsm * parent) {
    static uint8_t bInitDone = (uint8_t)0;
    int idx = 0;
    Wifi *me;

    if(bInitDone == (uint8_t)0) {
        me = &l_Wifi;
        /* Call constructor */
        QHsm_ctor(&me->super, Q_STATE_CAST(&Wifi_initial));

        /* Call orthogonal Component constructor */

        /* Call Timer Constructor */

        /* Initialize members */
        me->pParent = parent;
        for(idx = 0; idx < MAX_WIFI_HOOK; idx++) {
            me->hookFunc[idx] = NULL;
        }

        bInitDone = (uint8_t)1;
    }

    return(&me->super);
}
/*$enddef${components::SystemManagement::components::wifi::Wifi_ctor} ^^^^^^*/
/*$define${components::SystemManagement::components::wifi::Wifi_EventHandler} */
/*${components::SystemManagement::components::wifi::Wifi_EventHandler} .....*/
static esp_err_t Wifi_EventHandler(void * ctx, system_event_t * event) {
    int idx = 0;
    Wifi * me = &l_Wifi;
    esp_err_t retval;

    /* Invoke Hook event handler first */
    for(idx = 0; idx < MAX_WIFI_HOOK; idx++) {
        if(me->hookFunc[idx] != NULL) {
            retval = (*(me->hookFunc[idx]))(ctx, event);
            if(retval != ESP_OK) {
                ESP_LOGE(TAG, "Error returned by hookFunc");
            }
        }
    }

    switch(event->event_id) {
    case SYSTEM_EVENT_AP_START:
        ESP_LOGI(TAG, "SoftAP started");
        break;
    case SYSTEM_EVENT_AP_STOP:
        ESP_LOGI(TAG, "SoftAP stopped");
        break;
    case SYSTEM_EVENT_STA_START:
        esp_wifi_connect();
        break;
    case SYSTEM_EVENT_STA_GOT_IP:
        ESP_LOGI(TAG, "got ip:%s",
                 ip4addr_ntoa(&event->event_info.got_ip.ip_info.ip));
        break;
    case SYSTEM_EVENT_AP_STACONNECTED:
        ESP_LOGI(TAG, "station:"MACSTR" join, AID=%d",
                 MAC2STR(event->event_info.sta_connected.mac),
                 event->event_info.sta_connected.aid);
        break;
    case SYSTEM_EVENT_AP_STADISCONNECTED:
        ESP_LOGI(TAG, "station:"MACSTR"leave, AID=%d",
                 MAC2STR(event->event_info.sta_disconnected.mac),
                 event->event_info.sta_disconnected.aid);
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        break;
    default:
        break;
    }
    return ESP_OK;
}
/*$enddef${components::SystemManagement::components::wifi::Wifi_EventHandler} */
/*$define${components::SystemManagement::components::wifi::Wifi_AddHook} vvv*/
/*${components::SystemManagement::components::wifi::Wifi_AddHook} ..........*/
esp_err_t Wifi_AddHook(Wifi_HookFunction pfn) {
    int idx = 0;
    Wifi * me = &l_Wifi;

    if(pfn == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    for(idx = 0; idx < MAX_WIFI_HOOK; idx++) {
        if(me->hookFunc[idx] == NULL) {
            me->hookFunc[idx] = pfn;
            return ESP_OK;
        }
    }

    return ESP_ERR_NOT_FOUND;
}
/*$enddef${components::SystemManagement::components::wifi::Wifi_AddHook} ^^^*/
/*$define${components::SystemManagement::components::wifi::Wifi_RemoveHook} */
/*${components::SystemManagement::components::wifi::Wifi_RemoveHook} .......*/
esp_err_t Wifi_RemoveHook(Wifi_HookFunction pfn) {
    int idx = 0;
    Wifi * me = &l_Wifi;

    if(pfn == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    for(idx = 0; idx < MAX_WIFI_HOOK; idx++) {
        if(me->hookFunc[idx] == pfn) {
            me->hookFunc[idx] = NULL;
            return ESP_OK;
        }
    }

    return ESP_ERR_NOT_FOUND;
}
/*$enddef${components::SystemManagement::components::wifi::Wifi_RemoveHook} */

/*$define${components::SystemManagement::components::wifi::Wifi} vvvvvvvvvvv*/
/*${components::SystemManagement::components::wifi::Wifi} ..................*/
/*${components::SystemManagement::components::wifi::Wifi::SM} ..............*/
static QState Wifi_initial(Wifi * const me, QEvt const * const e) {
    /*${components::SystemManagement::components::wifi::Wifi::SM::initial} */

    QS_FUN_DICTIONARY(&Wifi_TOP);

    return Q_TRAN(&Wifi_TOP);
}
/*${components::SystemManagement::components::wifi::Wifi::SM::TOP} .........*/
static QState Wifi_TOP(Wifi * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*${components::SystemManagement::components::wifi::Wifi::SM::TOP} */
        case Q_ENTRY_SIG: {
            wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
            wifi_config_t wifi_cfg;

            ESP_LOGI(TAG, "Initialize networking stack");
            tcpip_adapter_init();

            ESP_LOGI(TAG, "Set event handling");
            ESP_ERROR_CHECK(esp_event_loop_init(Wifi_EventHandler, NULL));

            if (esp_wifi_init(&cfg) != ESP_OK) {
                ESP_LOGE(TAG, "Failed to init wifi");
            }

            if (esp_wifi_get_config(ESP_IF_WIFI_STA, &wifi_cfg) != ESP_OK) {
                ESP_LOGE(TAG, "Failed to get WiFi Station Configuration");
            }

            if (strlen((const char*) wifi_cfg.sta.ssid)) {
                ESP_LOGI(TAG, "Found ssid %s",     (const char*) wifi_cfg.sta.ssid);
                ESP_LOGI(TAG, "Found password %s", (const char*) wifi_cfg.sta.password);
            }
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status_;
}
/*$enddef${components::SystemManagement::components::wifi::Wifi} ^^^^^^^^^^^*/
