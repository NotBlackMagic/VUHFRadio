#include "ax5043_packet.h"

/**
  * @brief	This function enables data bit inversion
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Enable data bit inversion
  * @return	None
  */
void AX5043PacketEnableEncodeBitInversion(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, ENCODING, &config, 1);
	config = (config & ~ENCINV_MASK) | (enable);
	AX5043WriteLongAddress(interfaceID, ENCODING, &config, 1);
}

/**
  * @brief	This function if data bit inversion is enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	If data bit inversion is enabled
  */
uint8_t AX5043PacketIsEncodeBitInversionEnabled(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, ENCODING, &config, 1);
	return (config & ENCINV_MASK);
}

/**
  * @brief	This function enables differential encode/decode
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Enable differential encode/decode
  * @return	None
  */
void AX5043PacketEnableEncodeDifferential(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, ENCODING, &config, 1);
	config = (config & ~ENCDIFF_MASK) | (enable << 1);
	AX5043WriteLongAddress(interfaceID, ENCODING, &config, 1);
}

/**
  * @brief	This function if differential encode/decode is enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	If differential encode/decode is enabled
  */
uint8_t AX5043PacketIsEncodeDifferentialEnabled(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, ENCODING, &config, 1);
	return ((config & ENCDIFF_MASK) >> 1);
}

/**
  * @brief	This function enables scramble/descramble
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Enable scramble/descramble
  * @return	None
  */
void AX5043PacketEnableEncodeScramble(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, ENCODING, &config, 1);
	config = (config & ~ENCSCRAM_MASK) | (enable << 2);
	AX5043WriteLongAddress(interfaceID, ENCODING, &config, 1);
}

/**
  * @brief	This function if differential scramble/descramble  is enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	If scramble/descramble is enabled
  */
uint8_t AX5043PacketIsEncodeScrambleEnabled(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, ENCODING, &config, 1);
	return ((config & ENCSCRAM_MASK) >> 2);
}

/**
  * @brief	This function enables manchester encoding
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Enable scramble/descramble
  * @return	None
  */
void AX5043PacketEnableEncodeManchester(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, ENCODING, &config, 1);
	config = (config & ~ENCMNACH_MASK) | (enable << 3);
	AX5043WriteLongAddress(interfaceID, ENCODING, &config, 1);
}

/**
  * @brief	This function if manchester encoding is enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	If manchester encoding is enabled
  */
uint8_t AX5043PacketIsEncodManchesterEnabled(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, ENCODING, &config, 1);
	return ((config & ENCMNACH_MASK) >> 3);
}

/**
  * @brief	This function disables Dibit synchronization in 4-FSK
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Enable Dibit synchronization in 4-FSK
  * @return	None
  */
void AX5043PacketDisableEncodeDibit(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, ENCODING, &config, 1);
	config = (config & ~ENCNOSYNC_MASK) | (enable << 4);
	AX5043WriteLongAddress(interfaceID, ENCODING, &config, 1);
}

/**
  * @brief	This function if Dibit synchronization in 4-FSK is disabled
  * @param	interfaceID: Which interface (chip) used
  * @return	If Dibit synchronization in 4-FSK is disabled
  */
uint8_t AX5043PacketIsEncodeDibitDisabled(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, ENCODING, &config, 1);
	return ((config & ENCNOSYNC_MASK) >> 4);
}

/**
  * @brief	This function aborts current HDLC packet/pattern match
  * @param	interfaceID: Which interface (chip) used
  * @return	None
  */
void AX5043PacketAbortPatternMatch(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FRAMING, &config, 1);
	config = (config & ~FABORT_MASK) | (FABORT_MASK);
	AX5043WriteLongAddress(interfaceID, FRAMING, &config, 1);
}

/**
  * @brief	This function sets Frame Mode
  * @param	interfaceID: Which interface (chip) used
  * @param	FrmMode: Frame mode to use
  * @return	None
  */
void AX5043PacketSetFrameMode(uint8_t interfaceID, FrmMode frameMode) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FRAMING, &config, 1);
	config = (config & ~FRMMODE_MASK) | (frameMode << 1);
	AX5043WriteLongAddress(interfaceID, FRAMING, &config, 1);
}

/**
  * @brief	This function gets Frame Mode
  * @param	interfaceID: Which interface (chip) used
  * @return	Frame mode in use
  */
FrmMode AX5043PacketGetFrameMode(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FRAMING, &config, 1);
	return (FrmMode)((config & FRMMODE_MASK) >> 1);
}

/**
  * @brief	This function sets CRC Mode
  * @param	interfaceID: Which interface (chip) used
  * @param	CRCMode: CRC mode to use
  * @return	None
  */
void AX5043PacketSetCRCMode(uint8_t interfaceID, CRCMode frameMode) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FRAMING, &config, 1);
	config = (config & ~CRCMODE_MASK) | (frameMode << 4);
	AX5043WriteLongAddress(interfaceID, FRAMING, &config, 1);
}

/**
  * @brief	This function gets CRC Mode
  * @param	interfaceID: Which interface (chip) used
  * @return	CRCMode mode in use
  */
CRCMode AX5043PacketGetCRCMode(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FRAMING, &config, 1);
	return (CRCMode)((config & CRCMODE_MASK) >> 4);
}

/**
  * @brief	This function gets if a packet start was detected
  * @param	interfaceID: Which interface (chip) used
  * @return	If a packet start was detected
  */
uint8_t AX5043PacketPacketStartDetected(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FRAMING, &config, 1);
	return ((config & FRMRX_MASK) >> 7);
}

/**
  * @brief	This function sets the CRC reset value
  * @param	interfaceID: Which interface (chip) used
  * @param	crcInit: CRC Reset value
  * @return	None
  */
void AX5043PacketSetCRCInitValue(uint8_t interfaceID, uint32_t crcInit) {
	uint8_t config;
	config = (crcInit) & CRCINIT0_MASK;
	AX5043WriteLongAddress(interfaceID, CRCINIT0, &config, 1);
	config = (crcInit >> 8) & CRCINIT1_MASK;
	AX5043WriteLongAddress(interfaceID, CRCINIT1, &config, 1);
	config = (crcInit >> 16) & CRCINIT2_MASK;
	AX5043WriteLongAddress(interfaceID, CRCINIT2, &config, 1);
	config = (crcInit >> 24) & CRCINIT3_MASK;
	AX5043WriteLongAddress(interfaceID, CRCINIT3, &config, 1);
}

/**
  * @brief	This function gets the CRC reset value
  * @param	interfaceID: Which interface (chip) used
  * @return	CRC Reset value
  */
uint32_t AX5043PacketGetCRCInitValue(uint8_t interfaceID) {
	uint8_t config;
	uint32_t crcInit = 0;
	AX5043ReadLongAddress(interfaceID, CRCINIT0, &config, 1);
	crcInit = config & CRCINIT0_MASK;
	AX5043ReadLongAddress(interfaceID, CRCINIT1, &config, 1);
	crcInit += (config & CRCINIT1_MASK) << 8;
	AX5043ReadLongAddress(interfaceID, CRCINIT2, &config, 1);
	crcInit += (config & CRCINIT2_MASK) << 16;
	AX5043ReadLongAddress(interfaceID, CRCINIT3, &config, 1);
	crcInit += (config & CRCINIT3_MASK) << 24;
	return crcInit;
}

/**
  * @brief	This function enables FEC
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Enable FEC
  * @return	None
  */
void AX5043PacketEnableFEC(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FEC, &config, 1);
	config = (config & ~FECENA_MASK) | (enable);
	AX5043WriteLongAddress(interfaceID, FEC, &config, 1);
}

/**
  * @brief	This function if FEC is enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	If FEC is enabled
  */
uint8_t AX5043PacketIsFECEnabled(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FEC, &config, 1);
	return ((config & FECENA_MASK));
}

/**
  * @brief	This function set the attenuation soft RX data by 2^-FECINPSHIFT
  * @param	interfaceID: Which interface (chip) used
  * @param	inputShift: FECINPSHIFT
  * @return	None
  */
void AX5043PacketSetFECInputShift(uint8_t interfaceID, uint8_t inputShift) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FEC, &config, 1);
	config = (config & ~FECINPSHIFT_MASK) | (inputShift << 1);
	AX5043WriteLongAddress(interfaceID, FEC, &config, 1);
}

/**
  * @brief	This function gets the attenuation soft RX data by 2^-FECINPSHIFT
  * @param	interfaceID: Which interface (chip) used
  * @return	FECINPSHIFT
  */
uint8_t AX5043PacketGetFECInputShift(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FEC, &config, 1);
	return ((config & FECINPSHIFT_MASK) >> 1);
}

/**
  * @brief	This function enables noninverted interleave synchronization
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Enable noninverted interleave synchronization
  * @return	None
  */
void AX5043PacketEnableFECNonInvInterleave(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FEC, &config, 1);
	config = (config & ~FECPOS_MASK) | (enable << 4);
	AX5043WriteLongAddress(interfaceID, FEC, &config, 1);
}

/**
  * @brief	This function if noninverted interleave synchronization is enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	If noninverted interleave synchronization is enabled
  */
uint8_t AX5043PacketIsFECNonInvInterleaveEnabled(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FEC, &config, 1);
	return ((config & FECPOS_MASK) >> 4);
}

/**
  * @brief	This function enables inverted interleave synchronization
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Enable inverted interleave synchronization
  * @return	None
  */
void AX5043PacketEnableFECInvInterleave(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FEC, &config, 1);
	config = (config & ~FECNEG_MASK) | (enable << 5);
	AX5043WriteLongAddress(interfaceID, FEC, &config, 1);
}

/**
  * @brief	This function if inverted interleave synchronization is enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	If inverted interleave synchronization is enabled
  */
uint8_t AX5043PacketIsFECInvInterleaveEnabled(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FEC, &config, 1);
	return ((config & FECNEG_MASK) >> 5);
}

/**
  * @brief	This function enables inverted interleave synchronization
  * @param	interfaceID: Which interface (chip) used
  * @return	None
  */
void AX5043PacketResetViterbiDecoder(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FEC, &config, 1);
	config = (config & ~RSTVITERBI_MASK) | (RSTVITERBI_MASK);
	AX5043WriteLongAddress(interfaceID, FEC, &config, 1);
}

/**
  * @brief	This function enables shorten backtrack memory
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: Enable shorten backtrack memory
  * @return	None
  */
void AX5043PacketEnableShortenBacktrack(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FEC, &config, 1);
	config = (config & ~SHORTMEM_MASK) | (enable << 7);
	AX5043WriteLongAddress(interfaceID, FEC, &config, 1);
}

/**
  * @brief	This function if shorten backtrack memory is enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	If shorten backtrack memory is enabled
  */
uint8_t AX5043PacketIsShortenBacktrackEnabled(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FEC, &config, 1);
	return ((config & SHORTMEM_MASK) >> 7);
}

/**
  * @brief	This function sets FEC Interleaver synchronization threshold
  * @param	interfaceID: Which interface (chip) used
  * @param	fecSync: FEC Interleaver synchronization threshold
  * @return	None
  */
void AX5043PacketSetFECSync(uint8_t interfaceID, uint8_t fecSync) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FECSYNC, &config, 1);
	config = (config & ~FECSYNC_MASK) | (fecSync);
	AX5043WriteLongAddress(interfaceID, FECSYNC, &config, 1);
}

/**
  * @brief	This function gets FEC Interleaver synchronization threshold
  * @param	interfaceID: Which interface (chip) used
  * @return	FEC Interleaver synchronization threshold
  */
uint8_t AX5043PacketGetFECSync(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FECSYNC, &config, 1);
	return ((config & FECSYNC_MASK));
}

/**
  * @brief	This function gets the Metric increment of the survivor path
  * @param	interfaceID: Which interface (chip) used
  * @return	FEC Interleaver synchronization threshold
  */
uint8_t AX5043PacketGetMetricIncrementSurvivorPath(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FECSTATUS, &config, 1);
	return ((config & MAXMETRIC_MASK));
}

/**
  * @brief	This function gets if inverted synchronization sequence received
  * @param	interfaceID: Which interface (chip) used
  * @return	If inverted synchronization sequence received
  */
uint8_t AX5043PacketGetInvertedSyncSeqReceived(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, FECSTATUS, &config, 1);
	return ((config & FECINV_MASK) >> 7);
}

/**
  * @brief	This function sets the Address bytes Position
  * @param	interfaceID: Which interface (chip) used
  * @param	position: Address bytes Position
  * @return	None
  */
void AX5043PacketSetAddressBytesPosition(uint8_t interfaceID, uint8_t position) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTADDRCFG, &config, 1);
	config = (config & ~ADDRPOS_MASK) | (position);
	AX5043WriteLongAddress(interfaceID, PKTADDRCFG, &config, 1);
}

/**
  * @brief	This function gets the Address bytes Position
  * @param	interfaceID: Which interface (chip) used
  * @return	Address bytes Position
  */
uint8_t AX5043PacketGetAddressBytesPosition(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTADDRCFG, &config, 1);
	return (config & ADDRPOS_MASK);
}

/**
  * @brief	This function disables/enables FEC Sync Search during packet reception
  * @param	interfaceID: Which interface (chip) used
  * @param	disable: 1 -> Disable FEC Sync, 0 -> Enable FEC Sync
  * @return	None
  */
void AX5043PacketDisableFECSync(uint8_t interfaceID, uint8_t disable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTADDRCFG, &config, 1);
	config = (config & ~FECSYNCDIS_MASK) | (disable << 5);
	AX5043WriteLongAddress(interfaceID, PKTADDRCFG, &config, 1);
}

/**
  * @brief	This function gets if FEC Sync Search during packet reception is disabled
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> FEC Sync Disabled, 0 -> FEC Sync Enabled
  */
uint8_t AX5043PacketIfFECSyncDisabled(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTADDRCFG, &config, 1);
	return ((config & FECSYNCDIS_MASK) >> 5);
}

/**
  * @brief	This function sets skip first byte for CRC Calculation
  * @param	interfaceID: Which interface (chip) used
  * @param	skip: 1 -> Skip First Byte, 0 -> Don't Skip First Byte
  * @return	None
  */
void AX5043PacketSetSkipFirstByteCRC(uint8_t interfaceID, uint8_t skip) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTADDRCFG, &config, 1);
	config = (config & ~CRCSKIPFIRST_MASK) | (skip << 6);
	AX5043WriteLongAddress(interfaceID, PKTADDRCFG, &config, 1);
}

/**
  * @brief	This function gets if skip first byte for CRC Calculation is enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> Skip First Byte, 0 -> Don't Skip First Byte
  */
uint8_t AX5043PacketGetSkipFirstByteCRC(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTADDRCFG, &config, 1);
	return ((config & CRCSKIPFIRST_MASK) >> 6);
}

/**
  * @brief	This function sets MSBit First mode
  * @param	interfaceID: Which interface (chip) used
  * @param	msbFirst: 1 -> MSBbit First, 0 -> LSBbit First
  * @return	None
  */
void AX5043PacketSetMSBFirst(uint8_t interfaceID, uint8_t msbFirst) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTADDRCFG, &config, 1);
	config = (config & ~MSBFIRST_MASK) | (msbFirst << 7);
	AX5043WriteLongAddress(interfaceID, PKTADDRCFG, &config, 1);
}

/**
  * @brief	This function gets which MSBit/LSBit First mode is used
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> MSBbit First, 0 -> LSBbit First
  */
uint8_t AX5043PacketGetMSBFirst(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTADDRCFG, &config, 1);
	return ((config & MSBFIRST_MASK) >> 7);
}

/**
  * @brief	This function sets the Length bytes Position
  * @param	interfaceID: Which interface (chip) used
  * @param	position: Length bytes Position
  * @return	None
  */
void AX5043PacketSetLengthBytesPosition(uint8_t interfaceID, uint8_t position) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTLENCFG, &config, 1);
	config = (config & ~LENPOS_MASK) | (position);
	AX5043WriteLongAddress(interfaceID, PKTLENCFG, &config, 1);
}

/**
  * @brief	This function gets the Length bytes Position
  * @param	interfaceID: Which interface (chip) used
  * @return	Length bytes Position
  */
uint8_t AX5043PacketGetLengthBytesPosition(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTLENCFG, &config, 1);
	return (config & LENPOS_MASK);
}

/**
  * @brief	This function sets the number of significant bits in the Length byte
  * @param	interfaceID: Which interface (chip) used
  * @param	significantBits: Number of significant bits in the Length byte
  * @return	None
  */
void AX5043PacketSetLengthByteSignificantBits(uint8_t interfaceID, uint8_t significantBits) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTLENCFG, &config, 1);
	config = (config & ~LENBITS_MASK) | (significantBits << 4);
	AX5043WriteLongAddress(interfaceID, PKTLENCFG, &config, 1);
}

/**
  * @brief	This function gets the number of significant bits in the Length byte
  * @param	interfaceID: Which interface (chip) used
  * @return	Number of significant bits in the Length byte
  */
uint8_t AX5043PacketGetLengthByteSignificantBits(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTLENCFG, &config, 1);
	return ((config & LENBITS_MASK) >> 4);
}

/**
  * @brief	This function sets the packet length offset
  * @param	interfaceID: Which interface (chip) used
  * @param	offset: Packet Length Offset, is added to length byte by the receiver
  * @return	None
  */
void AX5043PacketSetLengthOffset(uint8_t interfaceID, uint8_t offset) {
	AX5043WriteLongAddress(interfaceID, PKTLENOFFSET, &offset, 1);
}

/**
  * @brief	This function gets the packet length offset
  * @param	interfaceID: Which interface (chip) used
  * @return	Packet Length Offset
  */
uint8_t AX5043PacketGetLengthOffset(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTLENOFFSET, &config, 1);
	return config;
}

/**
  * @brief	This function sets the maximum packet length
  * @param	interfaceID: Which interface (chip) used
  * @param	length: Maximum Packet Length
  * @return	None
  */
void AX5043PacketSetMaxLength(uint8_t interfaceID, uint8_t length) {
	AX5043WriteLongAddress(interfaceID, PKTMAXLEN, &length, 1);
}

/**
  * @brief	This function gets the maximum packet length
  * @param	interfaceID: Which interface (chip) used
  * @return	Maximum Packet Length
  */
uint8_t AX5043PacketGetMaxLength(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTMAXLEN, &config, 1);
	return config;
}

/**
  * @brief	This function sets the Packet Address
  * @param	interfaceID: Which interface (chip) used
  * @param	address: Packet Address
  * @return	None
  */
void AX5043PacketSetAddress(uint8_t interfaceID, uint32_t address) {
	uint8_t config;
	config = address & PKTADDR0_MASK;
	AX5043WriteLongAddress(interfaceID, PKTADDR0, &config, 1);
	config = (address >> 8) & PKTADDR1_MASK;
	AX5043WriteLongAddress(interfaceID, PKTADDR1, &config, 1);
	config = (address >> 16) & PKTADDR2_MASK;
	AX5043WriteLongAddress(interfaceID, PKTADDR2, &config, 1);
	config = (address >> 24) & PKTADDR3_MASK;
	AX5043WriteLongAddress(interfaceID, PKTADDR3, &config, 1);
}

/**
  * @brief	This function gets the Packet Address
  * @param	interfaceID: Which interface (chip) used
  * @return	Packet Address
  */
uint32_t AX5043PacketGetAddress(uint8_t interfaceID) {
	uint32_t address = 0;
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTADDR0, &config, 1);
	address = config & PKTADDR0_MASK;
	AX5043ReadLongAddress(interfaceID, PKTADDR1, &config, 1);
	address += (config & PKTADDR1_MASK) << 8;
	AX5043ReadLongAddress(interfaceID, PKTADDR2, &config, 1);
	address += (config & PKTADDR2_MASK) << 16;
	AX5043ReadLongAddress(interfaceID, PKTADDR3, &config, 1);
	address += (config & PKTADDR3_MASK) << 24;
	return address;
}

/**
  * @brief	This function sets the Packet Address Mask
  * @param	interfaceID: Which interface (chip) used
  * @param	addressMask: Packet Address Mask
  * @return	None
  */
void AX5043PacketSetAddressMask(uint8_t interfaceID, uint32_t addressMask) {
	uint8_t config;
	config = addressMask & PKTADDRMASK0_MASK;
	AX5043WriteLongAddress(interfaceID, PKTADDRMASK0, &config, 1);
	config = (addressMask >> 8) & PKTADDRMASK1_MASK;
	AX5043WriteLongAddress(interfaceID, PKTADDRMASK1, &config, 1);
	config = (addressMask >> 16) & PKTADDRMASK2_MASK;
	AX5043WriteLongAddress(interfaceID, PKTADDRMASK2, &config, 1);
	config = (addressMask >> 24) & PKTADDRMASK3_MASK;
	AX5043WriteLongAddress(interfaceID, PKTADDRMASK3, &config, 1);
}

/**
  * @brief	This function gets the Packet Address Mask
  * @param	interfaceID: Which interface (chip) used
  * @return	Packet Address Mask
  */
uint32_t AX5043PacketGetAddressMask(uint8_t interfaceID) {
	uint32_t addressMask = 0;
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTADDRMASK0, &config, 1);
	addressMask = config & PKTADDRMASK0_MASK;
	AX5043ReadLongAddress(interfaceID, PKTADDRMASK1, &config, 1);
	addressMask += (config & PKTADDRMASK1_MASK) << 8;
	AX5043ReadLongAddress(interfaceID, PKTADDRMASK2, &config, 1);
	addressMask += (config & PKTADDRMASK2_MASK) << 16;
	AX5043ReadLongAddress(interfaceID, PKTADDRMASK3, &config, 1);
	addressMask += (config & PKTADDRMASK3_MASK) << 24;
	return addressMask;
}

/**
  * @brief	This function sets the Patern Match 0 Unit. Must be MSB Aligned
  * @param	interfaceID: Which interface (chip) used
  * @param	paternMatch: Patern Match. MSB Aligned
  * @return	None
  */
void AX5043PacketSetPaternMatch0(uint8_t interfaceID, uint32_t paternMatch) {
	uint8_t config;
	config = paternMatch & MATCH0PAT0_MASK;
	AX5043WriteLongAddress(interfaceID, MATCH0PAT0, &config, 1);
	config = (paternMatch >> 8) & MATCH0PAT1_MASK;
	AX5043WriteLongAddress(interfaceID, MATCH0PAT1, &config, 1);
	config = (paternMatch >> 16) & MATCH0PAT2_MASK;
	AX5043WriteLongAddress(interfaceID, MATCH0PAT2, &config, 1);
	config = (paternMatch >> 24) & MATCH0PAT3_MASK;
	AX5043WriteLongAddress(interfaceID, MATCH0PAT3, &config, 1);
}

/**
  * @brief	This function gets the Patern Match 0 Unit
  * @param	interfaceID: Which interface (chip) used
  * @return	Patern Match
  */
uint32_t AX5043PacketGetPaternMatch0(uint8_t interfaceID) {
	uint32_t paternMatch = 0;
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, MATCH0PAT0, &config, 1);
	paternMatch = config & MATCH0PAT0_MASK;
	AX5043ReadLongAddress(interfaceID, MATCH0PAT1, &config, 1);
	paternMatch += (config & MATCH0PAT1_MASK) << 8;
	AX5043ReadLongAddress(interfaceID, MATCH0PAT2, &config, 1);
	paternMatch += (config & MATCH0PAT2_MASK) << 16;
	AX5043ReadLongAddress(interfaceID, MATCH0PAT3, &config, 1);
	paternMatch += (config & MATCH0PAT3_MASK) << 24;
	return paternMatch;
}

/**
  * @brief	This function sets the length in bits of the patern 0 (MATCH0LEN + 1)
  * @param	interfaceID: Which interface (chip) used
  * @param	length: Length in bits of the patern 0 (MATCH0LEN + 1)
  * @return	None
  */
void AX5043PacketSetPaternLength0(uint8_t interfaceID, uint8_t length) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, MATCH0LEN, &config, 1);
	config = (config & ~MATCH0LEN_MASK) | (length);
	AX5043WriteLongAddress(interfaceID, MATCH0LEN, &config, 1);
}

/**
  * @brief	This function gets the length in bits of the patern 0 (MATCH0LEN + 1)
  * @param	interfaceID: Which interface (chip) used
  * @return	Length in bits of the patern (MATCH0LEN + 1)
  */
uint8_t AX5043PacketGetPaternLength0(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, MATCH0LEN, &config, 1);
	return (config & MATCH0LEN_MASK);
}

/**
  * @brief	This function sets if patern Match 0 operates on decoded or raw bits
  * @param	interfaceID: Which interface (chip) used
  * @param	raw: 0 -> On Decoded bits, 1 -> On Raw Bits
  * @return	None
  */
void AX5043PacketSetPaternMatch0Raw(uint8_t interfaceID, uint8_t raw) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, MATCH0LEN, &config, 1);
	config = (config & ~MATCH0RAW_MASK) | (raw << 7);
	AX5043WriteLongAddress(interfaceID, MATCH0LEN, &config, 1);
}

/**
  * @brief	This function gets if patern Match 0 operates on decoded or raw bits
  * @param	interfaceID: Which interface (chip) used
  * @return	0 -> On Decoded bits, 1 -> On Raw Bits
  */
uint8_t AX5043PacketGetPaternMatch0Raw(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, MATCH0LEN, &config, 1);
	return ((config & MATCH0RAW_MASK) >> 7);
}

/**
  * @brief	This function sets the number of bits to signal a patern match 0, set if below (used for inverted paterns)
  * @param	interfaceID: Which interface (chip) used
  * @param	minimum: Number of bits
  * @return	None
  */
void AX5043PacketSetPaternMatch0Min(uint8_t interfaceID, uint8_t minimum) {
	uint8_t config = minimum & MATCH0MIN_MASK;
	AX5043WriteLongAddress(interfaceID, MATCH0MIN, &config, 1);
}

/**
  * @brief	This function gets the number of bits to signal a patern match 0, set if below (used for inverted paterns)
  * @param	interfaceID: Which interface (chip) used
  * @return	Number of bits
  */
uint8_t AX5043PacketGetPaternMatch0Min(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, MATCH0MIN, &config, 1);
	return (config & MATCH0MIN_MASK);
}

/**
  * @brief	This function sets the number of bits to signal a patern match 0, set if above
  * @param	interfaceID: Which interface (chip) used
  * @param	minimum: Number of bits
  * @return	None
  */
void AX5043PacketSetPaternMatch0Max(uint8_t interfaceID, uint8_t minimum) {
	uint8_t config = minimum & MATCH0MAX_MASK;
	AX5043WriteLongAddress(interfaceID, MATCH0MAX, &config, 1);
}

/**
  * @brief	This function gets the number of bits to signal a patern match 0, set if above
  * @param	interfaceID: Which interface (chip) used
  * @return	Number of bits
  */
uint8_t AX5043PacketGetPaternMatch0Max(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, MATCH0MAX, &config, 1);
	return (config & MATCH0MAX_MASK);
}

/**
  * @brief	This function sets the Patern Match 1 Unit. Must be MSB Aligned
  * @param	interfaceID: Which interface (chip) used
  * @param	paternMatch: Patern Match. MSB Aligned
  * @return	None
  */
void AX5043PacketSetPaternMatch1(uint8_t interfaceID, uint16_t paternMatch) {
	uint8_t config;
	config = paternMatch & MATCH1PAT0_MASK;
	AX5043WriteLongAddress(interfaceID, MATCH1PAT0, &config, 1);
	config = (paternMatch >> 8) & MATCH1PAT1_MASK;
	AX5043WriteLongAddress(interfaceID, MATCH1PAT1, &config, 1);
}

/**
  * @brief	This function gets the Patern Match 1 Unit
  * @param	interfaceID: Which interface (chip) used
  * @return	Patern Match
  */
uint16_t AX5043PacketGetPaternMatch1(uint8_t interfaceID) {
	uint16_t paternMatch = 0;
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, MATCH1PAT0, &config, 1);
	paternMatch = config & MATCH1PAT0_MASK;
	AX5043ReadLongAddress(interfaceID, MATCH1PAT1, &config, 1);
	paternMatch += (config & MATCH1PAT1_MASK) << 8;
	return paternMatch;
}

/**
  * @brief	This function sets the length in bits of the patern 1 (MATCH0LEN + 1)
  * @param	interfaceID: Which interface (chip) used
  * @param	length: Length in bits of the patern 1 (MATCH0LEN + 1)
  * @return	None
  */
void AX5043PacketSetPaternLength1(uint8_t interfaceID, uint8_t length) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, MATCH1LEN, &config, 1);
	config = (config & ~MATCH1LEN_MASK) | (length);
	AX5043WriteLongAddress(interfaceID, MATCH1LEN, &config, 1);
}

/**
  * @brief	This function gets the length in bits of the patern 1 (MATCH0LEN + 1)
  * @param	interfaceID: Which interface (chip) used
  * @return	Length in bits of the patern (MATCH0LEN + 1)
  */
uint8_t AX5043PacketGetPaternLength1(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, MATCH1LEN, &config, 1);
	return (config & MATCH1LEN_MASK);
}

/**
  * @brief	This function sets if patern Match 1 operates on decoded or raw bits
  * @param	interfaceID: Which interface (chip) used
  * @param	raw: 0 -> On Decoded bits, 1 -> On Raw Bits
  * @return	None
  */
void AX5043PacketSetPaternMatch1Raw(uint8_t interfaceID, uint8_t raw) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, MATCH1LEN, &config, 1);
	config = (config & ~MATCH1RAW_MASK) | (raw << 7);
	AX5043WriteLongAddress(interfaceID, MATCH1LEN, &config, 1);
}

/**
  * @brief	This function gets if patern Match 1 operates on decoded or raw bits
  * @param	interfaceID: Which interface (chip) used
  * @return	0 -> On Decoded bits, 1 -> On Raw Bits
  */
uint8_t AX5043PacketGetPaternMatch1Raw(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, MATCH1LEN, &config, 1);
	return ((config & MATCH1RAW_MASK) >> 7);
}

/**
  * @brief	This function sets the number of bits to signal a patern match 0, set if below (used for inverted paterns)
  * @param	interfaceID: Which interface (chip) used
  * @param	minimum: Number of bits
  * @return	None
  */
void AX5043PacketSetPaternMatch1Min(uint8_t interfaceID, uint8_t minimum) {
	uint8_t config = minimum & MATCH1MIN_MASK;
	AX5043WriteLongAddress(interfaceID, MATCH1MIN, &config, 1);
}

/**
  * @brief	This function gets the number of bits to signal a patern match 0, set if below (used for inverted paterns)
  * @param	interfaceID: Which interface (chip) used
  * @return	Number of bits
  */
uint8_t AX5043PacketGetPaternMatch1Min(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, MATCH1MIN, &config, 1);
	return (config & MATCH1MIN_MASK);
}

/**
  * @brief	This function sets the number of bits to signal a patern match 1, set if above
  * @param	interfaceID: Which interface (chip) used
  * @param	minimum: Number of bits
  * @return	None
  */
void AX5043PacketSetPaternMatch1Max(uint8_t interfaceID, uint8_t minimum) {
	uint8_t config = minimum & MATCH1MAX_MASK;
	AX5043WriteLongAddress(interfaceID, MATCH1MAX, &config, 1);
}

/**
  * @brief	This function gets the number of bits to signal a patern match 1, set if above
  * @param	interfaceID: Which interface (chip) used
  * @return	Number of bits
  */
uint8_t AX5043PacketGetPaternMatch1Max(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, MATCH1MAX, &config, 1);
	return (config & MATCH1MAX_MASK);
}

/**
  * @brief	This function sets the Transmit PLL Boost Time, (TMGTXBOOSTM * 2^TMGTXBOOSTE us)
  * @param	interfaceID: Which interface (chip) used
  * @param	mantissa: PLL Boost Time Mantissa
  * @param	exponent: PLL Boost Time Exponent
  * @return	None
  */
void AX5043PacketSetTXPLLBoostTime(uint8_t interfaceID, uint8_t mantissa, uint8_t exponent) {
	uint8_t config = (mantissa & TMGTXBOOSTM_MASK) + ((exponent << 5) & TMGTXBOOSTE_MASK);
	AX5043WriteLongAddress(interfaceID, TMGTXBOOST, &config, 1);
}

/**
  * @brief	This function gets the Transmit PLL Boost Time, (TMGTXBOOSTM * 2^TMGTXBOOSTE us)
  * @param	interfaceID: Which interface (chip) used
  * @param	mantissa: PLL Boost Time Mantissa return value
  * @param	exponent: PLL Boost Time Exponent return value
  * @return	None
  */
void AX5043PacketGetTXPLLBoostTime(uint8_t interfaceID, uint8_t* mantissa, uint8_t* exponent) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, TMGTXBOOST, &config, 1);
	*mantissa = (config & TMGTXBOOSTM_MASK);
	*exponent = (config & TMGTXBOOSTE_MASK) >> 5;
}

/**
  * @brief	This function sets the Transmit PLL (post Boost) Settling Time, (TMGTXBOOSTM * 2^TMGTXBOOSTE us)
  * @param	interfaceID: Which interface (chip) used
  * @param	mantissa: PLL (post Boost) Settling Time Mantissa
  * @param	exponent: PLL (post Boost) Settling Time Exponent
  * @return	None
  */
void AX5043PacketSetTXPLLSettlingTime(uint8_t interfaceID, uint8_t mantissa, uint8_t exponent) {
	uint8_t config = (mantissa & TMGTXSETTLEM_MASK) + ((exponent << 5) & TMGTXSETTLEE_MASK);
	AX5043WriteLongAddress(interfaceID, TMGTXSETTLE, &config, 1);
}

/**
  * @brief	This function gets the Transmit PLL (post Boost) Settling Time, (TMGTXSETTLEM * 2^TMGTXSETTLEE us)
  * @param	interfaceID: Which interface (chip) used
  * @param	mantissa: PLL(post Boost) Settling Time Mantissa return value
  * @param	exponent: PLL (post Boost) Settling Time Exponent return value
  * @return	None
  */
void AX5043PacketGetTXPLLSettlingTime(uint8_t interfaceID, uint8_t* mantissa, uint8_t* exponent) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, TMGTXSETTLE, &config, 1);
	*mantissa = (config & TMGTXSETTLEM_MASK);
	*exponent = (config & TMGTXSETTLEE_MASK) >> 5;
}

/**
  * @brief	This function sets the Receive PLL (post Boost) Settling Time, (TMGRXSETTLEM * 2^TMGRXSETTLEE us)
  * @param	interfaceID: Which interface (chip) used
  * @param	mantissa: PLL (post Boost) Settling Time Mantissa
  * @param	exponent: PLL (post Boost) Settling Time Exponent
  * @return	None
  */
void AX5043PacketSetRXPLLSettlingTime(uint8_t interfaceID, uint8_t mantissa, uint8_t exponent) {
	uint8_t config = (mantissa & TMGRXSETTLEM_MASK) + ((exponent << 5) & TMGRXSETTLEE_MASK);
	AX5043WriteLongAddress(interfaceID, TMGRXSETTLE, &config, 1);
}

/**
  * @brief	This function gets the Receive PLL (post Boost) Settling Time, (TMGRXSETTLEM * 2^TMGRXSETTLEE us)
  * @param	interfaceID: Which interface (chip) used
  * @param	mantissa: PLL(post Boost) Settling Time Mantissa return value
  * @param	exponent: PLL (post Boost) Settling Time Exponent return value
  * @return	None
  */
void AX5043PacketGetRXPLLSettlingTime(uint8_t interfaceID, uint8_t* mantissa, uint8_t* exponent) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, TMGRXSETTLE, &config, 1);
	*mantissa = (config & TMGRXSETTLEM_MASK);
	*exponent = (config & TMGRXSETTLEE_MASK) >> 5;
}

/**
  * @brief	This function sets the Receive DC Offset Acquisition Time, (TMGRXOFFSACQM * 2^TMGRXOFFSACQE us)
  * @param	interfaceID: Which interface (chip) used
  * @param	mantissa: Receive DC Offset Acquisition Time Mantissa
  * @param	exponent: Receive DC Offset Acquisition Time Exponent
  * @return	None
  */
void AX5043PacketSetRXDCOffsetAcquisitionTime(uint8_t interfaceID, uint8_t mantissa, uint8_t exponent) {
	uint8_t config = (mantissa & TMGRXOFFSACQM_MASK) + ((exponent << 5) & TMGRXOFFSACQE_MASK);
	AX5043WriteLongAddress(interfaceID, TMGRXOFFSACQ, &config, 1);
}

/**
  * @brief	This function gets the Receive DC Offset Acquisition Time, (TMGRXOFFSACQM * 2^TMGRXOFFSACQE us)
  * @param	interfaceID: Which interface (chip) used
  * @param	mantissa: Receive DC Offset Acquisition Time Mantissa return value
  * @param	exponent: Receive DC Offset Acquisition Time Exponent return value
  * @return	None
  */
void AX5043PacketGetRXDCOffsetAcquisitionTime(uint8_t interfaceID, uint8_t* mantissa, uint8_t* exponent) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, TMGRXOFFSACQ, &config, 1);
	*mantissa = (config & TMGRXOFFSACQM_MASK);
	*exponent = (config & TMGRXOFFSACQE_MASK) >> 5;
}

/**
  * @brief	This function sets the Receive Coarse AGC Time, (TMGRXCOARSEAGCM * 2^TMGRXCOARSEAGCE us)
  * @param	interfaceID: Which interface (chip) used
  * @param	mantissa: Receive Coarse AGC Time Mantissa
  * @param	exponent: Receive Coarse AGC Time Exponent
  * @return	None
  */
void AX5043PacketSetRXCoarseAGCTime(uint8_t interfaceID, uint8_t mantissa, uint8_t exponent) {
	uint8_t config = (mantissa & TMGRXCOARSEAGCM_MASK) + ((exponent << 5) & TMGRXCOARSEAGCE_MASK);
	AX5043WriteLongAddress(interfaceID, TMGRXCOARSEAGC, &config, 1);
}

/**
  * @brief	This function gets the Receive Coarse AGC Time, (TMGRXCOARSEAGCM * 2^TMGRXCOARSEAGCE us)
  * @param	interfaceID: Which interface (chip) used
  * @param	mantissa: Receive Coarse AGC Time Mantissa return value
  * @param	exponent: Receive Coarse AGC Time Exponent return value
  * @return	None
  */
void AX5043PacketGetRXCoarseAGCTime(uint8_t interfaceID, uint8_t* mantissa, uint8_t* exponent) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, TMGRXCOARSEAGC, &config, 1);
	*mantissa = (config & TMGRXCOARSEAGCM_MASK);
	*exponent = (config & TMGRXCOARSEAGCE_MASK) >> 5;
}

/**
  * @brief	This function sets the Receive AGC Settling Time, (TMGRXAGCM_MASK * 2^TMGRXAGCE_MASK us)
  * @param	interfaceID: Which interface (chip) used
  * @param	mantissa: Receive AGC Settling Time Mantissa
  * @param	exponent: Receive AGC Settling Time Exponent
  * @return	None
  */
void AX5043PacketSetRXAGCSettlingTime(uint8_t interfaceID, uint8_t mantissa, uint8_t exponent) {
	uint8_t config = (mantissa & TMGRXAGCM_MASK) + ((exponent << 5) & TMGRXAGCE_MASK);
	AX5043WriteLongAddress(interfaceID, TMGRXAGC, &config, 1);
}

/**
  * @brief	This function gets the Receive AGC Settling Time, (TMGRXCOARSEAGCM * 2^TMGRXCOARSEAGCE us)
  * @param	interfaceID: Which interface (chip) used
  * @param	mantissa: Receive AGC Settling Time Mantissa return value
  * @param	exponent: Receive AGC Settling Time Exponent return value
  * @return	None
  */
void AX5043PacketGetRXAGCSettlingTime(uint8_t interfaceID, uint8_t* mantissa, uint8_t* exponent) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, TMGRXAGC, &config, 1);
	*mantissa = (config & TMGRXAGCM_MASK);
	*exponent = (config & TMGRXAGCE_MASK) >> 5;
}

/**
  * @brief	This function sets the Receive RSSI Settling Time, (TMGRXRSSIM_MASK * 2^TMGRXRSSIE_MASK us)
  * @param	interfaceID: Which interface (chip) used
  * @param	mantissa: Receive RSSI Settling Time Mantissa
  * @param	exponent: Receive RSSI Settling Time Exponent
  * @return	None
  */
void AX5043PacketSetRXRSSISettlingTime(uint8_t interfaceID, uint8_t mantissa, uint8_t exponent) {
	uint8_t config = (mantissa & TMGRXRSSIM_MASK) + ((exponent << 5) & TMGRXRSSIE_MASK);
	AX5043WriteLongAddress(interfaceID, TMGRXRSSI, &config, 1);
}

/**
  * @brief	This function gets the Receive RSSI Settling Time, (TMGRXRSSIM_MASK * 2^TMGRXRSSIE_MASK us)
  * @param	interfaceID: Which interface (chip) used
  * @param	mantissa: Receive RSSI Settling Time Mantissa return value
  * @param	exponent: Receive RSSI Settling Time Exponent return value
  * @return	None
  */
void AX5043PacketGetRXRSSISettlingTime(uint8_t interfaceID, uint8_t* mantissa, uint8_t* exponent) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, TMGRXRSSI, &config, 1);
	*mantissa = (config & TMGRXRSSIM_MASK);
	*exponent = (config & TMGRXRSSIE_MASK) >> 5;
}

/**
  * @brief	This function sets the Recevie Preamble 1 Timeout, (TMGRXPREAMBLE1M_MASK * 2^TMGRXPREAMBLE1E_MASK us)
  * @param	interfaceID: Which interface (chip) used
  * @param	mantissa: Receive Preamble 1 Timeout Mantissa
  * @param	exponent: Receive Preamble 1 Timeout Exponent
  * @return	None
  */
void AX5043PacketSetRXPreamble1Timeout(uint8_t interfaceID, uint8_t mantissa, uint8_t exponent) {
	uint8_t config = (mantissa & TMGRXPREAMBLE1M_MASK) + ((exponent << 5) & TMGRXPREAMBLE1E_MASK);
	AX5043WriteLongAddress(interfaceID, TMGRXPREAMBLE1, &config, 1);
}

/**
  * @brief	This function gets the Receive Preamble 1 Timeout, (TMGRXPREAMBLE1M_MASK * 2^TMGRXPREAMBLE1E_MASK us)
  * @param	interfaceID: Which interface (chip) used
  * @param	mantissa: Receive Preamble 1 Timeout Mantissa return value
  * @param	exponent: Receive Preamble 1 Timeout Exponent return value
  * @return	None
  */
void AX5043PacketGetRXPreamble1Timeout(uint8_t interfaceID, uint8_t* mantissa, uint8_t* exponent) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, TMGRXPREAMBLE1, &config, 1);
	*mantissa = (config & TMGRXPREAMBLE1M_MASK);
	*exponent = (config & TMGRXPREAMBLE1E_MASK) >> 5;
}

/**
  * @brief	This function sets the Recevie Preamble 2 Timeout, (TMGRXPREAMBLE2M_MASK * 2^TMGRXPREAMBLE2E_MASK us)
  * @param	interfaceID: Which interface (chip) used
  * @param	mantissa: Receive Preamble 2 Timeout Mantissa
  * @param	exponent: Receive Preamble 2 Timeout Exponent
  * @return	None
  */
void AX5043PacketSetRXPreamble2Timeout(uint8_t interfaceID, uint8_t mantissa, uint8_t exponent) {
	uint8_t config = (mantissa & TMGRXPREAMBLE2M_MASK) + ((exponent << 5) & TMGRXPREAMBLE2E_MASK);
	AX5043WriteLongAddress(interfaceID, TMGRXPREAMBLE2, &config, 1);
}

/**
  * @brief	This function gets the Receive Preamble 2 Timeout, (TMGRXPREAMBLE2M_MASK * 2^TMGRXPREAMBLE2E_MASK us)
  * @param	interfaceID: Which interface (chip) used
  * @param	mantissa: Receive Preamble 2 Timeout Mantissa return value
  * @param	exponent: Receive Preamble 2 Timeout Exponent return value
  * @return	None
  */
void AX5043PacketGetRXPreamble2Timeout(uint8_t interfaceID, uint8_t* mantissa, uint8_t* exponent) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, TMGRXPREAMBLE2, &config, 1);
	*mantissa = (config & TMGRXPREAMBLE2M_MASK);
	*exponent = (config & TMGRXPREAMBLE2E_MASK) >> 5;
}

/**
  * @brief	This function sets the Recevie Preamble 3 Timeout, (TMGRXPREAMBLE3M_MASK * 2^TMGRXPREAMBLE3E_MASK us)
  * @param	interfaceID: Which interface (chip) used
  * @param	mantissa: Receive Preamble 3 Timeout Mantissa
  * @param	exponent: Receive Preamble 3 Timeout Exponent
  * @return	None
  */
void AX5043PacketSetRXPreamble3Timeout(uint8_t interfaceID, uint8_t mantissa, uint8_t exponent) {
	uint8_t config = (mantissa & TMGRXPREAMBLE3M_MASK) + ((exponent << 5) & TMGRXPREAMBLE3E_MASK);
	AX5043WriteLongAddress(interfaceID, TMGRXPREAMBLE3, &config, 1);
}

/**
  * @brief	This function gets the Receive Preamble 3 Timeout, (TMGRXPREAMBLE3M_MASK * 2^TMGRXPREAMBLE3E_MASK us)
  * @param	interfaceID: Which interface (chip) used
  * @param	mantissa: Receive Preamble 3 Timeout Mantissa return value
  * @param	exponent: Receive Preamble 3 Timeout Exponent return value
  * @return	None
  */
void AX5043PacketGetRXPreamble3Timeout(uint8_t interfaceID, uint8_t* mantissa, uint8_t* exponent) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, TMGRXPREAMBLE3, &config, 1);
	*mantissa = (config & TMGRXPREAMBLE3M_MASK);
	*exponent = (config & TMGRXPREAMBLE3E_MASK) >> 5;
}

/**
  * @brief	This function sets the RSSI Offset, added to the RSSI value. Used to Compensate for Board Effects
  * @param	interfaceID: Which interface (chip) used
  * @param	offset: RSSI Offset Value
  * @return	None
  */
void AX5043PacketSetRSSIOffset(uint8_t interfaceID, uint8_t offset) {
	AX5043WriteLongAddress(interfaceID, RSSIREFERENCE, &offset, 1);
}

/**
  * @brief	This function gets the RSSI Offset, added to the RSSI value. Used to Compensate for Board Effects
  * @param	interfaceID: Which interface (chip) used
  * @return	RSSI Offset Value
  */
uint8_t AX5043PacketgetRSSIOffset(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, RSSIREFERENCE, &config, 1);
	return config;
}

/**
  * @brief	This function sets the RSSI Absolute Threshold, above this indicates a busy channel
  * @param	interfaceID: Which interface (chip) used
  * @param	threshold: RSSI Threshold Value
  * @return	None
  */
void AX5043PacketSetRSSIAbsThreshold(uint8_t interfaceID, uint8_t threshold) {
	AX5043WriteLongAddress(interfaceID, RSSIABSTHR, &threshold, 1);
}

/**
  * @brief	This function gets the RSSI Absolute Threshold, above this indicates a busy channel
  * @param	interfaceID: Which interface (chip) used
  * @return	RSSI Threshold Value
  */
uint8_t AX5043PacketgetRSSIAbsThreshold(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, RSSIABSTHR, &config, 1);
	return config;
}

/**
  * @brief	This function sets the Background RSSI Time Constant, BGNDRSSI = BGNDRSSI + (RSSI - BGNDRSSI) * 2^-BGNDRSSIGAIN
  * @param	interfaceID: Which interface (chip) used
  * @param	timeConstant: Background RSSI Time Constant
  * @return	None
  */
void AX5043PacketSetBGNDRSSITimeConstant(uint8_t interfaceID, uint8_t timeConstant) {
	AX5043WriteLongAddress(interfaceID, BGNDRSSIGAIN, &timeConstant, 1);
}

/**
  * @brief	This function gets the Background RSSI Time Constant, BGNDRSSI = BGNDRSSI + (RSSI - BGNDRSSI) * 2^-BGNDRSSIGAIN
  * @param	interfaceID: Which interface (chip) used
  * @return	Background RSSI Time Constant
  */
uint8_t AX5043PacketGetBGNDRSSITimeConstant(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, BGNDRSSIGAIN, &config, 1);
	return config;
}

/**
  * @brief	This function sets the RSSI Relative Threshold, RSSI Level above BGNDRSSITHR above background RSSI level indicates a busy channel
  * @param	interfaceID: Which interface (chip) used
  * @param	threshold: RSSI Threshold Value
  * @return	None
  */
void AX5043PacketSetRSSIRelativeThreshold(uint8_t interfaceID, uint8_t threshold) {
	uint8_t config = threshold & BGNDRSSITHR_MASK;
	AX5043WriteLongAddress(interfaceID, BGNDRSSITHR, &config, 1);
}

/**
  * @brief	This function gets the RSSI Relative Threshold, RSSI Level above BGNDRSSITHR above background RSSI level indicates a busy channel
  * @param	interfaceID: Which interface (chip) used
  * @return	RSSI Threshold Value
  */
uint8_t AX5043PacketGetRSSIRelativeThreshold(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, BGNDRSSITHR, &config, 1);
	return (config & BGNDRSSITHR_MASK);
}

/**
  * @brief	This function sets the maximum chunk size in the FIFO
  * @param	interfaceID: Which interface (chip) used
  * @param	packetChuckSize: Packet Chuck Size
  * @return	None
  */
void AX5043PacketSetPacketChunkSize(uint8_t interfaceID, PacketChunckSize packetChuckSize) {
	uint8_t config = packetChuckSize & PKTCHUNKSIZE_MASK;
	AX5043WriteLongAddress(interfaceID, PKTCHUNKSIZE, &config, 1);
}

/**
  * @brief	This function gets the maximum chunk size in the FIFO
  * @param	interfaceID: Which interface (chip) used
  * @return	Packet Chuck Size
  */
PacketChunckSize AX5043PacketGetPacketChunkSize(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTCHUNKSIZE, &config, 1);
	return (PacketChunckSize)(config & PKTCHUNKSIZE_MASK);
}

/**
  * @brief	This function sets the Clock Source for RSSI Settling Timeout
  * @param	interfaceID: Which interface (chip) used
  * @param	clockSource: 0 -> 1us, 1 -> Bit Clock
  * @return	None
  */
void AX5043PacketSetRSSIClockSource(uint8_t interfaceID, uint8_t clockSource) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTMISCFLAGS, &config, 1);
	config = (config & ~RXRSSICLK_MASK) | (clockSource);
	AX5043WriteLongAddress(interfaceID, PKTMISCFLAGS, &config, 1);
}

/**
  * @brief	This function gets the Clock Source for RSSI Settling Timeout
  * @param	interfaceID: Which interface (chip) used
  * @return	0 -> 1us, 1 -> Bit Clock
  */
uint8_t AX5043PacketGetRSSIClockSource(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTMISCFLAGS, &config, 1);
	return (config & RXRSSICLK_MASK);
}

/**
  * @brief	This function sets the Clock Source for AGC Settling Timeout
  * @param	interfaceID: Which interface (chip) used
  * @param	clockSource: 0 -> 1us, 1 -> Bit Clock
  * @return	None
  */
void AX5043PacketSetAGCClockSource(uint8_t interfaceID, uint8_t clockSource) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTMISCFLAGS, &config, 1);
	config = (config & ~RXAGCCLK_MASK) | (clockSource << 1);
	AX5043WriteLongAddress(interfaceID, PKTMISCFLAGS, &config, 1);
}

/**
  * @brief	This function gets the Clock Source for AGC Settling Timeout
  * @param	interfaceID: Which interface (chip) used
  * @return	0 -> 1us, 1 -> Bit Clock
  */
uint8_t AX5043PacketGetAGCClockSource(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTMISCFLAGS, &config, 1);
	return ((config & RXAGCCLK_MASK) >> 1);
}

/**
  * @brief	This function Enables Calculation of the background noise/RSSI Level
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: 1 -> Enable, 0 -> Disabled
  * @return	None
  */
void AX5043PacketEnableBGNDRSSI(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTMISCFLAGS, &config, 1);
	config = (config & ~BGNDRSSI_MASK) | (enable << 2);
	AX5043WriteLongAddress(interfaceID, PKTMISCFLAGS, &config, 1);
}

/**
  * @brief	This function gets if Calculation of the background noise/RSSI Level is Enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	If Calculation of the background noise/RSSI Level is Enabled
  */
uint8_t AX5043PacketIsEnabeldBGNDRSSI(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTMISCFLAGS, &config, 1);
	return ((config & BGNDRSSI_MASK) >> 2);
}

/**
  * @brief	This function sets AGC settling detection, if enabled terminate settling before timeout
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: 1 -> Enable, 0 -> Disabled
  * @return	None
  */
void AX5043PacketSetAGCSettlingDetection(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTMISCFLAGS, &config, 1);
	config = (config & ~AGCSETTLDET_MASK) | (enable << 3);
	AX5043WriteLongAddress(interfaceID, PKTMISCFLAGS, &config, 1);
}

/**
  * @brief	This function gets AGC settling detection, if enabled terminate settling before timeout
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> Enable, 0 -> Disabled
  */
uint8_t AX5043PacketGetAGCSettlingDetection(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTMISCFLAGS, &config, 1);
	return ((config & AGCSETTLDET_MASK) >> 3);
}

/**
  * @brief	This function set Keep Radio ON after packet is received, in wake-on-radio mode
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: 1 -> Enable, 0 -> Disabled
  * @return	None
  */
void AX5043PacketSetKeepRadiOn(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTMISCFLAGS, &config, 1);
	config = (config & ~WORMULTIPKT_MASK) | (enable << 4);
	AX5043WriteLongAddress(interfaceID, PKTMISCFLAGS, &config, 1);
}

/**
  * @brief	This function gets if Keep Radio ON after packet is received, in wake-on-radio mode, is used
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> Enable, 0 -> Disabled
  */
uint8_t AX5043PacketGetKeepRadiOn(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTMISCFLAGS, &config, 1);
	return ((config & WORMULTIPKT_MASK) >> 4);
}

/**
  * @brief	This function enables Store Timer value when a delimiter is detected
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: 1 -> Enable, 0 -> Disabled
  * @return	None
  */
void AX5043PacketEnableStoreTimerValue(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTSTOREFLAGS, &config, 1);
	config = (config & ~STTIMER_MASK) | (enable);
	AX5043WriteLongAddress(interfaceID, PKTSTOREFLAGS, &config, 1);
}

/**
  * @brief	This function gets if Store Timer value when a delimiter is detected is Enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> Enable, 0 -> Disabled
  */
uint8_t AX5043PacketIsStoreTimerValueEnabled(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTSTOREFLAGS, &config, 1);
	return (config & STTIMER_MASK);
}

/**
  * @brief	This function enables Store Frequency value at end of packet
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: 1 -> Enable, 0 -> Disabled
  * @return	None
  */
void AX5043PacketEnableStoreFrequencyValue(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTSTOREFLAGS, &config, 1);
	config = (config & ~STFOFFS_MASK) | (enable << 1);
	AX5043WriteLongAddress(interfaceID, PKTSTOREFLAGS, &config, 1);
}

/**
  * @brief	This function gets if Store Frequency value at end of packet is Enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> Enable, 0 -> Disabled
  */
uint8_t AX5043PacketIsStoreFrequencyValueEnabled(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTSTOREFLAGS, &config, 1);
	return ((config & STFOFFS_MASK) >> 1);
}

/**
  * @brief	This function enables Store RF Frequency value at end of packet
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: 1 -> Enable, 0 -> Disabled
  * @return	None
  */
void AX5043PacketEnableStoreRFFrequencyValue(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTSTOREFLAGS, &config, 1);
	config = (config & ~STRFOFFS_MASK) | (enable << 2);
	AX5043WriteLongAddress(interfaceID, PKTSTOREFLAGS, &config, 1);
}

/**
  * @brief	This function gets if Store RF Frequency value at end of packet is Enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> Enable, 0 -> Disabled
  */
uint8_t AX5043PacketIsStoreRFFrequencyValueEnabled(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTSTOREFLAGS, &config, 1);
	return ((config & STRFOFFS_MASK) >> 2);
}

/**
  * @brief	This function enables Store Datarate value at end of packet
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: 1 -> Enable, 0 -> Disabled
  * @return	None
  */
void AX5043PacketEnableStoreDatarateValue(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTSTOREFLAGS, &config, 1);
	config = (config & ~STDR_MASK) | (enable << 3);
	AX5043WriteLongAddress(interfaceID, PKTSTOREFLAGS, &config, 1);
}

/**
  * @brief	This function gets if Store Datarate value at end of packet is Enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> Enable, 0 -> Disabled
  */
uint8_t AX5043PacketIsStoreDatarateValueEnabled(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTSTOREFLAGS, &config, 1);
	return ((config & STDR_MASK) >> 3);
}

/**
  * @brief	This function enables Store RSSI at end of packet
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: 1 -> Enable, 0 -> Disabled
  * @return	None
  */
void AX5043PacketEnableStoreRSSI(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTSTOREFLAGS, &config, 1);
	config = (config & ~STRSSI_MASK) | (enable << 4);
	AX5043WriteLongAddress(interfaceID, PKTSTOREFLAGS, &config, 1);
}

/**
  * @brief	This function gets if Store RSSI at end of packet is Enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> Enable, 0 -> Disabled
  */
uint8_t AX5043PacketIsStoreRSSIEnabled(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTSTOREFLAGS, &config, 1);
	return ((config & STRSSI_MASK) >> 4);
}

/**
  * @brief	This function enables Store CRC bytes
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: 1 -> Enable, 0 -> Disabled
  * @return	None
  */
void AX5043PacketEnableStoreCRCBytes(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTSTOREFLAGS, &config, 1);
	config = (config & ~STCRCB_MASK) | (enable << 5);
	AX5043WriteLongAddress(interfaceID, PKTSTOREFLAGS, &config, 1);
}

/**
  * @brief	This function gets if Store CRC bytes is enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> Enable, 0 -> Disabled
  */
uint8_t AX5043PacketIsStoreCRCBytesEnabled(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTSTOREFLAGS, &config, 1);
	return ((config & STCRCB_MASK) >> 5);
}

/**
  * @brief	This function enables Store RSSI and Background Noise Estimate at antenna selection time
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: 1 -> Enable, 0 -> Disabled
  * @return	None
  */
void AX5043PacketEnableStoreRSSIAndBGND(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTSTOREFLAGS, &config, 1);
	config = (config & ~STANTRSSI_MASK) | (enable << 6);
	AX5043WriteLongAddress(interfaceID, PKTSTOREFLAGS, &config, 1);
}

/**
  * @brief	This function gets Store RSSI and Background Noise Estimate at antenna selection time is enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> Enable, 0 -> Disabled
  */
uint8_t AX5043PacketIsStoreRSSIAndBGNDEnabled(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTSTOREFLAGS, &config, 1);
	return ((config & STANTRSSI_MASK) >> 6);
}

/**
  * @brief	This function sets Accept Packets with non integral number of Bytes
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: 1 -> Enable, 0 -> Disabled
  * @return	None
  */
void AX5043PacketSetAcceptPacketsResidual(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTACCEPTFLAGS, &config, 1);
	config = (config & ~ACCPTRESIDUE_MASK) | (enable);
	AX5043WriteLongAddress(interfaceID, PKTACCEPTFLAGS, &config, 1);
}

/**
  * @brief	This function gets Accept Packets with non integral number of Bytes
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> Enable, 0 -> Disabled
  */
uint8_t AX5043PacketGetAcceptPacketsResidual(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTACCEPTFLAGS, &config, 1);
	return (config & ACCPTRESIDUE_MASK);
}

/**
  * @brief	This function sets Accept Abort Packets
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: 1 -> Enable, 0 -> Disabled
  * @return	None
  */
void AX5043PacketSetAcceptPacketsAborted(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTACCEPTFLAGS, &config, 1);
	config = (config & ~ACCPTABRT_MASK) | (enable << 1);
	AX5043WriteLongAddress(interfaceID, PKTACCEPTFLAGS, &config, 1);
}

/**
  * @brief	This function gets Accept Abort Packets
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> Enable, 0 -> Disabled
  */
uint8_t AX5043PacketGetAcceptPacketsAborted(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTACCEPTFLAGS, &config, 1);
	return ((config & ACCPTABRT_MASK) >> 1);
}

/**
  * @brief	This function sets Accept CRC Failed Packets
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: 1 -> Enable, 0 -> Disabled
  * @return	None
  */
void AX5043PacketSetAcceptPacketsCRCFailed(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTACCEPTFLAGS, &config, 1);
	config = (config & ~ACCPTCRCF_MASK) | (enable << 2);
	AX5043WriteLongAddress(interfaceID, PKTACCEPTFLAGS, &config, 1);
}

/**
  * @brief	This function gets Accept CRC Failed Packets
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> Enable, 0 -> Disabled
  */
uint8_t AX5043PacketGetAcceptPacketsCRCFailed(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTACCEPTFLAGS, &config, 1);
	return ((config & ACCPTCRCF_MASK) >> 2);
}

/**
  * @brief	This function sets Accept Address Failed Check Packets
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: 1 -> Enable, 0 -> Disabled
  * @return	None
  */
void AX5043PacketSetAcceptPacketsAddressFailed(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTACCEPTFLAGS, &config, 1);
	config = (config & ~ACCPTADDRF_MASK) | (enable << 3);
	AX5043WriteLongAddress(interfaceID, PKTACCEPTFLAGS, &config, 1);
}

/**
  * @brief	This function gets Accept CRC Failed Check Packets
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> Enable, 0 -> Disabled
  */
uint8_t AX5043PacketGetAcceptPacketsAddressFailed(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTACCEPTFLAGS, &config, 1);
	return ((config & ACCPTADDRF_MASK) >> 3);
}

/**
  * @brief	This function sets Accept Packets that are too long
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: 1 -> Enable, 0 -> Disabled
  * @return	None
  */
void AX5043PacketSetAcceptPacketsOverSize(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTACCEPTFLAGS, &config, 1);
	config = (config & ~ACCPTSZF_MASK) | (enable << 4);
	AX5043WriteLongAddress(interfaceID, PKTACCEPTFLAGS, &config, 1);
}

/**
  * @brief	This function gets Accept Packets that are too long
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> Enable, 0 -> Disabled
  */
uint8_t AX5043PacketGetAcceptPacketsOverSize(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTACCEPTFLAGS, &config, 1);
	return ((config & ACCPTSZF_MASK) >> 4);
}

/**
  * @brief	This function sets Accept Packets that span multiple FIFO chunks
  * @param	interfaceID: Which interface (chip) used
  * @param	enable: 1 -> Enable, 0 -> Disabled
  * @return	None
  */
void AX5043PacketSetAcceptPacketsMultiChuck(uint8_t interfaceID, uint8_t enable) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTACCEPTFLAGS, &config, 1);
	config = (config & ~ACCPTLRGP_MASK) | (enable << 5);
	AX5043WriteLongAddress(interfaceID, PKTACCEPTFLAGS, &config, 1);
}

/**
  * @brief	This function gets Accept Packets that span multiple FIFO chunks
  * @param	interfaceID: Which interface (chip) used
  * @return	1 -> Enable, 0 -> Disabled
  */
uint8_t AX5043PacketGetAcceptPacketsMultiChuck(uint8_t interfaceID) {
	uint8_t config;
	AX5043ReadLongAddress(interfaceID, PKTACCEPTFLAGS, &config, 1);
	return ((config & ACCPTLRGP_MASK) >> 5);
}
