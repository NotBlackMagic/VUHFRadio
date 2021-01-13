#include "radioConfigs.h"
#include "radioStateMachine.h"

//BER Data variables
volatile uint32_t berTimestamp = 0;
volatile uint32_t errorBits = 0;
volatile uint32_t totalBits = 0;

//FIFO Data variables
volatile uint8_t newFIFODataPacketA;
volatile uint8_t fifoDataPacketLengthA;
volatile uint8_t fifoDataPacketA[255];

volatile uint8_t newFIFODataPacketB;
volatile uint8_t fifoDataPacketLengthB;
volatile uint8_t fifoDataPacketB[255];
void RadioBIRQHandler() {
	IrqRequest irqRequest = AX5043IrqGetIRQRequest(RADIO_B);

	if(irqRequest.irqrqfifonotempty == 0x01) {
		//FIFO Packet/Data available
		uint8_t fifoCnt;
		uint8_t rxRadioData[255];

		//Get FIFO Packet
		fifoCnt = AX5043FIFOGetFIFOCount(RADIO_B);
		AX5043FIFOGetFIFO(RADIO_B, rxRadioData, fifoCnt);

		uint8_t fifoIndex = 0;
		while(fifoIndex < fifoCnt) {
			uint8_t fifoOpcode = rxRadioData[fifoIndex++];
			switch(fifoOpcode) {
				case FIFO_RSSI: {
					radioBTracking.rssiTracking =  rxRadioData[fifoIndex++];
					break;
				}
				case FIFO_FREQOFFS: {
					int16_t trackFreq = (rxRadioData[fifoIndex++] << 8) + rxRadioData[fifoIndex++];
					break;
				}
				case FIFO_ANTRSSI2: {
					radioBTracking.rssiTracking = rxRadioData[fifoIndex++];
					int8_t bRSSI = rxRadioData[fifoIndex++];
					break;
				}
				case FIFO_TIMER: {
					uint32_t timer = (rxRadioData[fifoIndex++] << 16) + (rxRadioData[fifoIndex++] << 8) + rxRadioData[fifoIndex++];
					break;
				}
				case FIFO_RFFREQOFFS: {
					radioBTracking.rfFrequencyTracking = ((rxRadioData[fifoIndex++] << 28) + (rxRadioData[fifoIndex++] << 20) + (rxRadioData[fifoIndex++] << 12)) >> 12;
					break;
				}
				case FIFO_DATARATE: {
					uint32_t trackDatarate = (rxRadioData[fifoIndex++] << 16) + (rxRadioData[fifoIndex++] << 8) + rxRadioData[fifoIndex++];
					break;
				}
				case FIFO_ANTRSSI3: {
					radioBTracking.rssiTracking = rxRadioData[fifoIndex++];
					int8_t rssi2 = rxRadioData[fifoIndex++];
					int8_t bRSSI = rxRadioData[fifoIndex++];
					break;
				}
				case FIFO_DATA: {
					uint8_t dataLength = rxRadioData[fifoIndex++];
					uint8_t dataStatus = rxRadioData[fifoIndex++];

					fifoDataPacketLengthB = dataLength - 1;				//LENGTH Byte from the FIFO includes the status flags byte
					uint8_t i;
					for(i = 0; i < fifoDataPacketLengthB; i++) {
						fifoDataPacketB[i] = rxRadioData[fifoIndex++];
					}

					newFIFODataPacketB = 0x01;
					break;
				}
				default: {
					//Invalid OpCode, abort
					return;
				}
			}
		}
	}
}

void RadioAIRQHandler() {
	IrqRequest irqRequest = AX5043IrqGetIRQRequest(RADIO_A);

	if(irqRequest.irqrqfifonotempty == 0x01) {
		//FIFO Packet/Data available
		uint8_t fifoCnt;
		uint8_t rxRadioData[255];

		//Get FIFO Packet
		fifoCnt = AX5043FIFOGetFIFOCount(RADIO_A);
		AX5043FIFOGetFIFO(RADIO_A, rxRadioData, fifoCnt);

		uint8_t fifoIndex = 0;
		while(fifoIndex < fifoCnt) {
			uint8_t fifoOpcode = rxRadioData[fifoIndex++];
			switch(fifoOpcode) {
				case FIFO_RSSI: {
					radioATracking.rssiTracking =  rxRadioData[fifoIndex++];
					break;
				}
				case FIFO_FREQOFFS: {
					int16_t trackFreq = (rxRadioData[fifoIndex++] << 8) + rxRadioData[fifoIndex++];
					break;
				}
				case FIFO_ANTRSSI2: {
					radioATracking.rfFrequencyTracking = rxRadioData[fifoIndex++];
					int8_t bRSSI = rxRadioData[fifoIndex++];
					break;
				}
				case FIFO_TIMER: {
					uint32_t timer = (rxRadioData[fifoIndex++] << 16) + (rxRadioData[fifoIndex++] << 8) + rxRadioData[fifoIndex++];
					break;
				}
				case FIFO_RFFREQOFFS: {
					radioATracking.rfFrequencyTracking = ((rxRadioData[fifoIndex++] << 28) + (rxRadioData[fifoIndex++] << 20) + (rxRadioData[fifoIndex++] << 12)) >> 12;
					break;
				}
				case FIFO_DATARATE: {
					uint32_t trackDatarate = (rxRadioData[fifoIndex++] << 16) + (rxRadioData[fifoIndex++] << 8) + rxRadioData[fifoIndex++];
					break;
				}
				case FIFO_ANTRSSI3: {
					radioATracking.rssiTracking = rxRadioData[fifoIndex++];
					int8_t rssi2 = rxRadioData[fifoIndex++];
					int8_t bRSSI = rxRadioData[fifoIndex++];
					break;
				}
				case FIFO_DATA: {
					uint8_t dataLength = rxRadioData[fifoIndex++];
					uint8_t dataStatus = rxRadioData[fifoIndex++];
//					if((dataStatus & DATA_PKTEND) == DATA_PKTSTART) {
//
//					}

					fifoDataPacketLengthA = dataLength - 1;
					uint8_t i;
					for(i = 0; i < fifoDataPacketLengthA; i++) {
						fifoDataPacketA[i] = rxRadioData[fifoIndex++];
					}

					newFIFODataPacketA = 0x01;
					break;
				}
				default: {
					//Invalid OpCode, abort
					return;
				}
			}
		}
	}
}

uint8_t fDivider = 0;
void RadioTrackingUpdateHandler() {
	radioATracking.rssiTracking = AX5043GeneralGetRSSI(RADIO_UHF);
	radioBTracking.rssiTracking = AX5043GeneralGetRSSI(RADIO_VHF);

	if(radioATracking.rssiTracking >= RADIO_RSSI_THRESHOLD) {
		GPIOWrite(GPIO_OUT_LED1, 1);
	}
	else {
		GPIOWrite(GPIO_OUT_LED1, 0);
	}

	if(radioBTracking.rssiTracking >= RADIO_RSSI_THRESHOLD) {
		GPIOWrite(GPIO_OUT_LED3, 1);
	}
	else {
		GPIOWrite(GPIO_OUT_LED3, 0);
	}

	if(fDivider == 10) {
		//Update RF Frequency Tracking less frequently
		radioATracking.rfFrequencyTracking = AX5043RXTrackingGetRFFrequency(RADIO_UHF);
		radioBTracking.rfFrequencyTracking = AX5043RXTrackingGetRFFrequency(RADIO_VHF);

		fDivider = 0;
	}
	else {
		fDivider += 1;
	}
}

void RadioADCLKHandler() {
	uint8_t bit = GPIORead(GPIO_IN_DATA_U);

	if(bit != 0x00) {
		errorBits += 1;
	}

	totalBits += 1;

//	rawByteUHF += bit << rawByteIndexVHF;
//	if(rawByteIndexVHF == 0) {
//		rawByteReadyUHF = 1;
//		rawByteIndexUHF = 7;
//	}
//	else {
//		rawByteReadyUHF = 0;
//		rawByteIndexUHF -= 1;
//	}
}

void RadioBDCLKHandler() {
	uint8_t bit = GPIORead(GPIO_IN_DATA_V);

//	if(bit != 0x00) {
//		errorBits += 1;
//	}
//
//	totalBits += 1;

//	rawByteVHF += bit << rawByteIndexVHF;
//	if(rawByteIndexVHF == 0) {
//		rawByteReadyVHF = 1;
//		rawByteIndexVHF = 7;
//	}
//	else {
//		rawByteReadyVHF = 0;
//		rawByteIndexVHF -= 1;
//	}
}

/**
  * @brief	This function is the Handler for GPIO0s
  * @param	None
  * @return	None
  */
void EXTI0_IRQHandler(void) {
	if(LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_0) == 0x01 && LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_0) == 0x01) {
		//Interrupt for IRQ of Radio A, UHF
		RadioAIRQHandler();

		//Clear Interrupt Flag
		LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_0);
	}
}

/**
  * @brief	This function is the Handler for GPIO1s
  * @param	None
  * @return	None
  */
void EXTI1_IRQHandler(void) {
	if(LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_1) == 0x01 && LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_1) == 0x01) {
		//Interrupt for IRQ of Radio B, VHF
		RadioBIRQHandler();

		//Clear Interrupt Flag
		LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_1);
	}
}

/**
  * @brief	This function is the Handler for GPIO5s to GPIO9s
  * @param	None
  * @return	None
  */
void EXTI9_5_IRQHandler(void) {
	if(LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_8) == 0x01 && LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_8) == 0x01) {
		//Interrupt for DCLK of Radio B, VHF
		//Clear Interrupt Flag
		LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_8);

		RadioBDCLKHandler();
	}
}

/**
  * @brief	This function is the Handler for GPIO10s to GPIO15s
  * @param	None
  * @return	None
  */
void EXTI15_10_IRQHandler(void) {
	if(LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_11) == 0x01 && LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_11) == 0x01) {
		//Interrupt for DCLK of Radio A, UHF
		//Clear Interrupt Flag
		LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_11);

		RadioADCLKHandler();
	}
}

////Raw Radio Data interface (DATA) variables
//uint8_t rawByteReadyVHF = 0;
//uint8_t rawByteVHF = 0;
//uint8_t rawByteIndexVHF = 7;
//uint8_t rawByteReadyUHF = 0;
//uint8_t rawByteUHF = 0;
//uint8_t rawByteIndexUHF = 7;
//
//void RadioStateMachine() {
//	if(moduleDataMode == BER_Mode) {
//		if(berTimestamp + 1000 <= GetSysTick()) {
//			uint8_t str[200];
//
//			uint16_t len = sprintf(str, "UHF+");
//
//			int8_t rssi = AX5043GeneralGetRSSI(RADIO_UHF);
//			len += sprintf(&str[len], "RSSI=%d\n", rssi);
//
//			len += sprintf(&str[len], "UHF+BER=%d;%d\n", errorBits, totalBits);
//
//			USBVCPWrite(str, len);
//
//			berTimestamp = GetSysTick();
//		}
//		return;
//	}
//	else if(moduleDataMode == Raw_Bit_Mode) {
//		if(rawByteReadyVHF == 0x01) {
//			rawByteReadyVHF = 0;
//
//			uint8_t data[3];
//			data[0] = 'V';
//			data[1] = ':';
//			data[2] = rawByteReadyVHF;
//
//			USBVCPWrite(data, 3);
//		}
//		else if(rawByteReadyUHF == 0x01) {
//			rawByteReadyUHF = 0;
//
//			uint8_t data[3];
//			data[0] = 'U';
//			data[1] = ':';
//			data[2] = rawByteReadyUHF;
//
//			USBVCPWrite(data, 3);
//		}
//		return;
//	}
//
//	uint8_t radio = 0x02;
//	//Check for VHF and UHF Activity
//	if(GPIORead(GPIO_IN_IRQ_V) == 0x01) {
//		//Have VHF activity
//		radio = RADIO_VHF;
//	}
//	else if(GPIORead(GPIO_IN_IRQ_U) == 0x01) {
//		//Have UHF activity and no VHF
//		radio = RADIO_UHF;
//		GPIOWrite(GPIO_OUT_LED1, 0);	//Turn VHF RX LED off
//	}
//	else {
//		//No VHF or UHF Activity
//		GPIOWrite(GPIO_OUT_LED1, 0);	//Turn VHF RX LED off
//		GPIOWrite(GPIO_OUT_LED3, 0);	//Turn UHF RX LED off
//	}
//	return;
//
//	uint8_t fifoCnt = AX5043FIFOGetFIFOCount(radio);
//
//	uint8_t rxRadioData[300];
//	if(fifoCnt > 0) {
//		AX5043FIFOGetFIFO(radio, rxRadioData, fifoCnt);
//
//		uint8_t fifoIndex = 0;
//		while(fifoIndex < fifoCnt) {
//			uint16_t len = 0;
//			char str[300];
//			if(radio == RADIO_UHF) {
//				len = sprintf(str, "UHF+");
//			}
//			else if(radio == RADIO_VHF) {
//				len = sprintf(str, "VHF+");
//			}
//
//			uint8_t fifoOpcode = rxRadioData[fifoIndex++];
//			switch(fifoOpcode) {
//				case FIFO_RSSI: {
//					int8_t rssi =  rxRadioData[fifoIndex++];
//
//					len += sprintf(&str[len], "RSSI=%d\n", rssi);
//					USBVCPWrite(str, len);
//
//					break;
//				}
//				case FIFO_FREQOFFS: {
//					int16_t trackFreq = (rxRadioData[fifoIndex++] << 8) + rxRadioData[fifoIndex++];
//
//					len += sprintf(&str[len], "FOFF=%d\n", trackFreq);
//					USBVCPWrite(str, len);
//
//					break;
//				}
//				case FIFO_ANTRSSI2: {
//					int8_t rssi = rxRadioData[fifoIndex++];
//					int8_t bRSSI = rxRadioData[fifoIndex++];
//
//					len += sprintf(&str[len], "RSSI=%d,BGNDRSSI=%d\n", rssi, bRSSI);
//					USBVCPWrite(str, len);
//
//					break;
//				}
//				case FIFO_TIMER: {
//					uint32_t timer = (rxRadioData[fifoIndex++] << 16) + (rxRadioData[fifoIndex++] << 8) + rxRadioData[fifoIndex++];
//
//					len += sprintf(&str[len], "TIM=%d\n", timer);
//					USBVCPWrite(str, len);
//
//					break;
//				}
//				case FIFO_RFFREQOFFS: {
//					int32_t trackRFFreq = ((rxRadioData[fifoIndex++] << 28) + (rxRadioData[fifoIndex++] << 20) + (rxRadioData[fifoIndex++] << 12)) >> 12;
//
//					len += sprintf(&str[len], "RFFOFF=%d\n", trackRFFreq);
//					USBVCPWrite(str, len);
//
//					break;
//				}
//				case FIFO_DATARATE: {
//					uint32_t trackDatarate = (rxRadioData[fifoIndex++] << 16) + (rxRadioData[fifoIndex++] << 8) + rxRadioData[fifoIndex++];
//
//					len += sprintf(&str[len], "DRATE=%d\n", trackDatarate);
//					USBVCPWrite(str, len);
//
//					break;
//				}
//				case FIFO_ANTRSSI3: {
//					int8_t rssi1 = rxRadioData[fifoIndex++];
//					int8_t rssi2 = rxRadioData[fifoIndex++];
//					int8_t bRSSI = rxRadioData[fifoIndex++];
//
//					len += sprintf(&str[len], "RSSI1=%d,RSSI2=%d,BGNDRSSI=%d\n", rssi1, rssi2, bRSSI);
//					USBVCPWrite(str, len);
//
//					break;
//				}
//				case FIFO_DATA: {
//					uint8_t dataLength = rxRadioData[fifoIndex++];
//					uint8_t dataStatus = rxRadioData[fifoIndex];
//
//					uint8_t crc = (dataStatus & DATA_CRCFAIL) >> 3;
//					if(dataLength > 20) {
//						AX25Struct ax25Struct;
//						ax25Struct.payload = rxRadioData;
//
//						AX25Decode(&rxRadioData[fifoIndex + 1], dataLength - 1, &ax25Struct);
//
//						//AX25 Filtering, except CRC (CRC is part of HDLC frame)
//						if(AX25Filter(ax25Struct, uhfAX25FltStruct) == 0x00) {
//							uint8_t dspInfo = 0;
//
//							len += sprintf(&str[len], "DATA=", ax25Struct.destinationAddress);
//
//							//Add Destination, Source, Control and PID only if not filtered on those!
//							if(uhfAX25FltStruct.onDestinationAddress == 0x00) {
//								len += sprintf(&str[len], "%s,", ax25Struct.destinationAddress);
//								dspInfo = 1;
//							}
//							if(uhfAX25FltStruct.onSourceAddress == 0x00) {
//								len += sprintf(&str[len], "%s,", ax25Struct.sourceAddress);
//								dspInfo = 1;
//							}
//							if(uhfAX25FltStruct.onControlField == 0x00) {
//								len += sprintf(&str[len], "%d,", ax25Struct.control);
//								dspInfo = 1;
//							}
//							if(uhfAX25FltStruct.onPIDField == 0x00) {
//								len += sprintf(&str[len], "%d,", ax25Struct.pid);
//								dspInfo = 1;
//							}
//
//							//Check if any Info was added, to be displayed
//							if(dspInfo == 0x00) {
//								//No Info to display so reset len (string index counter)
//								len = 0;
//							}
//
//							//Add payload, on new line
//							len += sprintf(&str[len], "%d,", ax25Struct.payloadLength);
//
//							uint8_t i;
//							for(i = 0; i < ax25Struct.payloadLength; i++) {
//								str[len++] = ax25Struct.payload[i];
//							}
//
//							len += sprintf(&str[len], "\n");
//
//							USBVCPWrite(str, len);
//						}
//					}
//
//					if(radio == RADIO_UHF) {
//						GPIOWrite(GPIO_OUT_LED1, 1);
//					}
//					else if(radio == RADIO_VHF) {
//						GPIOWrite(GPIO_OUT_LED3, 1);
//					}
//
//					fifoIndex += dataLength;
//
//					break;
//				}
//				default: {
//					break;
//				}
//			}
//		}
//	}
//}
