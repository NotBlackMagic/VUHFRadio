#include "ax5043_fifo.h"

/**
  * @brief	This function gets the FIFOStat
  * @param	interfaceID: Which interface (chip) used
  * @return	FIFOStat: The status of the FIFO
  */
FIFOStat AX5043FIFOGetFIFOStat(uint8_t interfaceID) {
	FIFOStat fifoStat;
	AX5043ReadShortAddress(interfaceID, FIFOSTAT, &fifoStat.raw, 1);
	return fifoStat;
}

/**
  * @brief	This function sends a FIFOStat Command
  * @param	interfaceID: Which interface (chip) used
  * @param	fifoStatCommand: The FIFO Stat Command to be sent
  * @return	None
  */
void AX5043FIFOSetFIFOStatCommand(uint8_t interfaceID, FIFOStatCmd fifoStatCommand) {
	uint8_t config = (uint8_t)fifoStatCommand;
	AX5043WriteShortAddress(interfaceID, FIFOSTAT, &config, 1);
}

/**
  * @brief	This function writes to the FIFO Register
  * @param	interfaceID: Which interface (chip) used
  * @param	data: The Data to write to the FIFO
  * @param	length: Number of bytes to write
  * @return	None
  */
void AX5043FIFOSetFIFO(uint8_t interfaceID, uint8_t *data, uint8_t length) {
	AX5043WriteShortAddress(interfaceID, FIFODATA, data, length);
}

/**
  * @brief	This function reads to the FIFO Register
  * @param	interfaceID: Which interface (chip) used
  * @param	data: The Data read from the FIFO
  * @param	length: Number of bytes to read from the FIFO
  * @return	None
  */
void AX5043FIFOGetFIFO(uint8_t interfaceID, uint8_t *data, uint8_t length) {
	AX5043ReadShortAddress(interfaceID, FIFODATA, data, length);
}

/**
  * @brief	This function gets the FIFO Count, number of committed FIFO words
  * @param	interfaceID: Which interface (chip) used
  * @return	Number of committed FIFO words
  */
uint16_t AX5043FIFOGetFIFOCount(uint8_t interfaceID) {
	uint16_t fifoCount = 0;
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, FIFOCOUNT1, &config, 1);
	fifoCount = (config & FIFOCOUNT1_MASK) << 8;
	AX5043ReadShortAddress(interfaceID, FIFOCOUNT0, &config, 1);
	fifoCount += (config & FIFOCOUNT0_MASK) ;
	return fifoCount;
}

/**
  * @brief	This function gets the FIFO Free, number of free FIFO words
  * @param	interfaceID: Which interface (chip) used
  * @return	Number of free FIFO words
  */
uint16_t AX5043FIFOGetFIFOFree(uint8_t interfaceID) {
	uint16_t fifoFree = 0;
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, FIFOFREE1, &config, 1);
	fifoFree = (config & FIFOFREE1_MASK) << 8;
	AX5043ReadShortAddress(interfaceID, FIFOFREE0, &config, 1);
	fifoFree += (config & FIFOFREE0_MASK) ;
	return fifoFree;
}

/**
  * @brief	This function gets the FIFO Threshold, number of free FIFO Threshold
  * @param	interfaceID: Which interface (chip) used
  * @return	Number of free FIFO Threshold
  */
uint16_t AX5043FIFOGetFIFOThreshold(uint8_t interfaceID) {
	uint16_t fifoThreshold = 0;
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, FIFOTHRESH1, &config, 1);
	fifoThreshold = (config & FIFOTHRESH1_MASK) << 8;
	AX5043ReadShortAddress(interfaceID, FIFOTHRESH0, &config, 1);
	fifoThreshold += (config & FIFOTHRESH0_MASK) ;
	return fifoThreshold;
}
