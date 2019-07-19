#include <stdio.h>
#include "qpc.h"
#ifdef Q_SPY
#include "qs.h"
#endif /* #ifdef Q_SPY */
#include "nvs_flash.h"
#include "esp_log.h"
#include "bdcMotor.h"
#include "bt_bridge.h"
#include "dataStreamer.h"
#include "mpu9250.h"
#include "eMD.h"

static const char *TAG = "main";

/*
 * small size pool.
 * size: Evt
 */
static QF_MPOOL_EL(QEvt) smallPoolSto[CONFIG_QPC_SMALL_POOL_SIZE];
/*
 * medium size pool
 * size: QEvt + 16 Bytes
 */
typedef struct {
    QEvt super;
    uint32_t data[4];
} medPool;
static QF_MPOOL_EL(medPool) medPoolSto[CONFIG_QPC_MEDIUM_POOL_SIZE];

/*
 * large size pool
 * size: QEvt + 32 Bytes
 */
typedef struct {
    QEvt super;
    uint32_t data[8];
} largePool;
static QF_MPOOL_EL(largePool) largePoolSto[CONFIG_QPC_LARGE_POOL_SIZE];

void app_main()
{
    esp_err_t ret;

    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );

    /* initialize MPU9250 */
    mpu9250_init();

    eMD_Init();

    /* initialize bluetooth SPP */
    bt_bridge_init();

    /* initialize data streamer */
    ret = data_streamer_init();
    ESP_ERROR_CHECK( ret );

    /* Initialize the framework */
    QF_init();

#ifdef Q_SPY
    QS_INIT((void*)0);
#endif /* Q_SPY */

    /* Initialize Event Pool
     * Note: QF can manage up to three event pools (e.g., small, medium, and large events).
     * An application may call this function up to three times to initialize up to three event
     * pools in QF.  The subsequent calls to QF_poolInit() function must be made with
     * progressively increasing values of the evtSize parameter.
     */
    QF_poolInit(smallPoolSto, sizeof(smallPoolSto), sizeof(smallPoolSto[0]));
    QF_poolInit(medPoolSto, sizeof(medPoolSto), sizeof(medPoolSto[0]));
    QF_poolInit(largePoolSto, sizeof(largePoolSto), sizeof(largePoolSto[0]));

    bdc_motor_ctor();

    /* Run QF */
    QF_run();

    ESP_LOGI(TAG, "Goodbye app_main()\n");
}

