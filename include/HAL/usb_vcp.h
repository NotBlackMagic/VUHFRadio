#ifndef HAL_USB_VCP_H_
#define HAL_USB_VCP_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "rcc.h"

#include "usbd_cdc.h"
#include "usbd_core.h"
#include "usbd_desc.h"

#define USB_VCP_WRITE_TIMEOUT				1000

extern USBD_CDC_ItfTypeDef USBD_Interface_fops_FS;

uint8_t USBVCPInit();
uint8_t USBVCPIsConnected();
uint8_t USBVCPRead(uint8_t* data, uint16_t* length);
uint8_t USBVCPWrite(uint8_t* data, uint16_t length);

#ifdef __cplusplus
}
#endif

#endif /* HAL_USB_VCP_H_ */
