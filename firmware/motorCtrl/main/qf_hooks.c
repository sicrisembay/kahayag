#include "qpc.h"
#include "priorityList.h"
#include "driver/uart.h"
#include "esp_log.h"

#ifdef Q_SPY
static uint8_t qsTxBuf[CONFIG_QPC_QSPY_TX_SIZE];
static uint8_t qsRxBuf[CONFIG_QPC_QSPY_RX_SIZE];
static QSTimeCtr QS_tickTime_;
static QSTimeCtr QS_tickPeriod_;
//#define PRIORITY_QSPY_TX   (tskIDLE_PRIORITY + 1)
//#define PRIORITY_QSPY_RX   (tskIDLE_PRIORITY + 1)
#endif /* #ifdef Q_SPY */

static const char *TAG = "qf_hooks";

void QF_onStartup(void)
{
    /* Register Tick Hook */
}

IRAM_ATTR void Q_onAssert(char_t const * const module, int_t location)
{
    ESP_LOGE(TAG, "Q_onAssert: module:%s loc:%d\n", module, location);
}

#ifdef Q_SPY
#define QSPY_PORT   (UART_NUM_1)
#define TXD_PIN     CONFIG_QPC_QSPY_TX_PIN
#define RXD_PIN     CONFIG_QPC_QSPY_RX_PIN
#define RD_BUF_SIZE (128)
uint8_t readBuffer[RD_BUF_SIZE];

static void _QSpyRxTask(void *pxParam)
{
    int32_t nBytesRead = 0;
    static const char *QSPY_TASK_TAG = "QSPY_RX_TASK";
    esp_log_level_set(QSPY_TASK_TAG, ESP_LOG_INFO);
    ESP_LOGI(QSPY_TASK_TAG, "QSpy Task is up!\n");
    while(1) {
        /* Receive UART data */
        nBytesRead = uart_read_bytes(QSPY_PORT, readBuffer, RD_BUF_SIZE, 5 / portTICK_RATE_MS);
        if(nBytesRead > 0) {
           int32_t idx = 0;
           for(idx = 0; idx < nBytesRead; idx++) {
               QS_RX_PUT(readBuffer[idx]);
           }
           QS_rxParse();
        }
    }
}

static void _QSpyTxTask(void *pxParam)
{
    uint16_t nTxBytes = 0;
    uint8_t const *pTxBlock;
    static const char *QSPY_TASK_TAG = "QSPY_TX_TASK";
    esp_log_level_set(QSPY_TASK_TAG, ESP_LOG_INFO);
    ESP_LOGI(QSPY_TASK_TAG, "QSpy Task is up!\n");
    while(1) {
        uart_wait_tx_done(QSPY_PORT, (TickType_t)portMAX_DELAY);
        while(1) {
            nTxBytes = UART_FIFO_LEN;
            pTxBlock = QS_getBlock(&nTxBytes);
            if(nTxBytes != 0) {
                break;
            } else {
                vTaskDelay( 5 / portTICK_RATE_MS);
            }
        }
        uart_tx_chars(QSPY_PORT, (char *)pTxBlock, nTxBytes);
    }
}

uint8_t QS_onStartup(void const *arg)
{
    const uart_config_t uart_config = {
            .baud_rate = 115200,
            .data_bits = UART_DATA_8_BITS,
            .parity = UART_PARITY_DISABLE,
            .stop_bits = UART_STOP_BITS_1,
            .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
        };

    QS_initBuf(qsTxBuf, sizeof(qsTxBuf));
    QS_rxInitBuf(qsRxBuf, sizeof(qsRxBuf));

    uart_param_config(QSPY_PORT, &uart_config);
    uart_set_pin(QSPY_PORT, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(QSPY_PORT, CONFIG_QPC_QSPY_RX_SIZE, CONFIG_QPC_QSPY_TX_SIZE, 0, NULL, 0);

    xTaskCreate(_QSpyRxTask, "QSpy_rx_task", CONFIG_QPC_QSPY_RX_STACK_SIZE, NULL, PRIORITY_QSPY_RX, NULL);
    xTaskCreate(_QSpyTxTask, "QSpy_tx_task", CONFIG_QPC_QSPY_TX_STACK_SIZE, NULL, PRIORITY_QSPY_TX, NULL);

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


void QS_onCommand(uint8_t cmdId,
                  uint32_t param1, uint32_t param2, uint32_t param3)
{
    (void)cmdId;
    (void)param1;
    (void)param2;
    (void)param3;
}

#endif /*  Q_SPY */
