#include "qpc.h"
#include "freertos/ringbuf.h"
#include "freertos/task.h"
#include "priorityList.h"
#include "esp_log.h"
#include "bt_bridge.h"


#ifdef Q_SPY
static uint8_t qsTxBuf[CONFIG_QPC_QSPY_TX_SIZE];
static uint8_t qsRxBuf[CONFIG_QPC_QSPY_RX_SIZE];
//static QSTimeCtr QS_tickTime_;
//static QSTimeCtr QS_tickPeriod_;
#endif /* #ifdef Q_SPY */

static const char *TAG = "qf_hooks";
static const char *QSPY_TAG = "qspy";

void QF_onStartup(void)
{
    QS_filterOn(QS_UA_RECORDS);
}

IRAM_ATTR void Q_onAssert(char_t const * const module, int_t location)
{
    ESP_LOGE(TAG, "Q_onAssert: module:%s loc:%d\n", module, location);
}

#ifdef Q_SPY
#define RD_BUF_SIZE (128)
uint8_t readBuffer[RD_BUF_SIZE];

static void _QSpyTask(void *pxParam)
{
    uint8_t *pRxData = NULL;
    RingbufHandle_t RxBufHdl = NULL;
    size_t nRxData = 0;
    size_t idx = 0;
    uint16_t pktSize = 0;
    uint8_t const *pBlock;
    esp_err_t retval = ESP_OK;

#ifdef CONFIG_QPC_QSPY_PHY_BT_SPP
    while(1) {
        RxBufHdl = bt_bridge_get_rx_hdl();
        if(RxBufHdl == NULL) {
            vTaskDelay(1);
        } else {
            break;
        }
    }
#endif

    ESP_LOGI(QSPY_TAG, "QSpy Task is up.");

    while(1) {
        /* Check for receive data from BT */
        pRxData = (uint8_t *)xRingbufferReceiveUpTo(RxBufHdl, &nRxData, (TickType_t)(5 / portTICK_RATE_MS), 64);
        if(pRxData != NULL) {
            for(idx = 0; idx < nRxData; idx++) {
                QS_RX_PUT(pRxData[idx]);
            }
            vRingbufferReturnItem(RxBufHdl, (void*)pRxData);
            QS_rxParse();
        }
        /* Check if data needs to be tranmitted to BT */
#ifdef CONFIG_QPC_QSPY_PHY_BT_SPP
        if(bt_bridge_rdy()) {
            if(retval == ESP_OK) {
                /* Only get new block when the previous block
                 * was successfully transmitted.
                 */
                pktSize = 64;
                QF_CRIT_ENTRY(&qfMutex);
                pBlock = QS_getBlock(&pktSize);
                QF_CRIT_EXIT(&qfMutex);
            }
            if(pktSize > 0) {
                retval = bt_bridge_send((uint8_t *)pBlock, pktSize);
            }
        }
#else
#error "QSpy only support BT for this motor board"
#endif
    }
}

uint8_t QS_onStartup(void const *arg)
{
    QS_initBuf(qsTxBuf, sizeof(qsTxBuf));
    QS_rxInitBuf(qsRxBuf, sizeof(qsRxBuf));

    xTaskCreate(_QSpyTask, "QSpy", CONFIG_QPC_QSPY_STACK_SIZE, NULL, PRIORITY_QSPY, NULL);

    return (uint8_t)1; /* return success */
}


void QS_onCleanup(void)
{
    /// TODO: Implement functionality
}


IRAM_ATTR QSTimeCtr QS_onGetTime(void)
{
    return xTaskGetTickCount();
}


void QS_onFlush(void)
{
    /// TODO: Implement QS buffer flushing to HW peripheral
}


void QS_onReset(void)
{
    /// TODO: Implement functionality
}

#endif /*  Q_SPY */
