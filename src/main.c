#include "gpio.h"
#include "rcc.h"
#include "spi.h"
#include "timer.h"
#include "uart.h"
#include "usb_vcp.h"

#include "ax25.h"
#include "morse.h"
#include "radio.h"

#include "radioStateMachine.h"

#include "CATInterface.h"
#include "radioCommands.h"

#include "atCmdInter.h"
#include "commandHandler.h"

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
//	PWM1Init();
//	PWM2Init();

	//Initialize Global Variables
	GlobalVariablesInit();

	//Initialize the VHF and UHF Radio Interfaces, set the SPI and CS
	RadioInterfacesInit();

	//Init VHF Radio, base/general configurations
	RadioVHFInit();
	RadioVHFEnterFMMode(93200000 + 50000);			//Comercial: 97400000; RFM: 93200000; Mega Hits: 92400000
	RadioSetOperationMode(RADIO_B, RadioMode_RX);

	//Config VHF Radio
	centerFrequencyB = 93200000 + 50000;			//Comercial: 97400000; RFM: 93200000; Mega Hits: 92400000
	modulationB = RadioModulation_FM;
	operationModeB = RadioMode_RX;
	frequencyDeviationB = 65000;
	bandwidthB = 100000;
	ifFrequencyB = 10000;
	rxDatarateB = 200000;
	txDatarateB = 200000;
	outputPowerB = 26;
	afcRangeB = 25000;
	agcSpeedB = 9;

	afskSpaceB = 2200;
	afskMarkB = 1200;

	encoderB = RadioEncoder_NRZI;
	framingB = RadioFraming_HDLC;
	crcB = RadioCRC_CCITT;

	RadioSetCenterFrequency(RADIO_B, centerFrequencyB);
	RadioSetModulation(RADIO_B, modulationB);
	RadioSetTXDeviation(RADIO_B, frequencyDeviationB);
	RadioSetBandwidth(RADIO_B, bandwidthB);
	RadioSetIF(RADIO_B, ifFrequencyB);
	RadioSetRXDatarate(RADIO_B, rxDatarateB);
	RadioSetTXDatarate(RADIO_B, txDatarateB);
	RadioSetAFSKSpaceFreq(RADIO_B, afskSpaceB);
	RadioSetAFSKMarkFreq(RADIO_B, afskMarkB);
	RadioSetTXPower(RADIO_B, outputPowerB);
	RadioSetAFCRange(RADIO_B, afcRangeB);
	RadioSetAGCSpeed(RADIO_B, agcSpeedB);
	RadioSetOperationMode(RADIO_B, operationModeB);

	RadioSetEncodingMode(RADIO_B, encoderB);
	RadioSetFramingMode(RADIO_B, framingB);
	RadioSetCRCMode(RADIO_B, crcB);

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
	RadioUHFInit();

	//Config UHF Radio
	centerFrequencyA = 436450000 + 4300;
	modulationA = RadioModulation_AFSK;
	operationModeA = RadioMode_RX;
	frequencyDeviationA = 3000;
	bandwidthA = 15000;
	ifFrequencyA = 7500;
	rxDatarateA = 1200;
	txDatarateA = 1200;
	outputPowerA = 26;
	afcRangeA = 3750;
	agcSpeedA = 7;

	afskSpaceA = 2200;
	afskMarkA = 1200;

	encoderA = RadioEncoder_NRZI;
	framingA = RadioFraming_HDLC;
	crcA = RadioCRC_CCITT;

	RadioSetCenterFrequency(RADIO_A, centerFrequencyA);
	RadioSetModulation(RADIO_A, modulationA);
	RadioSetTXDeviation(RADIO_A, frequencyDeviationA);
	RadioSetBandwidth(RADIO_A, bandwidthA);
	RadioSetIF(RADIO_A, ifFrequencyA);
	RadioSetRXDatarate(RADIO_A, rxDatarateA);
	RadioSetTXDatarate(RADIO_A, txDatarateA);
	RadioSetAFSKSpaceFreq(RADIO_A, afskSpaceA);
	RadioSetAFSKMarkFreq(RADIO_A, afskMarkA);
	RadioSetTXPower(RADIO_A, outputPowerA);
	RadioSetAFCRange(RADIO_A, afcRangeA);
	RadioSetAGCSpeed(RADIO_A, agcSpeedA);
	RadioSetOperationMode(RADIO_A, operationModeA);

	RadioSetEncodingMode(RADIO_A, encoderA);
	RadioSetFramingMode(RADIO_A, framingA);
	RadioSetCRCMode(RADIO_A, crcA);

//	RadioConfigStruct radioUHFConfig;
//	radioUHFConfig.frequency = 436450000 + 4300;
//	radioUHFConfig.datarate = 1200;
//	radioUHFConfig.afcRange = 2000;
//	radioUHFConfig.fskDeviation = 3000;
//	radioUHFConfig.modulation = AFSK;
//	RadioUHFModConfig(radioUHFConfig);
//	RadioUHFEnterFMMode(radioUHFConfig.frequency);

	//Start the Tracking/Status update Timer
	TIM3Init();

	//Initializations done, VUHFRadio Powered Up
	GPIOWrite(GPIO_OUT_LED5, 1);

	//Variables for USB/AT Commands
	uint8_t isVCPConnected = 0;
	uint8_t rxData[512];
	uint16_t rxLength;
	uint8_t txData[512];
	uint16_t txLength;
	uint8_t* framed;
	uint16_t framedLength;
	while(1) {
		//USB Communication Check
		if(USBVCPRead(rxData, &rxLength) == 0x01) {
			CATInterfaceHandler(rxData, rxLength, txData, &txLength);
			USBVCPWrite(txData, txLength);

			//Forward received command over USB to UART, to the Radio Interface Module
			UART1Write(rxData, rxLength);
		}

		//UART Communication Check
		if(UART1Read(rxData, &rxLength) == 0x01) {
			CATInterfaceHandler(rxData, rxLength, txData, &txLength);
			UART1Write(txData, txLength);
		}
	}

	//Send Test Frame
	uint8_t testData[200];
	uint8_t testDataLen = 0;
	testData[testDataLen++] = 'I' << 1;
	testData[testDataLen++] = 'S' << 1;
	testData[testDataLen++] = 'T' << 1;
	testData[testDataLen++] = 'S' << 1;
	testData[testDataLen++] = 'A' << 1;
	testData[testDataLen++] = 'T' << 1;
	testData[testDataLen++] = '1' << 1;
	testData[testDataLen++] = 'C' << 1;
	testData[testDataLen++] = 'S' << 1;
	testData[testDataLen++] = '5' << 1;
	testData[testDataLen++] = 'C' << 1;
	testData[testDataLen++] = 'E' << 1;
	testData[testDataLen++] = 'P' << 1;
	testData[testDataLen++] = ('1' << 1) | 0x01;
	testData[testDataLen++] = 0x03;
	testData[testDataLen++] = 0x00;
	testData[testDataLen++] = '0';
	testData[testDataLen++] = '1';
	testData[testDataLen++] = '2';
	testData[testDataLen++] = '3';
	testData[testDataLen++] = '4';
	testData[testDataLen++] = '5';
	testData[testDataLen++] = '6';
	testData[testDataLen++] = '7';
	testData[testDataLen++] = '8';
	testData[testDataLen++] = '9';
	testData[testDataLen++] = '\n';

	//Random generator
	uint8_t i;
	for(i = 0; i < 200; i++) {
		testData[i] = rand();
	}
	testDataLen = i;

	RadioState radioState = AX5043GeneralRadioState(RADIO_VHF);
	PwrModeSelection pwrMode = AX5043PwrGetPowerMode(RADIO_VHF);
	RadioVHFEnterTX();
	while(1) {
		RadioVHFEnterTX();
		RadioVHFWritePreamble(0x55, 20);
		RadioVHFWriteFrame(testData, testDataLen);
		AX5043FIFOSetFIFOStatCommand(RADIO_VHF, FIFOStat_Commit);

		do {
			radioState = AX5043GeneralRadioState(RADIO_VHF);

			if(radioState == RadioState_TX || radioState == RadioState_TXTail) {
				GPIOWrite(GPIO_OUT_LED0, 1);
			}
			else {
				GPIOWrite(GPIO_OUT_LED0, 0);
			}

		} while(radioState != RadioState_Idle);

		AX5043PwrSetPowerMode(RADIO_VHF, PwrMode_Powerdown);

//		Delay(1000);
	}
}

void Error_Handler(void) {

}
