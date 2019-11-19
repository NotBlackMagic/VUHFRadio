#include "ax5043_interface.h"

//Variable that holds all used AX5043 Interfaces, use for when more then one chip is used
volatile AX5043InterfaceStruct ax5043Interfaces[AX5043_MAX_INTERFACES_INSTANCES];

/**
  * @brief	This function initializes the AX5043 Interfaces array, copies the set function pointers
  * @param	interfaces: Array to interface function struct
  * @param	numInterfaces: Number of interfaces used aka number of AX5043 instances/ic's used
  * @return	0 if all operations are OK else 1
  */
uint8_t AX5043InterfacesInit(AX5043InterfaceStruct interfaces[], uint8_t numInterfaces) {
	if(numInterfaces > AX5043_MAX_INTERFACES_INSTANCES) {
		return 1;
	}

	uint8_t i;
	for(i = 0; i < numInterfaces; i++) {
		ax5043Interfaces[i] = interfaces[i];
	}

	return 0;
}

/**
  * @brief	This function reads/writes to a AX5043 register at address (16 bit address)
  * @param	interfaceID: Which AX5043 chip to send to, interface ID
  * @param	address: Address of the register to write to (16 bit address)
  * @param	dataIn: Array of data to be received
  * @param	length: Array of transmit/receive arrays aka number of bytes to transmit/receive
  * @return	StatusBits: status variable returned by the AX5043
  */
StatusBits AX5043ReadLongAddress(uint8_t interfaceID, uint16_t address, uint8_t dataIn[], uint16_t length) {
	StatusBits status;
	status.raw = 0;

	address = address | 0x7000;		//Set MSbit Address to 1, A12, A13, A14
	address = (address & 0x7FFF) ;	//Set nR/Write bit to Read (0)

	ax5043Interfaces[interfaceID].SPICS(0);		//Set CS low

	//Write 16 bit register address and read status
	status.raw = ax5043Interfaces[interfaceID].SPIReadWrite((address >> 8) & 0xFF) << 8;
	status.raw = ax5043Interfaces[interfaceID].SPIReadWrite(address & 0xFF);

	//Write/read data
	uint16_t i;
	for(i = 0; i < length; i++) {
		dataIn[i] = ax5043Interfaces[interfaceID].SPIReadWrite(0x00);
	}

	ax5043Interfaces[interfaceID].SPICS(1);		//Set CS High

	return status;
}

/**
  * @brief	This function reads/writes to a AX5043 register at address (16 bit address)
  * @param	interfaceID: Which AX5043 chip to send to, interface ID
  * @param	address: Address of the register to write to (16 bit address)
  * @param	dataOut: Array of data to be transmitted
  * @param	length: Array of transmit/receive arrays aka number of bytes to transmit/receive
  * @return	StatusBits: status variable returned by the AX5043
  */
StatusBits AX5043WriteLongAddress(uint8_t interfaceID, uint16_t address, uint8_t dataOut[], uint16_t length) {
	StatusBits status;
	status.raw = 0;

	address = address | 0x7000;		//Set MSbit Address to 1, A12, A13, A14
	address = address | 0x8000;		//Set nR/Write bit to Write (1)

	ax5043Interfaces[interfaceID].SPICS(0);		//Set CS low

	//Write 16 bit register address and read status
	status.raw = ax5043Interfaces[interfaceID].SPIReadWrite((address >> 8) & 0xFF) << 8;
	status.raw = ax5043Interfaces[interfaceID].SPIReadWrite(address & 0xFF);

	//Write/read data
	uint16_t i;
	for(i = 0; i < length; i++) {
		ax5043Interfaces[interfaceID].SPIReadWrite(dataOut[i]);
	}

	ax5043Interfaces[interfaceID].SPICS(1);		//Set CS High

	return status;
}

/**
  * @brief	This function reads to a AX5043 register at address (8 bit address)
  * @param	interfaceID: Which AX5043 chip to send to, interface ID
  * @param	address: Address of the register to write to (8 bit address)
  * @param	dataIn: Array of data to be received
  * @param	length: Array of transmit/receive arrays aka number of bytes to transmit/receive
  * @return	StatusBits: status variable returned by the AX5043, only bits 15 to 8 are valid (deepSleep to fifoEmpty)
  */
StatusBits AX5043ReadShortAddress(uint8_t interfaceID, uint8_t address, uint8_t dataIn[], uint16_t length) {
	StatusBits status;
	status.raw = 0;

	address = (address & 0x7F);		//Set nR/Write bit to Read (0)

	ax5043Interfaces[interfaceID].SPICS(0);		//Set CS low

	//Write 8 bit register address and read status
	status.raw = ax5043Interfaces[interfaceID].SPIReadWrite(address) << 8;

	//Write/read data
	uint16_t i;
	for(i = 0; i < length; i++) {
		dataIn[i] = ax5043Interfaces[interfaceID].SPIReadWrite(0x00);
	}

	ax5043Interfaces[interfaceID].SPICS(1);		//Set CS High

	return status;
}

/**
  * @brief	This function writes to a AX5043 register at address (8 bit address)
  * @param	interfaceID: Which AX5043 chip to send to, interface ID
  * @param	address: Address of the register to write to (8 bit address)
  * @param	dataOut: Array of data to be transmitted
  * @param	length: Array of transmit/receive arrays aka number of bytes to transmit/receive
  * @return	StatusBits: status variable returned by the AX5043, only bits 15 to 8 are valid (deepSleep to fifoEmpty)
  */
StatusBits AX5043WriteShortAddress(uint8_t interfaceID, uint8_t address, uint8_t dataOut[], uint16_t length) {
	StatusBits status;
	status.raw = 0;

	address = address | 0x80;		//Set nR/Write bit to Write (1)

	ax5043Interfaces[interfaceID].SPICS(0);		//Set CS low

	//Write 8 bit register address and read status
	status.raw = ax5043Interfaces[interfaceID].SPIReadWrite(address) << 8;

	//Write/read data
	uint16_t i;
	for(i = 0; i < length; i++) {
		ax5043Interfaces[interfaceID].SPIReadWrite(dataOut[i]);
	}

	ax5043Interfaces[interfaceID].SPICS(1);		//Set CS High

	return status;
}
