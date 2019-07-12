#include "qpc.h"
#include "esp_log.h"
#include "esp_err.h"
#include "userCommand.h"
#include "signalList.h"
#include "dataStreamer.h"
#include "bdcMotor.h"

#ifdef Q_SPY

#ifdef CONFIG_USER_CMD_DEBUG_ENABLED
static const char *TAG = "user";
#endif

static void _motorCmdReply(uint32_t seq, uint8_t motorId, uint8_t cmdId, uint8_t sts)
{
    QS_BEGIN(RECORD_MOTOR, QS_onCommand);
    QS_U8(3, RESPONSE_TAG);
    QS_U32(10, seq);
    QS_U8(3, motorId);
    QS_U8(3, cmdId);
    QS_U8(3, sts);
    QS_END();
}
static void _sysCmdReply(uint32_t seq, uint8_t cmdId, uint8_t sts)
{
    QS_BEGIN(RECORD_STREAM, QS_onCommand);
    QS_U8(3, RESPONSE_TAG);
    QS_U32(10, seq);
    QS_U8(3, cmdId);
    QS_U8(3, sts);
    QS_END();
}

void QS_onCommand(uint8_t cmdId, uint32_t param1, uint32_t param2, uint32_t param3)
{
#ifdef CONFIG_USER_CMD_DEBUG_ENABLED
    ESP_LOGI(TAG, "cmd: 0x%02X, p1: %d, p2: %d, p3: %d", cmdId, param1, param2, param3);
#endif

    switch(cmdId) {
    case CMD_MOTOR_STOP: {
        if(param1 < MOTOR_ID_MAX) {
            if(ESP_OK == bdc_motor_stop(param1, QS_onCommand)) {
                _motorCmdReply(0, param1, cmdId, RESPONSE_OK);
            } else {
                _motorCmdReply(0, param1, cmdId, RESPONSE_INVALID);
            }
        } else {
            _motorCmdReply(0, param1, cmdId, RESPONSE_INVALID);
        }
        break;
    }

    case CMD_MOTOR_RUN: {
        if(param1 < MOTOR_ID_MAX) {
            if(ESP_OK == bdc_motor_run(param1, (fix16_t)param2, QS_onCommand)) {
                _motorCmdReply(0, param1, cmdId, RESPONSE_OK);
            } else {
                _motorCmdReply(0, param1, cmdId, RESPONSE_INVALID);
            }
        } else {
            _motorCmdReply(0, param1, cmdId, RESPONSE_INVALID);
        }
        break;
    }

    case CMD_MOTOR_MOVE: {
        if(param1 < MOTOR_ID_MAX) {
            if(ESP_OK == bdc_motor_move(param1, (fix16_t)param2, (fix16_t)param3, QS_onCommand)) {
                _motorCmdReply(0, param1, cmdId, RESPONSE_OK);
            } else {
                _motorCmdReply(0, param1, cmdId, RESPONSE_INVALID);
            }
        } else {
            _motorCmdReply(0, param1, cmdId, RESPONSE_INVALID);
        }
        break;
    }

    case CMD_MOTOR_OPEN_LOOP: {
        if(param1 < MOTOR_ID_MAX) {
            if(ESP_OK == bdc_motor_open_loop((motor_id_t)param1, (fix16_t)param2, QS_onCommand)) {
                _motorCmdReply(0, param1, cmdId, RESPONSE_OK);
            } else {
                _motorCmdReply(0, param1, cmdId, RESPONSE_INVALID);
            }
        } else {
            _motorCmdReply(0, param1, cmdId, RESPONSE_INVALID);
        }
        break;
    }

    case CMD_MOTOR_GET_CTRL_PARAM: {
        if(param1 < MOTOR_ID_MAX) {
            fix16_t ctrlParamVal = 0;
            QS_BEGIN(RECORD_MOTOR, QS_onCommand);
            QS_U8(3, RESPONSE_TAG);
            QS_U32(10, 0);//seq); // for now seq is 0
            QS_U8(3, (uint8_t)param1);
            QS_U8(3, (uint8_t)cmdId);
            QS_U8(3, (uint8_t)RESPONSE_OK);
            bdc_motor_get_pos_Kp((motor_id_t)param1, &ctrlParamVal);
            QS_I32(10, (uint32_t)ctrlParamVal);
            bdc_motor_get_speed_coeffA((motor_id_t)param1, &ctrlParamVal);
            QS_I32(10, (uint32_t)ctrlParamVal);
            bdc_motor_get_speed_coeffB((motor_id_t)param1, &ctrlParamVal);
            QS_I32(10, (uint32_t)ctrlParamVal);
            bdc_motor_get_speed_coeffC((motor_id_t)param1, &ctrlParamVal);
            QS_I32(10, (uint32_t)ctrlParamVal);
            bdc_motor_get_driver_conv_factor((motor_id_t)param1, &ctrlParamVal);
            QS_I32(10, (uint32_t)ctrlParamVal);
            QS_END();
        } else {
            _motorCmdReply(0, param1, cmdId, RESPONSE_INVALID);
        }
        break;
    }

    case CMD_MOTOR_SET_SPEED_COEFFA: {
        if(param1 < MOTOR_ID_MAX) {
            if(ESP_OK == bdc_motor_set_speed_coeffA((motor_id_t)param1, (fix16_t)param2)) {
                _motorCmdReply(0, param1, cmdId, RESPONSE_OK);
            } else {
                _motorCmdReply(0, param1, cmdId, RESPONSE_INVALID);
            }
        } else {
            _motorCmdReply(0, param1, cmdId, RESPONSE_INVALID);
        }
        break;
    }

    case CMD_MOTOR_SET_SPEED_COEFFB: {
        if(param1 < MOTOR_ID_MAX) {
            if(ESP_OK == bdc_motor_set_speed_coeffB((motor_id_t)param1, (fix16_t)param2)) {
                _motorCmdReply(0, param1, cmdId, RESPONSE_OK);
            } else {
                _motorCmdReply(0, param1, cmdId, RESPONSE_INVALID);
            }
        } else {
            _motorCmdReply(0, param1, cmdId, RESPONSE_INVALID);
        }
        break;
    }

    case CMD_MOTOR_SET_SPEED_COEFFC: {
        if(param1 < MOTOR_ID_MAX) {
            if(ESP_OK == bdc_motor_set_speed_coeffC((motor_id_t)param1, (fix16_t)param2)) {
                _motorCmdReply(0, param1, cmdId, RESPONSE_OK);
            } else {
                _motorCmdReply(0, param1, cmdId, RESPONSE_INVALID);
            }
        } else {
            _motorCmdReply(0, param1, cmdId, RESPONSE_INVALID);
        }
        break;
    }

    case CMD_MOTOR_SET_POS_KP: {
        if(param1 < MOTOR_ID_MAX) {
            if(ESP_OK == bdc_motor_set_pos_Kp((motor_id_t)param1, (fix16_t)param2)) {
                _motorCmdReply(0, param1, cmdId, RESPONSE_OK);
            } else {
                _motorCmdReply(0, param1, cmdId, RESPONSE_INVALID);
            }
        } else {
            _motorCmdReply(0, param1, cmdId, RESPONSE_INVALID);
        }
        break;
    }

    case CMD_MOTOR_SET_DRV_CONV_FACTOR: {
        if(param1 < MOTOR_ID_MAX) {
            if(ESP_OK == bdc_motor_set_driver_conv_factor((motor_id_t)param1, (fix16_t)param2)) {
                _motorCmdReply(0, param1, cmdId, RESPONSE_OK);
            } else {
                _motorCmdReply(0, param1, cmdId, RESPONSE_INVALID);
            }
        } else {
            _motorCmdReply(0, param1, cmdId, RESPONSE_INVALID);
        }
        break;
    }

    case CMD_MOTOR_SET_POSITION_VALUE: {
        if(param1 < MOTOR_ID_MAX) {
            if(ESP_OK == bdc_motor_set_position((motor_id_t)param1, (fix16_t)param2)) {
                _motorCmdReply(0, param1, cmdId, RESPONSE_OK);
            } else {
                _motorCmdReply(0, param1, cmdId, RESPONSE_INVALID);
            }
        } else {
            _motorCmdReply(0, param1, cmdId, RESPONSE_INVALID);
        }
    }
    case CMD_DATA_STREAM_SET_FLAG: {
        if(ESP_OK == data_streamer_enable(param1, param2)) {
            _sysCmdReply(0, cmdId, RESPONSE_OK);
        } else {
            _sysCmdReply(0, cmdId, RESPONSE_INVALID);
        }
        break;
    }

    default:
        break;
    }
}


#endif /*  Q_SPY */
