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

static void _commandReply(uint32_t seq, uint8_t cmdId, uint8_t record, uint8_t sts)
{
    QS_BEGIN(record, QS_onCommand);
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
                _commandReply(0, cmdId, RECORD_MOTOR, RESPONSE_OK);
            } else {
                _commandReply(0, cmdId, RECORD_MOTOR, RESPONSE_INVALID);
            }
        } else {
            _commandReply(0, cmdId, RECORD_MOTOR, RESPONSE_INVALID);
        }
        break;
    }

    case CMD_MOTOR_RUN: {
        if(param1 < MOTOR_ID_MAX) {
            if(ESP_OK == bdc_motor_run(param1, (fix16_t)param2, QS_onCommand)) {
                _commandReply(0, cmdId, RECORD_MOTOR, RESPONSE_OK);
            } else {
                _commandReply(0, cmdId, RECORD_MOTOR, RESPONSE_INVALID);
            }
        } else {
            _commandReply(0, cmdId, RECORD_MOTOR, RESPONSE_INVALID);
        }
        break;
    }

    case CMD_MOTOR_MOVE: {
        if(param1 < MOTOR_ID_MAX) {
            if(ESP_OK == bdc_motor_move(param1, (fix16_t)param2, (fix16_t)param3, QS_onCommand)) {
                _commandReply(0, cmdId, RECORD_MOTOR, RESPONSE_OK);
            } else {
                _commandReply(0, cmdId, RECORD_MOTOR, RESPONSE_INVALID);
            }
        } else {
            _commandReply(0, cmdId, RECORD_MOTOR, RESPONSE_INVALID);
        }
        break;
    }

    case CMD_DATA_STREAM_SET_FLAG: {
        if(ESP_OK == data_streamer_enable(param1, param2)) {
            _commandReply(0, cmdId, RECORD_STREAM, RESPONSE_OK);
        } else {
            _commandReply(0, cmdId, RECORD_STREAM, RESPONSE_INVALID);
        }
        break;
    }
    default:
        break;
    }
}


#endif /*  Q_SPY */
