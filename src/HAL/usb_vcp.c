#include "usb_vcp.h"

#define USB_RX_BUFFER_LENGTH		512
#define USB_TX_BUFFER_LENGTH		512

//USB Device Core handle declaration
USBD_HandleTypeDef hUsbDeviceFS;

static int8_t USBVCPOnConnect();
static int8_t USBVCPOnDisconnect();
static int8_t USBVCPControl(uint8_t cmd, uint8_t* pbuf, uint16_t length);
static int8_t USBVCPOnReceive(uint8_t* Buf, uint32_t *Len);

USBD_CDC_ItfTypeDef USBD_Interface_fops_FS = {
	USBVCPOnConnect,
	USBVCPOnDisconnect,
	USBVCPControl,
	USBVCPOnReceive
};

//USB RX buffer Variables
uint16_t usbRXBufferLength = 0;
uint8_t usbRXBufferFull = 0;
uint8_t usbRXBuffer[USB_RX_BUFFER_LENGTH];		//Received data over USB are stored in this buffer

//USB TX buffer Variables
uint8_t usbTXBuffer[USB_TX_BUFFER_LENGTH];		//Data to send over USB CDC are stored in this buffer

//USB COM Port status variables
uint8_t usbCOMPortOpen = 0;

/**
  * @brief	This function initializes the USB VCP Peripheral
  * @param	None
  * @return	USBD_OK if all operations are OK else USBD_FAIL
  */
uint8_t USBVCPInit() {
	//Init Device Library, add supported class and start the library
	if (USBD_Init(&hUsbDeviceFS, &FS_Desc, DEVICE_FS) != USBD_OK) {
		//Error_Handler();
		return USBD_FAIL;
	}
	if (USBD_RegisterClass(&hUsbDeviceFS, &USBD_CDC) != USBD_OK) {
		//Error_Handler();
		return USBD_FAIL;
	}
	if (USBD_CDC_RegisterInterface(&hUsbDeviceFS, &USBD_Interface_fops_FS) != USBD_OK) {
		//Error_Handler();
		return USBD_FAIL;
	}
	if (USBD_Start(&hUsbDeviceFS) != USBD_OK) {
		//Error_Handler();
		return USBD_FAIL;
	}

	return USBD_OK;
}

/**
  * @brief	This function reads the USB VCP receive buffer
  * @param	data: data array to where the received data should be copied to
  * @param	length: length of the received array, is set in this function
  * @return	Returns 0 if no new data, 1 if new data
  */
uint8_t USBVCPRead(uint8_t* data, uint16_t* length) {
	//First check if COM Port is open
	if(usbCOMPortOpen == 0) {
		//COM Port not open, return error
		return 0;
	}

	if(usbRXBufferFull == 1) {
		uint16_t i;
		for(i = 0; i < usbRXBufferLength; i++) {
			data[i] = usbRXBuffer[i];
		}

		*length = usbRXBufferLength;
		usbRXBufferFull = 0;

		return 1;
	}
	else {
		return 0;
	}
}

/**
  * @brief	This function writes data over USB VCP
  * @param	data: data array to transmit
  * @param	length: length of the transmit data array
  * @return	USBD_OK if all operations are OK else USBD_FAIL
  */
uint8_t USBVCPWrite(uint8_t* data, uint16_t length) {
	uint8_t result = USBD_OK;

	//First check if COM Port is open
	if(usbCOMPortOpen == 0) {
		//COM Port not open, return error
		return USBD_FAIL;
	}

	//Check if USB device is busy, if busy wait for not busy or timeout
	uint32_t timeout = GetSysTick();
	USBD_CDC_HandleTypeDef* hcdc = (USBD_CDC_HandleTypeDef*)hUsbDeviceFS.pClassData;
	while(hcdc->TxState != 0 && (timeout + USB_VCP_WRITE_TIMEOUT) > GetSysTick()) {
		hcdc = (USBD_CDC_HandleTypeDef*)hUsbDeviceFS.pClassData;
	}
	if (hcdc->TxState != 0) {
		//USB device is busy, return
		return USBD_BUSY;
	}

	//Set the USB send buffer
	USBD_CDC_SetTxBuffer(&hUsbDeviceFS, data, length);
	result = USBD_CDC_TransmitPacket(&hUsbDeviceFS);

	return result;
}

/**
  * @brief	This function returns if there is a open port
  * @param	None
  * @return	1 if yes, 0 if no
  */
uint8_t USBVCPIsConnected() {
	return usbCOMPortOpen;
}

/**
  * @brief	This function is called when USB gets connected
  * @param	None
  * @return	USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t USBVCPOnConnect() {
	USBD_CDC_SetTxBuffer(&hUsbDeviceFS, usbTXBuffer, 0);
	USBD_CDC_SetRxBuffer(&hUsbDeviceFS, usbRXBuffer);
	USBD_CDC_ReceivePacket(&hUsbDeviceFS);
	return USBD_OK;
}

/**
  * @brief	This function is called when USB gets disconnected
  * @param	None
  * @return	USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t USBVCPOnDisconnect() {
	return USBD_OK;
}

/**
  * @brief	Manage the CDC class requests
  * @param  cmd: Command code
  * @param  pbuf: Buffer containing command data (request parameters)
  * @param  length: Number of data to be sent (in bytes)
  * @return	USBD_OK if all operations are OK else USBD_FAIL
  */
static uint8_t lineCoding[7] = {0x00, 0xC2, 0x01, 0x00, 0x00, 0x00, 0x08};	// 115200bps, 1stop, no parity, 8bit
static int8_t USBVCPControl(uint8_t cmd, uint8_t* pbuf, uint16_t length) {
	switch(cmd) {
		case CDC_SEND_ENCAPSULATED_COMMAND: {
			break;
		}
		case CDC_GET_ENCAPSULATED_RESPONSE: {
			break;
		}
		case CDC_SET_COMM_FEATURE: {
			break;
		}
		case CDC_GET_COMM_FEATURE: {
			break;
		}
		case CDC_CLEAR_COMM_FEATURE: {
			break;
		}
		/*******************************************************************************/
		/* Line Coding Structure                                                       */
		/*-----------------------------------------------------------------------------*/
		/* Offset | Field       | Size | Value  | Description                          */
		/* 0      | dwDTERate   |   4  | Number |Data terminal rate, in bits per second*/
		/* 4      | bCharFormat |   1  | Number | Stop bits                            */
		/*                                        0 - 1 Stop bit                       */
		/*                                        1 - 1.5 Stop bits                    */
		/*                                        2 - 2 Stop bits                      */
		/* 5      | bParityType |  1   | Number | Parity                               */
		/*                                        0 - None                             */
		/*                                        1 - Odd                              */
		/*                                        2 - Even                             */
		/*                                        3 - Mark                             */
		/*                                        4 - Space                            */
		/* 6      | bDataBits  |   1   | Number Data bits (5, 6, 7, 8 or 16).          */
		/*******************************************************************************/
		case CDC_SET_LINE_CODING: {
			memcpy(lineCoding, pbuf, sizeof(lineCoding));
			break;
		}
		case CDC_GET_LINE_CODING: {
			memcpy(pbuf, lineCoding, sizeof(lineCoding));
			break;
		}
		case CDC_SET_CONTROL_LINE_STATE: {
			USBD_SetupReqTypedef* req = (USBD_SetupReqTypedef*)pbuf;
			if((req->wValue & 0x0001) != 0) {
				usbCOMPortOpen = 1;
			}
			else {
				usbCOMPortOpen = 0;
			}
			break;
		}
		case CDC_SEND_BREAK: {
			break;
		}
		default: {
			break;
		}
	}
	return USBD_OK;
}

static int8_t USBVCPOnReceive(uint8_t* Buf, uint32_t *Len) {
	usbRXBufferLength =  *Len;
	usbRXBufferFull = 1;

	//Re-set the USB RX Buffer to be ready for the next reception
	USBD_CDC_SetRxBuffer(&hUsbDeviceFS, &Buf[0]);
	USBD_CDC_ReceivePacket(&hUsbDeviceFS);
	return (USBD_OK);
}
