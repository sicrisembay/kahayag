#ifndef _BT_BRIDGE_H_
#define _BT_BRIDGE_H_

#include "freertos/ringbuf.h"

extern void bt_bridge_init(void);
extern RingbufHandle_t bt_bridge_get_rx_hdl(void);
extern bool bt_bridge_rdy(void);
extern esp_err_t bt_bridge_send(uint8_t * pData, uint16_t size);

#endif /* _BT_BRIDGE_H_ */

