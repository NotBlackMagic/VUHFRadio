#include "adc.h"
#include "gpio.h"
#include "rcc.h"
#include "spi.h"
#include "timer.h"
#include "uart.h"
#include "usb_vcp.h"

#include "ax25.h"
#include "tnc.h"
#include "morse.h"
#include "radio.h"

#include "radioStateMachine.h"

#include "CATInterface.h"
#include "radioCommands.h"
#include "memoryChannelConfigs.h"

#include "ax5043_experimental.h"

uint8_t RadioWritePacket(uint8_t radio, uint8_t data[], uint8_t dataLength);

int main(void) {
	//Configure the system clock
 	SystemClockInit();
	SystemTickInit();

	//Initialize all configured peripherals
	GPIOInit();
	UART1Init(115200);
	USBVCPInit();
	ADC1Init();
	SPI1Init();
	SPI2Init();
//	PWM1Init();		//DCLK for Radio B, VHF
//	PWM2Init();		//DCLK for Radio A, UHF

	//Initialize the VHF and UHF Radio Interfaces, set the SPI and CS
	RadioInterfacesInit();

//	//Reset Radio
//	AX5043PwrReset(RADIO_A);
//
//	uint8_t data[10];
//	data[0] = 0x04;
//	AX5043WriteLongAddress(RADIO_A, 0xF10, data, 1);
//	data[0] = 0x00;
//	AX5043WriteLongAddress(RADIO_A, 0xF11, data, 1);
//	data[0] = 0x10;
//	AX5043WriteLongAddress(RADIO_A, 0xF35, data, 1);
//	data[0] = 0x28;
//	AX5043WriteLongAddress(RADIO_A, 0xF34, data, 1);
//	data[0] = 0x04;
//	AX5043WriteShortAddress(RADIO_A, 0x032, data, 1);
//
////	RadioSetCenterFrequency(RADIO_A, 450000000);
//
//	uint32_t N = (uint32_t)((float)400000000/16000000*(1<<24));
//	data[0] = (N>>24)&0xFF;
//	AX5043WriteShortAddress(RADIO_A, 0x034, data, 1);
//	data[0] = (N>>16)&0xFF;
//	AX5043WriteShortAddress(RADIO_A, 0x035, data, 1);
//	data[0] = (N>>8)&0xFF;
//	AX5043WriteShortAddress(RADIO_A, 0x036, data, 1);
//	data[0] = N&0xFF;
//	AX5043WriteShortAddress(RADIO_A, 0x037, data, 1);
//
//	data[0] = 0x10;
//	AX5043WriteShortAddress(RADIO_A, 0x033, data, 1);
//
//	uint8_t rcv=0;
//	do {
//		AX5043ReadShortAddress(RADIO_A, 0x33, &rcv, 1);
//	} while(rcv&(1<<4));
//
//	volatile uint8_t pllvcodiv;
//	AX5043ReadShortAddress(RADIO_A, 0x33, &pllvcodiv, 1);
//
//	volatile uint8_t rangeError = AX5043SynthGetAutoRangingErrorA(RADIO_A);
//	volatile uint8_t pllRange = AX5043SynthGetVCORangeA(RADIO_A);

	//PLL Range Values
	//400MHz - 14
	//410MHz - 12
	//420MHz - 11
	//430MHz - 10
	//440MHz - 09
	//450MHz - 08

	//Init VHF Radio, base/general configurations
	RadioInitBaseConfiguration(RADIO_B);
//	RadioVHFInit();

	//Config VHF Radio
	radioBBaseConfigs.radio = RADIO_B;
	radioBBaseConfigs.radioXTAL = RADIO_XTAL;
	radioBBaseConfigs.radioCenterFrequencyMin = RADIO_B_FREQ_MIN;
	radioBBaseConfigs.radioCenterFrequencyMax = RADIO_B_FREQ_MAX;
	radioBBaseConfigs.radioRSSIOffset = -11;
//	radioBConfig.centerFrequency = 93200000 + 50000;			//Comercial: 97400000; RFM: 93200000; Mega Hits: 92400000
//	radioBConfig.modulation = RadioModulation_FM;
//	radioBConfig.operationMode = RadioMode_RX;
//	radioBConfig.frequencyDeviation = 65000;
//	radioBConfig.bandwidth = 100000;
//	radioBConfig.ifFrequency = 10000;
//	radioBConfig.rxDatarate = 200000;
//	radioBConfig.txDatarate = 200000;
//	radioBConfig.outputPower = 16;
//	radioBConfig.afcRange = 25000;
//	radioBConfig.agcSpeed = 9;
//
//	radioBConfig.afskSpace = 2200;
//	radioBConfig.afskMark = 1200;
//
//	radioBConfig.tncMode = RadioTNCMode_OFF;
//	radioBConfig.encoder = RadioEncoder_NRZI;
//	radioBConfig.framing = RadioFraming_HDLC;
//	radioBConfig.crc = RadioCRC_CCITT;
//	radioBConfig.preambleSymbol = 0x55;
//	radioBConfig.preambleLength = 20;

//	RadioSetCenterFrequency(RADIO_B, 145895000);
//	volatile uint8_t rangeError = AX5043SynthGetAutoRangingErrorA(RADIO_B);
//	volatile uint8_t pllRange = AX5043SynthGetVCORangeA(RADIO_B);
	radioBConfig = memoryChannelsFixed[Memory_AFSK_1200];
	radioBConfig.centerFrequency = 145895000;

	//QPSK Test Config
//	radioBConfig.centerFrequency = 145895000;
//	radioBConfig.modulation = RadioModulation_QPSK;
//	radioBConfig.operationMode = RadioMode_RX;
//	radioBConfig.frequencyDeviation = 4800;
//	radioBConfig.bandwidth = 19200;
//	radioBConfig.ifFrequency = 9600;
//	radioBConfig.rxDatarate = 19200;
//	radioBConfig.txDatarate = 19200;
//	radioBConfig.outputPower = 16;
//	radioBConfig.afcRange = 4800;
//	radioBConfig.agcSpeed = 4;
//
//	radioBConfig.afskSpace = 2200;
//	radioBConfig.afskMark = 1200;
//
//	radioBConfig.tncMode = RadioTNCMode_KISS;
//	radioBConfig.encoder = RadioEncoder_NRZ;
//	radioBConfig.framing = RadioFraming_HDLC;
//	radioBConfig.crc = RadioCRC_CCITT;
//	radioBConfig.preambleSymbol = 0xAA;
//	radioBConfig.preambleLength = 200;

	RadioSetFullConfiguration(RADIO_B, radioBConfig);
//	AX5043PacketSetAcceptPacketsCRCFailed(RADIO_B, 1);

//	RadioSetCenterFrequency(RADIO_B, radioBConfig.centerFrequency);
//	RadioSetModulation(RADIO_B, radioBConfig.modulation);
//	RadioSetTXDeviation(RADIO_B, radioBConfig.frequencyDeviation);
//	RadioSetBandwidth(RADIO_B, radioBConfig.bandwidth);
//	RadioSetIF(RADIO_B, radioBConfig.ifFrequency);
//	RadioSetRXDatarate(RADIO_B, radioBConfig.rxDatarate);
//	RadioSetTXDatarate(RADIO_B, radioBConfig.txDatarate);
//	RadioSetTXPower(RADIO_B, radioBConfig.outputPower);
//	RadioSetAFCRange(RADIO_B, radioBConfig.afcRange);
//	RadioSetAGCSpeed(RADIO_B, radioBConfig.agcSpeed);
//	RadioSetOperationMode(RADIO_B, radioBConfig.operationMode);
//	RadioSetAFSKSpaceFreq(RADIO_B, radioBConfig.afskSpace);			//Have to be done AFTER operation mode is set, depends on operationMode
//	RadioSetAFSKMarkFreq(RADIO_B, radioBConfig.afskMark);
//
//	RadioSetEncodingMode(RADIO_B, radioBConfig.encoder);
//	RadioSetFramingMode(RADIO_B, radioBConfig.framing);
//	RadioSetCRCMode(RADIO_B, radioBConfig.crc);

//	RadioConfigStruct radioVHFConfig;
//	radioVHFConfig.frequency = 119100000;	//145895000 + 1500;
//	radioVHFConfig.datarate = 9600;
//	radioVHFConfig.afcRange = 2000;
//	radioVHFConfig.fskDeviation = 4800;
//	radioVHFConfig.modulation = FSK;
//	RadioVHFModConfig(radioVHFConfig);
//	RadioVHFEnterFMMode(93200000 + 50000);			//Comercial: 97400000; RFM: 93200000; Mega Hits: 92400000
//	RadioVHFEnterAMMode(119160000 - 4000);

	//Init UHF Radio, base/general configurations
	RadioInitBaseConfiguration(RADIO_A);
//	RadioUHFInit();

	//Config UHF Radio
	radioABaseConfigs.radio = RADIO_A;
	radioABaseConfigs.radioXTAL = RADIO_XTAL;
	radioABaseConfigs.radioCenterFrequencyMin = RADIO_A_FREQ_MIN;
	radioABaseConfigs.radioCenterFrequencyMax = RADIO_A_FREQ_MAX;

//	radioAConfig.operationMode = RadioMode_RX;
//	radioAConfig.centerFrequency = 436450000 + 4300;
//	radioAConfig.modulation = RadioModulation_BPSK;
//	radioAConfig.frequencyDeviation = 2400;
//	radioAConfig.bandwidth = 19200;
//	radioAConfig.ifFrequency = 9600;
//	radioAConfig.rxDatarate = 2400;
//	radioAConfig.txDatarate = 2400;
//	radioAConfig.outputPower = 16;
//	radioAConfig.afcRange = 4800;
//	radioAConfig.agcSpeed = 6;
//
//	radioAConfig.afskSpace = 2200;
//	radioAConfig.afskMark = 1200;
//
//	radioAConfig.tncMode = RadioTNCMode_KISS;
//	radioAConfig.encoder = RadioEncoder_NRZI_S;
//	radioAConfig.framing = RadioFraming_HDLC;
//	radioAConfig.crc = RadioCRC_CCITT;
//	radioAConfig.preambleSymbol = 0x55;
//	radioAConfig.preambleLength = 20;

//	RadioSetCenterFrequency(RADIO_A, 436450000);
	radioAConfig = memoryChannelsFixed[Memory_AFSK_1200];
	radioAConfig.centerFrequency = 436450000;
	RadioSetFullConfiguration(RADIO_A, radioAConfig);

//	RadioSetBandwidth(RADIO_A, 70000);

//	RadioSetCenterFrequency(RADIO_A, radioAConfig.centerFrequency);
//	RadioSetModulation(RADIO_A, radioAConfig.modulation);
//	RadioSetTXDeviation(RADIO_A, radioAConfig.frequencyDeviation);
//	RadioSetBandwidth(RADIO_A, radioAConfig.bandwidth);
//	RadioSetIF(RADIO_A, radioAConfig.ifFrequency);
//	RadioSetRXDatarate(RADIO_A, radioAConfig.rxDatarate);
//	RadioSetTXDatarate(RADIO_A, radioAConfig.txDatarate);
//	RadioSetAFSKSpaceFreq(RADIO_A, radioAConfig.afskSpace);
//	RadioSetAFSKMarkFreq(RADIO_A, radioAConfig.afskMark);
//	RadioSetTXPower(RADIO_A, radioAConfig.outputPower);
//	RadioSetAFCRange(RADIO_A, radioAConfig.afcRange);
//	RadioSetAGCSpeed(RADIO_A, radioAConfig.agcSpeed);
//	RadioSetOperationMode(RADIO_A, radioAConfig.operationMode);
//	RadioSetAFSKSpaceFreq(RADIO_A, radioAConfig.afskSpace);			//Have to be done AFTER operation mode is set, depends on operationMode
//	RadioSetAFSKMarkFreq(RADIO_A, radioAConfig.afskMark);
//
//	RadioSetEncodingMode(RADIO_A, radioAConfig.encoder);
//	RadioSetFramingMode(RADIO_A, radioAConfig.framing);
//	RadioSetCRCMode(RADIO_A, radioAConfig.crc);

//	RadioConfigStruct radioUHFConfig;
//	radioUHFConfig.frequency = 436450000 + 4300;
//	radioUHFConfig.datarate = 1200;
//	radioUHFConfig.afcRange = 2000;
//	radioUHFConfig.fskDeviation = 3000;
//	radioUHFConfig.modulation = AFSK;
//	RadioUHFModConfig(radioUHFConfig);
//	RadioUHFEnterFMMode(radioUHFConfig.frequency);

//	//Analog IQ Mode
//	uint8_t reg = 0;
//	//Config TMMUX
//	reg = GPADCSource_5;
//	AX5043WriteLongAddress(RADIO_A, TMMUX, &reg, 1);
//	//Config BBDETECTOR
//	reg = 0x08;
//	AX5043WriteLongAddress(RADIO_A, BBDETECTOR0, &reg, 1);
//
//	//DSPMode
//	#define DSPMODEFCG						0x0320	//DSPmode Configuration
//	#define DSPMODESKIP1					0x0321	//DSPmode Receive Data 1
//	#define DSPMODESKIP0					0x0322	//DSPmode Receive Data 0
//
//	//DSPMode Interface Pins:
//	//SYSCLK -> Bit Clock
//	//DCLK -> Frame Sync
//	//DATA -> Receive Data
//	//PWRAMP -> Transmit Data
//
//	//Config DCLK
//	reg = 0x06;		//DSPmode Frame Sync
//	AX5043WriteShortAddress(RADIO_A, PINFUNCDCLK, &reg, 1);
//	//Config DATA
//	reg = 0x86;		//DSPmode Receiver Data, weak pullup enabled
//	AX5043WriteShortAddress(RADIO_A, PINFUNCDATA, &reg, 1);
//	//Config SYS
//	reg = SysClk_fXtal_div1;		//Output fXtal/16 = 16MHz/16 = 1MHz
//	AX5043WriteShortAddress(RADIO_A, PINFUNCSYSCLK, &reg, 1);
//
//	AX5043RXParamSetRXFrequencyGainA0(RADIO_A, 0x0F);
//	AX5043RXParamSetRXFrequencyGainB0(RADIO_A, 0x1F);
//	AX5043RXParamSetRXFrequencyGainC0(RADIO_A, 0x1F);
//	AX5043RXParamSetRXFrequencyGainD0(RADIO_A, 0x1F);
//
//	AX5043PacketSetGainTimingRecovery0(RADIO_A, 0x00, 0x00);
//	AX5043PacketSetGainTimingRecovery1(RADIO_A, 0x00, 0x00);
//	AX5043PacketSetGainTimingRecovery2(RADIO_A, 0x00, 0x00);
//	AX5043PacketSetGainTimingRecovery3(RADIO_A, 0x00, 0x00);
//
//	//Config DSP Mode
//	AX5043ExperimentalEnableFSYNCDelay(RADIO_A, 0);
//	AX5043ExperimentalSetSyncSource(RADIO_A, SyncSource_Baseband_Clock);
//	DSPModeSkip skipData;
//	skipData.raw = 0xFFFF;
//	skipData.skipbasebandiq = 0;
//	AX5043ExperimentalSetDSPModeSkipData(RADIO_A, skipData);
//
//	while(1);

	//Start the Tracking/Status update Timer
	uint32_t trackingUpdateTimer = GetSysTick();
//	TIM3Init();

	//Initializations done, VUHFRadio Powered Up
	GPIOWrite(GPIO_OUT_LED5, 1);

	//Variables for USB/AT Commands
	uint8_t rxData[512];
	uint16_t rxLength;
	uint8_t txData[512];
	uint16_t txLength;
	while(1) {
		//USB Communication Check
		if(USBVCPRead(rxData, &rxLength) == 0x01) {
			//Check if is a KISS packet/frame/command, always start with FEND (0xC0)
			if(rxData[0] == FEND) {
				//This is a KISS packet
				KissCmd kissCmd = rxData[1] & KISS_COMMAND_MASK;		//Extract the Command bits
				uint8_t kissPort = (rxData[1] & KISS_PORT_MASK) >> 4;	//Extract the Port bits

				if(kissCmd == DataFrame) {
					//This is a KISS data frame
					uint8_t txRadioDataLength = 0;
					uint8_t txRadioData[255];

					//Extract the KISS Frame to send over Radio
					uint8_t i = 2;
					while(i < rxLength) {
						if(rxData[i] == FEND) {
							//Frame end
							break;
						}
						txRadioData[txRadioDataLength++] = rxData[i++];
					}

					if(kissPort == RADIO_A && radioAConfig.tncMode == RadioTNCMode_KISS) {
						//Send Frame over radio
						RadioWritePacket(RADIO_A, txRadioData, txRadioDataLength);
					}
					else if(kissPort == RADIO_B && radioBConfig.tncMode == RadioTNCMode_KISS) {
						//Send Frame over radio
						RadioWritePacket(RADIO_B, txRadioData, txRadioDataLength);
					}
				}
			}
			else {
				//Not a KISS packet so check as CAT command
				CATInterfaceHandler(rxData, rxLength, txData, &txLength);
				USBVCPWrite(txData, txLength);

				//Forward received command over USB to UART, to the Radio Interface Module
				UART1Write(rxData, rxLength);
			}
		}

		//UART Communication Check
		if(UART1Read(rxData, &rxLength) == 0x01) {
			//Check if is a KISS packet/frame/command, always start with FEND (0xC0)
			if(rxData[0] == FEND) {
				//This is a KISS packet
				KissCmd kissCmd = rxData[1] & KISS_COMMAND_MASK;		//Extract the Command bits
				uint8_t kissPort = (rxData[1] & KISS_PORT_MASK) >> 4;	//Extract the Port bits

				if(kissCmd == DataFrame) {
					//This is a KISS data frame
					uint8_t txRadioDataLength = 0;
					uint8_t txRadioData[255];

					//Extract the KISS Frame to send over Radio
					uint8_t i = 2;
					while(i < rxLength) {
						if(rxData[i] == FEND) {
							//Frame end
							break;
						}
						txRadioData[txRadioDataLength++] = rxData[i++];
					}

					if(kissPort == RADIO_A && radioAConfig.tncMode == RadioTNCMode_KISS) {
						txRadioDataLength = 0;
						txRadioData[txRadioDataLength++] = 'N' << 1;
						txRadioData[txRadioDataLength++] = 'B' << 1;
						txRadioData[txRadioDataLength++] = 'M' << 1;
						txRadioData[txRadioDataLength++] = 'W' << 1;
						txRadioData[txRadioDataLength++] = 'I' << 1;
						txRadioData[txRadioDataLength++] = 'N' << 1;
						txRadioData[txRadioDataLength++] = '1' << 1;

						txRadioData[txRadioDataLength++] = 'V' << 1;
						txRadioData[txRadioDataLength++] = 'U' << 1;
						txRadioData[txRadioDataLength++] = 'H' << 1;
						txRadioData[txRadioDataLength++] = 'F' << 1;
						txRadioData[txRadioDataLength++] = 'T' << 1;
						txRadioData[txRadioDataLength++] = 'X' << 1;
						txRadioData[txRadioDataLength++] = ('1' << 1) | 0x01;

						txRadioData[txRadioDataLength++] = 0x03;
						txRadioData[txRadioDataLength++] = 0x00;
						txRadioData[txRadioDataLength++] = 'T';
						txRadioData[txRadioDataLength++] = 'H';
						txRadioData[txRadioDataLength++] = 'E';
						txRadioData[txRadioDataLength++] = ' ';
						txRadioData[txRadioDataLength++] = 'Q';
						txRadioData[txRadioDataLength++] = 'I';
						txRadioData[txRadioDataLength++] = 'C';
						txRadioData[txRadioDataLength++] = 'K';
						txRadioData[txRadioDataLength++] = ' ';
						txRadioData[txRadioDataLength++] = 'B';
						txRadioData[txRadioDataLength++] = 'R';
						txRadioData[txRadioDataLength++] = 'O';
						txRadioData[txRadioDataLength++] = 'W';
						txRadioData[txRadioDataLength++] = 'N';
						txRadioData[txRadioDataLength++] = ' ';
						txRadioData[txRadioDataLength++] = 'F';
						txRadioData[txRadioDataLength++] = 'O';
						txRadioData[txRadioDataLength++] = 'X';
						txRadioData[txRadioDataLength++] = ' ';
						txRadioData[txRadioDataLength++] = 'J';
						txRadioData[txRadioDataLength++] = 'U';
						txRadioData[txRadioDataLength++] = 'M';
						txRadioData[txRadioDataLength++] = 'P';
						txRadioData[txRadioDataLength++] = 'S';
						txRadioData[txRadioDataLength++] = ' ';
						txRadioData[txRadioDataLength++] = 'O';
						txRadioData[txRadioDataLength++] = 'V';
						txRadioData[txRadioDataLength++] = 'E';
						txRadioData[txRadioDataLength++] = 'R';
						txRadioData[txRadioDataLength++] = ' ';
						txRadioData[txRadioDataLength++] = 'T';
						txRadioData[txRadioDataLength++] = 'H';
						txRadioData[txRadioDataLength++] = 'E';
						txRadioData[txRadioDataLength++] = ' ';
						txRadioData[txRadioDataLength++] = 'L';
						txRadioData[txRadioDataLength++] = 'A';
						txRadioData[txRadioDataLength++] = 'Z';
						txRadioData[txRadioDataLength++] = 'Y';
						txRadioData[txRadioDataLength++] = ' ';
						txRadioData[txRadioDataLength++] = 'D';
						txRadioData[txRadioDataLength++] = 'O';
						txRadioData[txRadioDataLength++] = 'G';

						//Send Frame over radio
						RadioWritePacket(RADIO_A, txRadioData, txRadioDataLength);
					}
					else if(kissPort == RADIO_B && radioBConfig.tncMode == RadioTNCMode_KISS) {
						txRadioDataLength = 0;
						txRadioData[txRadioDataLength++] = 'N' << 1;
						txRadioData[txRadioDataLength++] = 'B' << 1;
						txRadioData[txRadioDataLength++] = 'M' << 1;
						txRadioData[txRadioDataLength++] = 'W' << 1;
						txRadioData[txRadioDataLength++] = 'I' << 1;
						txRadioData[txRadioDataLength++] = 'N' << 1;
						txRadioData[txRadioDataLength++] = '1' << 1;

						txRadioData[txRadioDataLength++] = 'V' << 1;
						txRadioData[txRadioDataLength++] = 'U' << 1;
						txRadioData[txRadioDataLength++] = 'H' << 1;
						txRadioData[txRadioDataLength++] = 'F' << 1;
						txRadioData[txRadioDataLength++] = 'T' << 1;
						txRadioData[txRadioDataLength++] = 'X' << 1;
						txRadioData[txRadioDataLength++] = ('1' << 1) | 0x01;

						txRadioData[txRadioDataLength++] = 0x03;
						txRadioData[txRadioDataLength++] = 0x00;
						txRadioData[txRadioDataLength++] = 'T';
						txRadioData[txRadioDataLength++] = 'H';
						txRadioData[txRadioDataLength++] = 'E';
						txRadioData[txRadioDataLength++] = ' ';
						txRadioData[txRadioDataLength++] = 'Q';
						txRadioData[txRadioDataLength++] = 'I';
						txRadioData[txRadioDataLength++] = 'C';
						txRadioData[txRadioDataLength++] = 'K';
						txRadioData[txRadioDataLength++] = ' ';
						txRadioData[txRadioDataLength++] = 'B';
						txRadioData[txRadioDataLength++] = 'R';
						txRadioData[txRadioDataLength++] = 'O';
						txRadioData[txRadioDataLength++] = 'W';
						txRadioData[txRadioDataLength++] = 'N';
						txRadioData[txRadioDataLength++] = ' ';
						txRadioData[txRadioDataLength++] = 'F';
						txRadioData[txRadioDataLength++] = 'O';
						txRadioData[txRadioDataLength++] = 'X';
						txRadioData[txRadioDataLength++] = ' ';
						txRadioData[txRadioDataLength++] = 'J';
						txRadioData[txRadioDataLength++] = 'U';
						txRadioData[txRadioDataLength++] = 'M';
						txRadioData[txRadioDataLength++] = 'P';
						txRadioData[txRadioDataLength++] = 'S';
						txRadioData[txRadioDataLength++] = ' ';
						txRadioData[txRadioDataLength++] = 'O';
						txRadioData[txRadioDataLength++] = 'V';
						txRadioData[txRadioDataLength++] = 'E';
						txRadioData[txRadioDataLength++] = 'R';
						txRadioData[txRadioDataLength++] = ' ';
						txRadioData[txRadioDataLength++] = 'T';
						txRadioData[txRadioDataLength++] = 'H';
						txRadioData[txRadioDataLength++] = 'E';
						txRadioData[txRadioDataLength++] = ' ';
						txRadioData[txRadioDataLength++] = 'L';
						txRadioData[txRadioDataLength++] = 'A';
						txRadioData[txRadioDataLength++] = 'Z';
						txRadioData[txRadioDataLength++] = 'Y';
						txRadioData[txRadioDataLength++] = ' ';
						txRadioData[txRadioDataLength++] = 'D';
						txRadioData[txRadioDataLength++] = 'O';
						txRadioData[txRadioDataLength++] = 'G';

						//Send Frame over radio
						RadioWritePacket(RADIO_B, txRadioData, txRadioDataLength);
					}
				}
			}
			else {
				//Not a KISS packet so check as CAT command
				CATInterfaceHandler(rxData, rxLength, txData, &txLength);
				UART1Write(txData, txLength);
			}
		}

		if(radioAConfig.tncMode == RadioTNCMode_KISS && newFIFODataPacketA == 0x01) {
			if(radioAConfig.framing == RadioFraming_HDLC) {
				//In HDLC mode the CRC is appended at the end of the data frame, remove that
				fifoDataPacketLengthA -= 2;
			}

			uint8_t len = 0;
			char str[255];
			str[len++] = FEND;
			str[len++] = ((RADIO_A << 4) & KISS_PORT_MASK) + (DataFrame & KISS_COMMAND_MASK);

			uint8_t i;
			for(i = 0; i < fifoDataPacketLengthA; i++) {
				str[len++] = fifoDataPacketA[i];
			}

			str[len++] = FEND;

			USBVCPWrite(str, len);
			UART1Write(str, len);

			newFIFODataPacketA = 0x00;
		}

		if(radioBConfig.tncMode == RadioTNCMode_KISS && newFIFODataPacketB == 0x01) {
			if(radioBConfig.framing == RadioFraming_HDLC) {
				//In HDLC mode the CRC is appended at the end of the data frame, remove that
				fifoDataPacketLengthB -= 2;
			}

			uint8_t len = 0;
			char str[255];
			str[len++] = FEND;
			str[len++] = ((RADIO_B << 4) & KISS_PORT_MASK) + (DataFrame & KISS_COMMAND_MASK);

			uint8_t i;
			for(i = 0; i < fifoDataPacketLengthB; i++) {
				str[len++] = fifoDataPacketB[i];
			}

			str[len++] = FEND;

			USBVCPWrite(str, len);
			UART1Write(str, len);

			newFIFODataPacketB = 0x00;
		}

		//Radio Tracking Update every ~20ms (50 Hz)
		if((trackingUpdateTimer + 20) < GetSysTick()) {
			RadioTrackingUpdateHandler();

			trackingUpdateTimer = GetSysTick();
		}

	}
}

/**
  * @brief	This function sends packet, handles all settings and transitions
  * @param	radio: Selects the Radio
  * @param	data: The Packet to be sent
  * @param	dataLength: Length of the Packet to be sent
  * @return	0-> Success, 1-> Failed/Error
  */
uint8_t RadioWritePacket(uint8_t radio, uint8_t data[], uint8_t dataLength) {
	//Send Frame over radio
	//First: Disable "FIFO Empty" Interrupt
	IrqMask irqMask;
	irqMask.raw = 0x0000;
	irqMask.irqmfifonotempty = 1;
	AX5043IrqDisableIRQs(radio, irqMask);

	//Second: Clear FIFO and enter TX Mode
	AX5043FIFOSetFIFOStatCommand(radio, FIFOStat_ClearFIFO);		//FIFO has to be empty to switch to "Standby" mode, intermediate mode needed to switch from RX to TX mode
	RadioSetOperationMode(radio, RadioMode_TX);
	if(radio == RADIO_A && radioAConfig.modulation == RadioModulation_AFSK) {
		RadioSetAFSKSpaceFreq(RADIO_A, radioAConfig.afskSpace);
		RadioSetAFSKMarkFreq(RADIO_A, radioAConfig.afskMark);
	}
	else if(radio == RADIO_B && radioBConfig.modulation == RadioModulation_AFSK) {
		RadioSetAFSKSpaceFreq(RADIO_B, radioBConfig.afskSpace);
		RadioSetAFSKMarkFreq(RADIO_B, radioBConfig.afskMark);
	}

	//Third: Send Data to Radio FIFO
	if(radio == RADIO_A) {
		if(RadioWriteFIFORepeatData(RADIO_A, radioAConfig.preambleSymbol, radioAConfig.preambleLength) != 0x00) {
			//Error writing the preamble to the FIFO
			return 0x01;
		}
	}
	else if(radio == RADIO_B) {
		if(RadioWriteFIFORepeatData(RADIO_B, radioBConfig.preambleSymbol, radioBConfig.preambleLength) != 0x00) {
			//Error writing the preamble to the FIFO
			return 0x01;
		}
	}
	if(RadioWriteFIFOData(radio, data, dataLength) != 0x00) {
		//Error writing the Packet to the FIFO
		return 0x01;
	}

	//Forth: Commit FIFO Data, this actually sends the frame
	AX5043FIFOSetFIFOStatCommand(radio, FIFOStat_Commit);

	//Fifth: Wait for Transmission Complete
	RadioState radioState;
	do {
		radioState = AX5043GeneralRadioState(radio);
		if(radioState == RadioState_TX || radioState == RadioState_TXTail) {
			GPIOWrite(GPIO_OUT_LED0, 1);
		}
		else {
			GPIOWrite(GPIO_OUT_LED0, 0);
		}
		Delay(5);
	} while(radioState != RadioState_Idle);

	//Sixth: Switch back to RX Mode
	AX5043FIFOSetFIFOStatCommand(radio, FIFOStat_ClearFIFO);		//FIFO has to be empty to switch to "Standby" mode, intermediate mode needed to switch from TX to RX mode
	RadioSetOperationMode(radio, RadioMode_RX);
	if(radio == RADIO_A && radioAConfig.modulation == RadioModulation_AFSK) {
		RadioSetAFSKSpaceFreq(RADIO_A, radioAConfig.afskSpace);
		RadioSetAFSKMarkFreq(RADIO_A, radioAConfig.afskMark);
	}
	else if(radio == RADIO_B && radioBConfig.modulation == RadioModulation_AFSK) {
		RadioSetAFSKSpaceFreq(RADIO_B, radioBConfig.afskSpace);
		RadioSetAFSKMarkFreq(RADIO_B, radioBConfig.afskMark);
	}

	//Seventh: Re-enable "FIFO Empty" Interrupt
	AX5043IrqEnableIRQs(radio, irqMask);

	return 0;
}

void Error_Handler(void) {

}
