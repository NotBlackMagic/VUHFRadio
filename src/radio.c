#include "radio.h"

#define FXTAL						16000000	//Xtal Frequency in Hz

void RadioUHFCS(uint8_t cs) {
	GPIOWrite(GPIO_OUT_CS_U, cs);
}

void RadioVHFCS(uint8_t cs) {
	GPIOWrite(GPIO_OUT_CS_V, cs);
}

void RadioInterfacesInit() {
	//Initialize Radio Interfaces
	AX5043InterfaceStruct radioInterfaces[2];
	radioInterfaces[RADIO_UHF].SPICS = RadioUHFCS;
	radioInterfaces[RADIO_UHF].SPIReadWrite = SPI1ReadWrite;
	radioInterfaces[RADIO_VHF].SPICS = RadioVHFCS;
	radioInterfaces[RADIO_VHF].SPIReadWrite = SPI2ReadWrite;
	AX5043InterfacesInit(radioInterfaces, 2);
}

void RadioVHFInit() {
	//Reset Radio
	AX5043PwrReset(RADIO_VHF);

	//Power Down
	AX5043PwrSetPowerMode(RADIO_VHF, PwrMode_Powerdown);

	//Set GPIOs
	AX5043GPIOCnfgSysClk(RADIO_VHF, SysClk_Low, 0);
	AX5043GPIOCnfgDCLK(RADIO_VHF, DCLK_Low, 0, 0);
	AX5043GPIOCnfgDATA(RADIO_VHF, DATA_Low, 0, 0);
	//AX5043GPIOCnfgIRQ(RADIO_VHF, IRQ_Int_Req, 0, 0);		//Default
	AX5043GPIOCnfgAntSel(RADIO_VHF, AntSel_Low, 0, 0);
	//AX5043GPIOCnfgPwrRamp(RADIO_VHF, PwrRamp_Low, 0, 0);	//Default

	//Set Performance Tuning Registers
	uint8_t data = 0x0F;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE0, &data, 1);
	//AX5043WriteLongAddress(RADIO_VHF, PERFTUNE12, 0x00, 1);
	data = 0x03;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE13, &data, 1);
	data = 0x04;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE16, &data, 1);
	data = 0x00;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE17, &data, 1);
	data = 0x06;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE24, &data, 1);
	data = 0x07;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE28, &data, 1);
	data = 0x5C;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE33, &data, 1);
	data = 0x53;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE34, &data, 1);
	data = 0x76;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE35, &data, 1);
	data = 0x92;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE38, &data, 1);
	data = 0x3F;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE48, &data, 1);
	data = 0xF0;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE49, &data, 1);
	data = 0x3F;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE50, &data, 1);
	data = 0xF0;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE51, &data, 1);
	data = 0x08;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE52, &data, 1);
	data = 0x10;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE53, &data, 1);
	data = 0x24;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE68, &data, 1);
	data = 0x00;
	AX5043WriteLongAddress(RADIO_VHF, PERFTUNE114, &data, 1);

	//Set Synth
	AX5043SynthSetPLLLoopFilter(RADIO_VHF, PLLLoop_Filter500kHz);
	AX5043SynthSetPLLChargePumpCurrent(RADIO_VHF, 0x10);
	AX5043SynthSetPLLVCOSelection(RADIO_VHF, 1);	//Use VCO 2 with external inductor
	AX5043SynthSetPLLVCO2Internal(RADIO_VHF, 1);	//Use VCO 2 with external inductor
//	AX5043SynthSetPLLRefDivider(RADIO_VHF, PllCodiv_fXtal_div1);	//Set refrence divider
	AX5043SynthSetFrequencyA(RADIO_VHF, 0x091E51EC);
//	AX5043SynthSetFrequencyB(RADIO_VHF, 0x08B22E58);

	//Perform auto ranging
	AX5043SynthStartAutoRangingA(RADIO_VHF);
	while(AX5043SynthGetAutoRangingA(RADIO_VHF));	//Wait for Auto Ranging Complete
//	AX5043SynthStartAutoRangingB(RADIO_VHF);
//	while(AX5043SynthGetAutoRangingB(RADIO_VHF));	//Wait for Auto Ranging Complete

	//Set PLL/VCO Parameters
	//AX5043PLLParamSetVCOBias(RADIO_VHF, 0x07);
	//AX5043PLLParamIsManualVCOIEnabled(RADIO_VHF);
	//AX5043PLLParamSetLockDetectDelay(RADIO_VHF, 0x03);	//Default
	//AX5043PLLParamSetPLLRangingClock(RADIO_VHF, PLLRangingClock_11);	//Default

	//Set Modulation
	AX5043GeneralSetModulation(RADIO_VHF, AFSK);
	AX5043TXParamSetTXDatarate(RADIO_VHF, 0x04EB);	//Set datarate to 1200 bits/s
	AX5043TXParamSetFSKFrequencyDeviation(RADIO_VHF, 0x0A8E); //Set FSK deviation to 3000 Hz
	AX5043RXParamSetAFSKSpaceFrequency(RADIO_VHF, 0x14);	//Set AFSK Space freq. of 1200 Hz
	AX5043RXParamSetAFSKMarkFrequency(RADIO_VHF, 0x25);		//Set AFSK Mark freq. of 2200 Hz
}

void RadioUHFInit() {
	//Reset Radio
	AX5043PwrReset(RADIO_UHF);

	//Power Down
	AX5043PwrSetPowerMode(RADIO_UHF, PwrMode_Powerdown);

	//Set GPIOs
	AX5043GPIOCnfgSysClk(RADIO_UHF, SysClk_Low, 0);
	AX5043GPIOCnfgDCLK(RADIO_UHF, DCLK_Modem_Data_Clk_Output, 0, 0);
	AX5043GPIOCnfgDATA(RADIO_UHF, DATA_Modem_Data_Output, 0, 0);
	//AX5043GPIOCnfgIRQ(RADIO_UHF, IRQ_Int_Req, 0, 0);		//Default
	AX5043GPIOCnfgAntSel(RADIO_UHF, AntSel_Low, 0, 0);
	AX5043GPIOCnfgPwrRamp(RADIO_UHF, PwrRamp_DAC_Output, 0, 0);	//Default

	//Set DAC
	AX5043GPIOSetDACInput(RADIO_UHF, DACInput_RSSI);
	AX5043GPIOSetDACInputShift(RADIO_UHF, 0x0C);

	//Set Performance Tuning Registers
	uint8_t data = 0x0F;
	AX5043WriteLongAddress(RADIO_UHF, PERFTUNE0, &data, 1);
	data = 0x03;
	AX5043WriteLongAddress(RADIO_UHF, PERFTUNE13, &data, 1);
	data = 0x04;
	AX5043WriteLongAddress(RADIO_UHF, PERFTUNE16, &data, 1);
	data = 0x00;
	AX5043WriteLongAddress(RADIO_UHF, PERFTUNE17, &data, 1);
	data = 0x06;
	AX5043WriteLongAddress(RADIO_UHF, PERFTUNE24, &data, 1);
	data = 0x07;
	AX5043WriteLongAddress(RADIO_UHF, PERFTUNE28, &data, 1);
	data = 0x5C;
	AX5043WriteLongAddress(RADIO_UHF, PERFTUNE33, &data, 1);
	data = 0x53;
	AX5043WriteLongAddress(RADIO_UHF, PERFTUNE34, &data, 1);
	data = 0x76;
	AX5043WriteLongAddress(RADIO_UHF, PERFTUNE35, &data, 1);
	data = 0x92;
	AX5043WriteLongAddress(RADIO_UHF, PERFTUNE38, &data, 1);
	data = 0x3F;
	AX5043WriteLongAddress(RADIO_UHF, PERFTUNE48, &data, 1);
	data = 0xF0;
	AX5043WriteLongAddress(RADIO_UHF, PERFTUNE49, &data, 1);
	data = 0x3F;
	AX5043WriteLongAddress(RADIO_UHF, PERFTUNE50, &data, 1);
	data = 0xF0;
	AX5043WriteLongAddress(RADIO_UHF, PERFTUNE51, &data, 1);
	data = 0x28;
	AX5043WriteLongAddress(RADIO_UHF, PERFTUNE52, &data, 1);
	data = 0x10;
	AX5043WriteLongAddress(RADIO_UHF, PERFTUNE53, &data, 1);
	data = 0x24;
	AX5043WriteLongAddress(RADIO_UHF, PERFTUNE68, &data, 1);
	data = 0x00;
	AX5043WriteLongAddress(RADIO_UHF, PERFTUNE114, &data, 1);

	//Set Synth
	AX5043SynthSetPLLLoopFilter(RADIO_UHF, PLLLoop_Filter500kHz);
//	AX5043SynthSetPLLChargePumpCurrent(RADIO_UHF, 0x10);
	AX5043SynthSetPLLVCOSelection(RADIO_UHF, 0);	//Use VCO 1
//	AX5043SynthSetPLLVCO2Internal(RADIO_UHF, 1);	//Use VCO 2 with external inductor
	AX5043SynthSetPLLVCOEnableRefDivider(RADIO_UHF, 1);
	AX5043SynthSetFrequencyA(RADIO_UHF, 0x1B474335);	//For 436.45MHz is 0x1B473334 calulated but calibrated value is 0x1B474335
//	AX5043SynthSetFrequencyB(RADIO_UHF, 0x1B473334);

	//Perform auto ranging
	AX5043SynthStartAutoRangingA(RADIO_UHF);
	while(AX5043SynthGetAutoRangingA(RADIO_UHF));	//Wait for Auto Ranging Complete
//	AX5043SynthStartAutoRangingB(RADIO_UHF);
//	while(AX5043SynthGetAutoRangingB(RADIO_UHF));	//Wait for Auto Ranging Complete

	//Set PLL/VCO Parameters
	//AX5043PLLParamSetVCOBias(RADIO_UHF, 0x07);
	//AX5043PLLParamIsManualVCOIEnabled(RADIO_UHF);
	//AX5043PLLParamSetLockDetectDelay(RADIO_UHF, 0x03);	//Default
	//AX5043PLLParamSetPLLRangingClock(RADIO_UHF, PLLRangingClock_11);	//Default

	//Set Modulation for TX Mode
	AX5043GeneralSetModulation(RADIO_UHF, AFSK);
	AX5043TXParamSetTXDatarate(RADIO_UHF, 0x04EB);	//Set datarate to 1200 bits/s
	AX5043TXParamSetFSKFrequencyDeviation(RADIO_UHF, 0x0A8E); //Set FSK deviation to 3000 Hz
	AX5043RXParamSetAFSKSpaceFrequency(RADIO_UHF, 0x14);	//Set AFSK Space freq. of 1200 Hz
	AX5043RXParamSetAFSKMarkFrequency(RADIO_UHF, 0x25);		//Set AFSK Mark freq. of 2200 Hz

	//Set Demodulation for RX Mode
	RadioUHFSetIF(50000);
	RadioUHFSetBandwidth(100000);
	RadioUHFSetRXBitrate(1200);

	//AX5043RXParamSetIFFrequency(RADIO_UHF, 0x0CCD);	//Set IF to 50 kHz
//	AX5043RXParamSetDecimation(RADIO_UHF, 0x28);	//Set decimation to have fbsaeband = 100 kHz
//	AX5043RXParamSetRXDatarate(RADIO_UHF, 0x034156);	//Set to 1200 bits/s
	AX5043RXParamSetRXMaximumDatarateOffset(RADIO_UHF, 0x00);
	AX5043RXParamSetRXMaximumFrequencyOffset(RADIO_UHF, 0x0419);	//Max RF offset set to +- 1kHz
	AX5043RXParamSetCorrectFrequencyOffsetLO(RADIO_UHF, 1);		//Correction done at 1st LO
	AX5043RXParamSetAFSKSpaceFrequency(RADIO_UHF, 0x0028);	//Set AFSK Space freq. of 1200 Hz
	AX5043RXParamSetAFSKMarkFrequency(RADIO_UHF, 0x0049);	//Set AFSK Mark freq. of 2200 Hz
	AX5043RXParamSetAFSKDetBandwitdh(RADIO_UHF, 0x0B);
	AX5043RXParamSetRXParameterNumber0(RADIO_UHF, 0);
	AX5043RXParamSetRXParameterNumber1(RADIO_UHF, 1);
	AX5043RXParamSetRXParameterNumber2(RADIO_UHF, 3);
	AX5043RXParamSetRXParameterNumber3(RADIO_UHF, 3);
	//RX Parameter 0
	AX5043RXParamSetAGCAttackSpeed0(RADIO_UHF, 0x08);
	AX5043RXParamSetAGCReleaseSpeed0(RADIO_UHF, 0x0E);
	AX5043RXParamSetAGCTargetAvgMagnitude0(RADIO_UHF, 0x84);
	AX5043PacketSetGainTimingRecovery0(RADIO_UHF, 0x0A, 0x0A);
	AX5043PacketSetGainDatarateRecovery0(RADIO_UHF, 0x0A, 0x04);
	AX5043RXParamSetRXFrequencyDeviation0(RADIO_UHF, 0x00);
	AX5043RXParamSetBasebandGainBlockAOffsetCompRes0(RADIO_UHF, 0x00);
	AX5043RXParamSetBasebandGainBlockBOffsetCompRes0(RADIO_UHF, 0x00);
	//RX Parameter 1
	AX5043RXParamSetAGCAttackSpeed1(RADIO_UHF, 0x08);
	AX5043RXParamSetAGCReleaseSpeed1(RADIO_UHF, 0x0E);
	AX5043RXParamSetAGCTargetAvgMagnitude1(RADIO_UHF, 0x84);
	AX5043PacketSetGainTimingRecovery1(RADIO_UHF, 0x0A, 0x08);
	AX5043PacketSetGainDatarateRecovery1(RADIO_UHF, 0x0A, 0x03);
	AX5043RXParamSetRXFrequencyDeviation1(RADIO_UHF, 0x4B);
	AX5043RXParamSetBasebandGainBlockAOffsetCompRes1(RADIO_UHF, 0x00);
	AX5043RXParamSetBasebandGainBlockBOffsetCompRes1(RADIO_UHF, 0x00);
	//RX Parameter 3
	AX5043RXParamSetAGCAttackSpeed3(RADIO_UHF, 0x0F);
	AX5043RXParamSetAGCReleaseSpeed3(RADIO_UHF, 0x0F);
	AX5043RXParamSetAGCTargetAvgMagnitude3(RADIO_UHF, 0x84);
	AX5043PacketSetGainTimingRecovery3(RADIO_UHF, 0x0A, 0x07);
	AX5043PacketSetGainDatarateRecovery3(RADIO_UHF, 0x0A, 0x02);
	AX5043RXParamSetRXFrequencyDeviation3(RADIO_UHF, 0x4B);
	AX5043RXParamSetBasebandGainBlockAOffsetCompRes3(RADIO_UHF, 0x00);
	AX5043RXParamSetBasebandGainBlockBOffsetCompRes3(RADIO_UHF, 0x00);

	//Set Packet, encoding and framing
//	AX5043PacketEnableEncodeBitInversion(RADIO_UHF, 1);
//	AX5043PacketEnableEncodeDiffrential(RADIO_UHF, 1);
	AX5043PacketSetFrameMode(RADIO_UHF, FrmMode_Raw);
//	AX5043PacketSetCRCMode(RADIO_UHF, CRCMode_Off);
//	AX5043PacketSetPacketChunkSize(RADIO_UHF, PacketChunkSize_240byte);
//	AX5043PacketSetPaternMatch0(RADIO_UHF, 0xAACCAACC);
//	AX5043PacketSetPaternMatch1(RADIO_UHF, 0x7E7E);
//	AX5043PacketSetPaternLength1(RADIO_UHF, 0x0F);
}

void RadioVHFEnterTX() {
	PwrStatus status = AX5043PwrStats(RADIO_VHF);
	AX5043PwrSetPowerMode(RADIO_VHF, PwrMode_TXEN);
	status = AX5043PwrStats(RADIO_VHF);
	while(status.svmodem != 0x01) {
		status = AX5043PwrStats(RADIO_VHF);
	}
}

void RadioUHFEnterTX() {
	PwrStatus status = AX5043PwrStats(RADIO_UHF);
	AX5043PwrSetPowerMode(RADIO_UHF, PwrMode_TXEN);
	status = AX5043PwrStats(RADIO_UHF);
	while(status.svmodem != 0x01) {
		status = AX5043PwrStats(RADIO_UHF);
	}
}

void RadioUHFSetBandwidth(uint32_t bandwidth) {
	uint8_t decimation = FXTAL / (bandwidth << 4);
	AX5043RXParamSetDecimation(RADIO_UHF, decimation);
}

void RadioUHFSetIF(uint32_t ifFreq) {
	uint16_t ifF = (uint16_t)(ifFreq * (1048576.f / FXTAL) + 0.5f);
	AX5043RXParamSetIFFrequency(RADIO_UHF, ifF);
}

void RadioUHFSetRXBitrate(uint32_t bitrate) {
	uint8_t decimation = AX5043RXParamGetDecimation(RADIO_UHF);
	uint32_t dr = (FXTAL << 7) / (bitrate * decimation);
	AX5043RXParamSetRXDatarate(RADIO_UHF, dr);
}

void RadioVHFWriteFrame(uint8_t data[], uint8_t dataLength) {
	uint8_t fifoData[256];
	uint8_t i = 0;

	fifoData[i++] = 0xE1;		//FIFO Data command
	fifoData[i++] = dataLength; //FIFO Data Length
	fifoData[i++] = 0x2B;		//Bypass encoder and framing, bypass CRC, set as start and end packet

	//Copy to send data
	uint8_t j;
	for(j = 0; j < dataLength; j++) {
		fifoData[i++] = data[j];
	}

	AX5043FIFOSetFIFO(RADIO_VHF, fifoData, i);
}

void RadioUHFWriteFrame(uint8_t data[], uint8_t dataLength) {
	uint8_t fifoData[256];
	uint8_t i = 0;

	fifoData[i++] = 0xE1;		//FIFO Data command
	fifoData[i++] = dataLength; //FIFO Data Length
	fifoData[i++] = 0x2B;		//Bypass encoder and framing, bypass CRC, set as start and end packet

	//Copy to send data
	uint8_t j;
	for(j = 0; j < dataLength; j++) {
		fifoData[i++] = data[j];
	}

	AX5043FIFOSetFIFO(RADIO_UHF, fifoData, i);
}
