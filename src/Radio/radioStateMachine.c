#include "radioStateMachine.h"

uint8_t fifoCnt;
uint8_t rxRadioData[300];
void RadioStateMachine(uint8_t radio) {
	fifoCnt = AX5043FIFOGetFIFOCount(radio);

	if(fifoCnt > 0) {
		AX5043FIFOGetFIFO(radio, rxRadioData, fifoCnt);

		uint8_t fifoIndex = 0;
		while(fifoIndex < fifoCnt) {
			uint16_t len = 0;
			char str[300];
			if(radio == RADIO_UHF) {
				len = sprintf(str, "UHF+");
			}
			else if(radio == RADIO_VHF) {
				len = sprintf(str, "VHF+");
			}

			uint8_t fifoOpcode = rxRadioData[fifoIndex++];
			switch(fifoOpcode) {
				case FIFO_RSSI: {
					int8_t rssi =  rxRadioData[fifoIndex++];

					len += sprintf(&str[len], "RSSI=%d\n", rssi);
					USBVCPWrite(str, len);

					break;
				}
				case FIFO_FREQOFFS: {
					int16_t trackFreq = (rxRadioData[fifoIndex++] << 8) + rxRadioData[fifoIndex++];

					len += sprintf(&str[len], "FOFF=%d\n", trackFreq);
					USBVCPWrite(str, len);

					break;
				}
				case FIFO_ANTRSSI2: {
					int8_t rssi = rxRadioData[fifoIndex++];
					int8_t bRSSI = rxRadioData[fifoIndex++];

					len += sprintf(&str[len], "RSSI=%d,BGNDRSSI=%d\n", rssi, bRSSI);
					USBVCPWrite(str, len);

					break;
				}
				case FIFO_TIMER: {
					uint32_t timer = (rxRadioData[fifoIndex++] << 16) + (rxRadioData[fifoIndex++] << 8) + rxRadioData[fifoIndex++];

					len += sprintf(&str[len], "TIM=%d\n", timer);
					USBVCPWrite(str, len);

					break;
				}
				case FIFO_RFFREQOFFS: {
					int32_t trackRFFreq = ((rxRadioData[fifoIndex++] << 28) + (rxRadioData[fifoIndex++] << 20) + (rxRadioData[fifoIndex++] << 12)) >> 12;

					len += sprintf(&str[len], "RFFOFF=%d\n", trackRFFreq);
					USBVCPWrite(str, len);

					break;
				}
				case FIFO_DATARATE: {
					uint32_t trackDatarate = (rxRadioData[fifoIndex++] << 16) + (rxRadioData[fifoIndex++] << 8) + rxRadioData[fifoIndex++];

					len += sprintf(&str[len], "DRATE=%d\n", trackDatarate);
					USBVCPWrite(str, len);

					break;
				}
				case FIFO_ANTRSSI3: {
					int8_t rssi1 = rxRadioData[fifoIndex++];
					int8_t rssi2 = rxRadioData[fifoIndex++];
					int8_t bRSSI = rxRadioData[fifoIndex++];

					len += sprintf(&str[len], "RSSI1=%d,RSSI2=%d,BGNDRSSI=%d\n", rssi1, rssi2, bRSSI);
					USBVCPWrite(str, len);

					break;
				}
				case FIFO_DATA: {
					uint8_t dataLength = rxRadioData[fifoIndex++];
					uint8_t dataStatus = rxRadioData[fifoIndex];

					uint8_t crc = (dataStatus & DATA_CRCFAIL) >> 3;
					if(dataLength > 20) {
						AX25Struct ax25Struct;
						ax25Struct.payload = rxRadioData;

						AX25Decode(&rxRadioData[fifoIndex + 1], dataLength - 1, &ax25Struct);

						//AX25 Filtering, except CRC (CRC is part of HDLC frame)
						if(AX25Filter(ax25Struct, uhfAX25FltStruct) == 0x00) {
							uint8_t dspInfo = 0;

							len += sprintf(&str[len], "DATA=", ax25Struct.destinationAddress);

							//Add Destination, Source, Control and PID only if not filtered on those!
							if(uhfAX25FltStruct.onDestinationAddress == 0x00) {
								len += sprintf(&str[len], "%s,", ax25Struct.destinationAddress);
								dspInfo = 1;
							}
							if(uhfAX25FltStruct.onSourceAddress == 0x00) {
								len += sprintf(&str[len], "%s,", ax25Struct.sourceAddress);
								dspInfo = 1;
							}
							if(uhfAX25FltStruct.onControlField == 0x00) {
								len += sprintf(&str[len], "%d,", ax25Struct.control);
								dspInfo = 1;
							}
							if(uhfAX25FltStruct.onPIDField == 0x00) {
								len += sprintf(&str[len], "%d,", ax25Struct.pid);
								dspInfo = 1;
							}

							//Check if any Info was added, to be displayed
							if(dspInfo == 0x00) {
								//No Info to display so reset len (string index counter)
								len = 0;
							}

							//Add payload, on new line
							len += sprintf(&str[len], "%d,", ax25Struct.payloadLength);

							uint8_t i;
							for(i = 0; i < ax25Struct.payloadLength; i++) {
								str[len++] = ax25Struct.payload[i];
							}

							len += sprintf(&str[len], "\n");

							USBVCPWrite(str, len);
						}
					}

					if(radio == RADIO_UHF) {
						GPIOWrite(GPIO_OUT_LED1, 1);
					}
					else if(radio == RADIO_VHF) {
						GPIOWrite(GPIO_OUT_LED3, 1);
					}

					fifoIndex += dataLength;

					break;
				}
				default: {
					break;
				}
			}
		}
	}
}
