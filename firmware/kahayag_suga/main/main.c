#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "qpc.h"
#ifdef Q_SPY
#include "qs.h"
#endif /** Q_SPY */
#include "signalList.h"
#include "SysMngt.h"
#include "InOut.h"

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
/*
 * Storage for Publish-Subscribe
 */
static QSubscrList subscrSto[MAX_PUB_SIG];

void app_main()
{
    printf("Hello from app_main()\n");

    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("This is ESP32 chip with %d CPU cores, WiFi%s%s, ",
            chip_info.cores,
            (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
            (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    printf("silicon revision %d, ", chip_info.revision);

    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

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
    /* Initialize Publish-Subscribe */
    QF_psInit(subscrSto, Q_DIM(subscrSto));

    /* Call Active Object Constructors */
    SysMgnt_ctor();
    InOut_ctor();

    /* Run QF */
    QF_run();

    printf("Goodbye app_main()\n");
}

