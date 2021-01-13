#ifndef AX5043_AX5043_PACKET_H_
#define AX5043_AX5043_PACKET_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ax5043_interface.h"
#include "ax5043_regs.h"

//Registers Configuration of ENCODING
#define ENCINV_MASK							0x01	//Invert data if set to 1
#define ENCDIFF_MASK						0x02	//Differential encode/decode data if set to 1
#define ENCSCRAM_MASK						0x04	//Enable scramble/descramble if set to 1
#define ENCMNACH_MASK						0x08	//Enable manchester encoding/decoding. FM0/FM1 may be achieved by also appropriately setting ENC DIFF and ENC INV
#define ENCNOSYNC_MASK						0x10	//Disable Dibit synchronization in 4-FSK mode

//Registers Configuration of FRAMING
#define FABORT_MASK							0x01	//Write 1 to abort current HDLC[1] packet/pattern match
#define FRMMODE_MASK						0x0E	//Frame Mode Bit Values Mask
#define CRCMODE_MASK						0x70	//CRC Mode Bit Values Mask
#define FRMRX_MASK							0x80	//Packet start detected: set when a flag is detected in HDLC[1] mode or preamble match in RAW pattern match mode
//FRMMODE Bits
typedef enum {
	FrmMode_Raw = 0,
	FrmMode_RawSoftBits = 1,
	FrmMode_HDLC = 2,
	FrmMode_RawPatternMatch = 3,
	FrmMode_WMBUS = 4,
	FrmMode_WMBUS4to6 = 5
} FrmMode;
//CRCMODE Bits
typedef enum {
	CRCMode_Off = 0,
	CRCMode_CCITT = 1,
	CRCMode_CRC16 = 2,
	CRCMode_DNP = 3,
	CRCMode_CRC32 = 6
} CRCMode;

//Register Configuration of CRCINIT Register
#define CRCINIT0_MASK						0xFF	//CRC reset value; normally all 1's
#define CRCINIT1_MASK						0xFF	//CRC reset value; normally all 1's
#define CRCINIT2_MASK						0xFF	//CRC reset value; normally all 1's
#define CRCINIT3_MASK						0xFF	//CRC reset value; normally all 1's

//Register Configuration of FEC Register
#define FECENA_MASK							0x01	//Enable FEC (Convolutional Encoder)
#define FECINPSHIFT_MASK					0x0E	//Attenuate soft RX data by 2^-FECINPSHIFT
#define FECPOS_MASK							0x10	//Enable noninverted interleave synchronization
#define FECNEG_MASK							0x20	//Enable inverted interleave synchronization
#define RSTVITERBI_MASK						0x40	//Reset Viterbi decoder
#define SHORTMEM_MASK						0x80	//Shorten backtrack memory

//Register Configuration of FECSYNC Register
#define FECSYNC_MASK						0xFF	//Interleaver synchronization threshold

//Register Configuration of FECSTATUS Register
#define MAXMETRIC_MASK						0x7F	//Metric increment of the survivor path
#define FECINV_MASK							0x80	//Inverted synchronization sequence received

//Register Configuration of PKTADDRCFG Register
#define ADDRPOS_MASK						0x0F	//Position of the address bytes Mask
#define FECSYNCDIS_MASK						0x20	//When set, disable FEC sync search during packet reception Mask
#define CRCSKIPFIRST_MASK					0x40	//When set, the first byte of the packet is not included in the CRC calculation Mask
#define MSBFIRST_MASK						0x80	//When set, each byte is sent MSB first; when cleared, each byte is sent LSB first Mask

//Register Configuration of PKTLENCFG Register
#define LENPOS_MASK							0x0F	//Position of the length byte Mask
#define LENBITS_MASK						0xF0	//Number of significant bits in the length byte Mask

//Register Configuration of PKTLENOFFSET Register
#define LENOFFSET_MASK						0xFF	//Packet Length Offset Mask

//Register Configuration of PKTMAXLEN Register
#define MAXLEN_MASK							0xFF	//Packet Maximum Length Mask

//Register Configuration of PKTADDR Register
#define PKTADDR0_MASK						0xFF	//Packet Address Mask
#define PKTADDR1_MASK						0xFF	//Packet Address Mask
#define PKTADDR2_MASK						0xFF	//Packet Address Mask
#define PKTADDR3_MASK						0xFF	//Packet Address Mask

//Register Configuration of PKTADDRMASK Register
#define PKTADDRMASK0_MASK					0xFF	//Packet Address Mask Mask
#define PKTADDRMASK1_MASK					0xFF	//Packet Address Mask Mask
#define PKTADDRMASK2_MASK					0xFF	//Packet Address Mask Mask
#define PKTADDRMASK3_MASK					0xFF	//Packet Address Mask Mask

//Register Configuration of MATCH0PAT Register
#define MATCH0PAT0_MASK						0xFF	//Pattern for Match Unit 0; LSB is received first; patterns of length less than 32 must be MSB aligned
#define MATCH0PAT1_MASK						0xFF	//Pattern for Match Unit 0; LSB is received first; patterns of length less than 32 must be MSB aligned
#define MATCH0PAT2_MASK						0xFF	//Pattern for Match Unit 0; LSB is received first; patterns of length less than 32 must be MSB aligned
#define MATCH0PAT3_MASK						0xFF	//Pattern for Match Unit 0; LSB is received first; patterns of length less than 32 must be MSB aligned

//Register Configuration of MATCH0LEN Register
#define MATCH0LEN_MASK						0x1F	//Pattern Length for Match Unit 0; The length in bits of the pattern is MATCH0LEN + 1
#define MATCH0RAW_MASK						0x80	//Select whether Match Unit 0 operates on decoded (afterManchester, Descrambler etc.) (if 0), or on raw received bits (if 1)

//Register Configuration of MATCH0MIN Register
#define MATCH0MIN_MASK						0x1F	//A match is signalled if the received bitstream matches the pattern in less than MATCH0MIN positions. This can be used to detect inverted sequences.

//Register Configuration of MATCH0MAX Register
#define MATCH0MAX_MASK						0x1F	//A match is signalled if the received bitstream matches the pattern in more than MATCH0MAX positions

//Register Configuration of MATCH1PAT Register
#define MATCH1PAT0_MASK						0xFF	//Pattern for Match Unit 1; LSB is received first; patterns of length less than 16 must be MSB aligned
#define MATCH1PAT1_MASK						0xFF	//Pattern for Match Unit 1; LSB is received first; patterns of length less than 16 must be MSB aligned

//Register Configuration of MATCH1LEN Register
#define MATCH1LEN_MASK						0x0F	//Pattern Length for Match Unit 1; The length in bits of the pattern is MATCH1LEN + 1
#define MATCH1RAW_MASK						0x80	//Select whether Match Unit 1 operates on decoded (after Manchester, Descrambler etc.) (if 0), or on raw received bits (if 1)

//Register Configuration of MATCH1MIN Register
#define MATCH1MIN_MASK						0x0F	//A match is signalled if the received bitstream matches the pattern in less than MATCH1MIN positions. This can be used to detect inverted sequences

//Register Configuration of MATCH1MAX Register
#define MATCH1MAX_MASK						0x0F	//A match is signalled if the received bitstream matches the pattern in more than MATCH1MAX positions

//Register Configuration of TMGTXBOOST Register
#define TMGTXBOOSTM_MASK					0x1F	//Transmit PLL Boost Time Mantissa Mask, PLL Boost time is TMGTXBOOSTM * 2^TMGTXBOOSTE us
#define TMGTXBOOSTE_MASK					0xE0	//Transmit PLL Boost Time Exponent Mask, PLL Boost time is TMGTXBOOSTM * 2^TMGTXBOOSTE us

//Register Configuration of TMGTXSETTLE Register
#define TMGTXSETTLEM_MASK					0x1F	//Transmit PLL (post Boost) Settling Time Mantissa Mask, PLL post boost settling time is TMGTXSETTLEM * 2^TMGTXSETTLEE us
#define TMGTXSETTLEE_MASK					0xE0	//Transmit PLL (post Boost) Settling Time Exponent Mask, PLL post boost settling time is TMGTXSETTLEM * 2^TMGTXSETTLEE us

//Register Configuration of TMGRXBOOST Register
#define TMGRXBOOSTM_MASK					0x1F	//Transmit PLL Boost Time Mantissa Mask, PLL Boost time is TMGTXBOOSTM * 2^TMGTXBOOSTE us
#define TMGRXBOOSTE_MASK					0xE0	//Transmit PLL Boost Time Exponent Mask, PLL Boost time is TMGTXBOOSTM * 2^TMGTXBOOSTE us

//Register Configuration of TMGRXSETTLE Register
#define TMGRXSETTLEM_MASK					0x1F	//Receive PLL (post Boost) Settling Time Mantissa Mask, Receive PLL post boost settling time is TMGRXSETTLEM * 2^TMGRXSETTLEE us
#define TMGRXSETTLEE_MASK					0xE0	//Receive PLL (post Boost) Settling Time Exponent Mask, Receive PLL post boost settling time is TMGRXSETTLEM * 2^TMGRXSETTLEE us

//Register Configuration of TMGRXOFFSACQ Register
#define TMGRXOFFSACQM_MASK					0x1F	//Baseband DC Offset Acquisition Time Mantissa Mask, Baseband DC Offset Acquisition Time is TMGRXOFFSACQM * 2^TMGRXOFFSACQE us
#define TMGRXOFFSACQE_MASK					0xE0	//Baseband DC Offset Acquisition Time Exponent Mask, Baseband DC Offset Acquisition Time is TMGRXOFFSACQM * 2^TMGRXOFFSACQE us

//Register Configuration of TMGRXCOARSEAGC Register
#define TMGRXCOARSEAGCM_MASK				0x1F	//Receive Coarse AGC Time Mantissa Mask, Receive Coarse AGC Time is TMGRXCOARSEAGCM * 2^TMGRXCOARSEAGCE us
#define TMGRXCOARSEAGCE_MASK				0xE0	//Receive Coarse AGC Time Exponent Mask, Receive Coarse AGC Time is TMGRXCOARSEAGCM * 2^TMGRXCOARSEAGCE us

//Register Configuration of TMGRXAGC Register
#define TMGRXAGCM_MASK						0x1F	//Receiver AGC Settling Time Mantissa Mask, Receive AGC Settling Time is TMGRXAGCM * 2^TMGRXAGCE us
#define TMGRXAGCE_MASK						0xE0	//Receiver AGC Settling Time Exponent Mask, Receive AGC Settling Time is TMGRXAGCM * 2^TMGRXAGCE us

//Register Configuration of TMGRXRSSI Register
#define TMGRXRSSIM_MASK						0x1F	//Receiver RSSI Settling Time Mantissa Mask, Receive RSSI Settling Time is TMGRXRSSIM * 2^TMGRXRSSIE us
#define TMGRXRSSIE_MASK						0xE0	//Receiver RSSI Settling Time Exponent Mask, Receive RSSI Settling Time is TMGRXRSSIM * 2^TMGRXRSSIE us

//Register Configuration of TMGRXPREAMBLE1 Register
#define TMGRXPREAMBLE1M_MASK				0x1F	//Receiver Preamble 1 Timeout Mantissa Mask, Recevie Preamble 1 Timeout is TMGRXPREAMBLE1M * 2^TMGRXPREAMBLE1E bits
#define TMGRXPREAMBLE1E_MASK				0xE0	//Receiver Preamble 1 Timeout Exponent Mask, Recevie Preamble 1 Timeout is TMGRXPREAMBLE1M * 2^TMGRXPREAMBLE1E bits

//Register Configuration of TMGRXPREAMBLE2 Register
#define TMGRXPREAMBLE2M_MASK				0x1F	//Receiver Preamble 2 Timeout Mantissa Mask, Recevie Preamble 2 Timeout is TMGRXPREAMBLE2M * 2^TMGRXPREAMBLE2E bits
#define TMGRXPREAMBLE2E_MASK				0xE0	//Receiver Preamble 2 Timeout Exponent Mask, Recevie Preamble 2 Timeout is TMGRXPREAMBLE2M * 2^TMGRXPREAMBLE2E bits

//Register Configuration of TMGRXPREAMBLE3 Register
#define TMGRXPREAMBLE3M_MASK				0x1F	//Receiver Preamble 3 Timeout Mantissa Mask, Recevie Preamble 3 Timeout is TMGRXPREAMBLE3M * 2^TMGRXPREAMBLE3E bits
#define TMGRXPREAMBLE3E_MASK				0xE0	//Receiver Preamble 3 Timeout Exponent Mask, Recevie Preamble 3 Timeout is TMGRXPREAMBLE3M * 2^TMGRXPREAMBLE3E bits

//Register Configuration of RSSIREFERENCE Register
#define RSSIREFERENCE_MASK					0xFF	//RSSI Offset Mask

//Register Configuration of RSSIABSTHR Register
#define RSSIABSTHR_MASK						0xFF	//RSSI Absolute Threshold Mask

//Register Configuration of BGNDRSSIGAIN Register
#define BGNDRSSIGAIN_MASK					0x0F	//Background RSSI Averaging Time Constant Mask

//Register Configuration of BGNDRSSITHR Register
#define BGNDRSSITHR_MASK					0x3F	//Background RSSI Relative Threshold Mask

//Register Configuration of PKTCHUNKSIZE Register
#define PKTCHUNKSIZE_MASK					0x0F	//Maximum Packet Chunk Size Mask (for PacketChunckSize)
//PKTCHUNKSIZE Bits
typedef enum {
	PacketChunkSize_1byte = 1,
	PacketChunkSize_2byte = 2,
	PacketChunkSize_4byte = 3,
	PacketChunkSize_8byte = 4,
	PacketChunkSize_16byte = 5,
	PacketChunkSize_32byte = 6,
	PacketChunkSize_64byte = 7,
	PacketChunkSize_96byte = 8,
	PacketChunkSize_128byte = 9,
	PacketChunkSize_160byte = 10,
	PacketChunkSize_192byte = 11,
	PacketChunkSize_224byte = 12,
	PacketChunkSize_240byte = 13

} PacketChunckSize;

//Register Configuration of PKTMISCFLAGS Register
#define RXRSSICLK_MASK						0x01	//Clock source for RSSI settling timeout: 0 = 1 us, 1 = Bit clock
#define RXAGCCLK_MASK						0x02	//Clock source for AGC settling timeout: 0 = 1 us, 1 = Bit clock
#define BGNDRSSI_MASK						0x04	//If 1, enable the calculation of the background noise/RSSI level
#define AGCSETTLDET_MASK					0x08	//If 1, if AGC settling is detected, terminate settling before timeout
#define WORMULTIPKT_MASK					0x10	//If 1, the receiver continues to be on after a packet is received in wake-on-radio mode; otherwise, it is shut dow

//Register Configuration of PKTSTOREFLAGS Register
#define STTIMER_MASK						0x01	//Store Timer value when a delimiter is detected
#define STFOFFS_MASK						0x02	//Store Frequency offset at end of packet
#define STRFOFFS_MASK						0x04	//Store RF Frequency offset at end of packet
#define STDR_MASK							0x08	//Store Datarate offset at end of packet
#define STRSSI_MASK							0x10	//Store RSSI at end of packet
#define STCRCB_MASK							0x20	//Store CRC Bytes. Normally, CRC bytes are discarded after checking. In HDLC [1] mode, CRC bytes are always stored, regardless of this bit
#define STANTRSSI_MASK						0x40	//Store RSSI and Background Noise Estimate at antenna selection time

//Register Configuration of PKTACCEPTFLAGS Register
#define ACCPTRESIDUE_MASK					0x01	//Accept Packets with a nonintegral number of Bytes (HDLC [1] only)
#define ACCPTABRT_MASK						0x02	//Accept aborted Packets
#define ACCPTCRCF_MASK						0x04	//Accept Packets that fail CRC check
#define ACCPTADDRF_MASK						0x08	//Accept Packets that fail Address check
#define ACCPTSZF_MASK						0x10	//Accept Packets that are too long
#define ACCPTLRGP_MASK						0x20	//Accept Packets that span multiple FIFO chunks

void AX5043PacketEnableEncodeBitInversion(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043PacketIsEncodeBitInversionEnabled(uint8_t interfaceID);
void AX5043PacketEnableEncodeDifferential(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043PacketIsEncodeDifferentialEnabled(uint8_t interfaceID);
void AX5043PacketEnableEncodeScramble(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043PacketIsEncodeScrambleEnabled(uint8_t interfaceID);
void AX5043PacketEnableEncodeManchester(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043PacketIsEncodManchesterEnabled(uint8_t interfaceID);
void AX5043PacketDisableEncodeDibit(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043PacketIsEncodeDibitDisabled(uint8_t interfaceID);
void AX5043PacketAbortPatternMatch(uint8_t interfaceID);
void AX5043PacketSetFrameMode(uint8_t interfaceID, FrmMode frameMode);
FrmMode AX5043PacketGetFrameMode(uint8_t interfaceID);
void AX5043PacketSetCRCMode(uint8_t interfaceID, CRCMode frameMode);
CRCMode AX5043PacketGetCRCMode(uint8_t interfaceID);
uint8_t AX5043PacketPacketStartDetected(uint8_t interfaceID);
void AX5043PacketSetCRCInitValue(uint8_t interfaceID, uint32_t crcInit);
uint32_t AX5043PacketGetCRCInitValue(uint8_t interfaceID);
void AX5043PacketEnableFEC(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043PacketIsFECEnabled(uint8_t interfaceID);
void AX5043PacketSetFECInputShift(uint8_t interfaceID, uint8_t inputShift);
uint8_t AX5043PacketGetFECInputShift(uint8_t interfaceID);
void AX5043PacketEnableFECNonInvInterleave(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043PacketIsFECNonInvInterleaveEnabled(uint8_t interfaceID);
void AX5043PacketEnableFECInvInterleave(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043PacketIsFECInvInterleaveEnabled(uint8_t interfaceID);
void AX5043PacketResetViterbiDecoder(uint8_t interfaceID);
void AX5043PacketEnableShortenBacktrack(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043PacketIsShortenBacktrackEnabled(uint8_t interfaceID);
void AX5043PacketSetFECSync(uint8_t interfaceID, uint8_t fecSync);
uint8_t AX5043PacketGetFECSync(uint8_t interfaceID);
uint8_t AX5043PacketGetMetricIncrementSurvivorPath(uint8_t interfaceID);
uint8_t AX5043PacketGetInvertedSyncSeqReceived(uint8_t interfaceID);
void AX5043PacketSetAddressBytesPosition(uint8_t interfaceID, uint8_t position);
uint8_t AX5043PacketGetAddressBytesPosition(uint8_t interfaceID);
void AX5043PacketDisableFECSync(uint8_t interfaceID, uint8_t disable);
uint8_t AX5043PacketIfFECSyncDisabled(uint8_t interfaceID);
void AX5043PacketSetSkipFirstByteCRC(uint8_t interfaceID, uint8_t skip);
uint8_t AX5043PacketGetSkipFirstByteCRC(uint8_t interfaceID);
void AX5043PacketSetMSBFirst(uint8_t interfaceID, uint8_t msbFirst);
uint8_t AX5043PacketGetMSBFirst(uint8_t interfaceID);
void AX5043PacketSetLengthBytesPosition(uint8_t interfaceID, uint8_t position);
uint8_t AX5043PacketGetLengthBytesPosition(uint8_t interfaceID);
void AX5043PacketSetLengthByteSignificantBits(uint8_t interfaceID, uint8_t significantBits);
uint8_t AX5043PacketGetLengthByteSignificantBits(uint8_t interfaceID);
void AX5043PacketSetLengthOffset(uint8_t interfaceID, uint8_t offset);
uint8_t AX5043PacketGetLengthOffset(uint8_t interfaceID);
void AX5043PacketSetMaxLength(uint8_t interfaceID, uint8_t length);
uint8_t AX5043PacketGetMaxLength(uint8_t interfaceID);
void AX5043PacketSetAddress(uint8_t interfaceID, uint32_t address);
uint32_t AX5043PacketGetAddress(uint8_t interfaceID);
void AX5043PacketSetAddressMask(uint8_t interfaceID, uint32_t addressMask);
uint32_t AX5043PacketGetAddressMask(uint8_t interfaceID);
void AX5043PacketSetPaternMatch0(uint8_t interfaceID, uint32_t paternMatch);
uint32_t AX5043PacketGetPaternMatch0(uint8_t interfaceID);
void AX5043PacketSetPaternLength0(uint8_t interfaceID, uint8_t length);
uint8_t AX5043PacketGetPaternLength0(uint8_t interfaceID);
void AX5043PacketSetPaternMatch0Raw(uint8_t interfaceID, uint8_t raw);
uint8_t AX5043PacketGetPaternMatch0Raw(uint8_t interfaceID);
void AX5043PacketSetPaternMatch0Min(uint8_t interfaceID, uint8_t minimum);
uint8_t AX5043PacketGetPaternMatch0Min(uint8_t interfaceID);
void AX5043PacketSetPaternMatch0Max(uint8_t interfaceID, uint8_t minimum);
uint8_t AX5043PacketGetPaternMatch0Max(uint8_t interfaceID);
void AX5043PacketSetPaternMatch1(uint8_t interfaceID, uint16_t paternMatch);
uint16_t AX5043PacketGetPaternMatch1(uint8_t interfaceID);
void AX5043PacketSetPaternLength1(uint8_t interfaceID, uint8_t length);
uint8_t AX5043PacketGetPaternLength1(uint8_t interfaceID);
void AX5043PacketSetPaternMatch1Raw(uint8_t interfaceID, uint8_t raw);
uint8_t AX5043PacketGetPaternMatch1Raw(uint8_t interfaceID);
void AX5043PacketSetPaternMatch1Min(uint8_t interfaceID, uint8_t minimum);
uint8_t AX5043PacketGetPaternMatch1Min(uint8_t interfaceID);
void AX5043PacketSetPaternMatch1Max(uint8_t interfaceID, uint8_t minimum);
uint8_t AX5043PacketGetPaternMatch1Max(uint8_t interfaceID);
void AX5043PacketSetTXPLLBoostTime(uint8_t interfaceID, uint8_t mantissa, uint8_t exponent);
void AX5043PacketGetTXPLLBoostTime(uint8_t interfaceID, uint8_t* mantissa, uint8_t* exponent);
void AX5043PacketSetTXPLLSettlingTime(uint8_t interfaceID, uint8_t mantissa, uint8_t exponent);
void AX5043PacketGetTXPLLSettlingTime(uint8_t interfaceID, uint8_t* mantissa, uint8_t* exponent);
void AX5043PacketSetRXPLLBoostTime(uint8_t interfaceID, uint8_t mantissa, uint8_t exponent);
void AX5043PacketGetRXPLLBoostTime(uint8_t interfaceID, uint8_t* mantissa, uint8_t* exponent);
void AX5043PacketSetRXPLLSettlingTime(uint8_t interfaceID, uint8_t mantissa, uint8_t exponent);
void AX5043PacketGetRXPLLSettlingTime(uint8_t interfaceID, uint8_t* mantissa, uint8_t* exponent);
void AX5043PacketSetRXDCOffsetAcquisitionTime(uint8_t interfaceID, uint8_t mantissa, uint8_t exponent);
void AX5043PacketGetRXDCOffsetAcquisitionTime(uint8_t interfaceID, uint8_t* mantissa, uint8_t* exponent);
void AX5043PacketSetRXCoarseAGCTime(uint8_t interfaceID, uint8_t mantissa, uint8_t exponent);
void AX5043PacketGetRXCoarseAGCTime(uint8_t interfaceID, uint8_t* mantissa, uint8_t* exponent);
void AX5043PacketSetRXAGCSettlingTime(uint8_t interfaceID, uint8_t mantissa, uint8_t exponent);
void AX5043PacketGetRXAGCSettlingTime(uint8_t interfaceID, uint8_t* mantissa, uint8_t* exponent);
void AX5043PacketSetRXRSSISettlingTime(uint8_t interfaceID, uint8_t mantissa, uint8_t exponent);
void AX5043PacketGetRXRSSISettlingTime(uint8_t interfaceID, uint8_t* mantissa, uint8_t* exponent);
void AX5043PacketSetRXPreamble1Timeout(uint8_t interfaceID, uint8_t mantissa, uint8_t exponent);
void AX5043PacketGetRXPreamble1Timeout(uint8_t interfaceID, uint8_t* mantissa, uint8_t* exponent);
void AX5043PacketSetRXPreamble2Timeout(uint8_t interfaceID, uint8_t mantissa, uint8_t exponent);
void AX5043PacketGetRXPreamble2Timeout(uint8_t interfaceID, uint8_t* mantissa, uint8_t* exponent);
void AX5043PacketSetRXPreamble3Timeout(uint8_t interfaceID, uint8_t mantissa, uint8_t exponent);
void AX5043PacketGetRXPreamble3Timeout(uint8_t interfaceID, uint8_t* mantissa, uint8_t* exponent);
void AX5043PacketSetRSSIOffset(uint8_t interfaceID, uint8_t offset);
uint8_t AX5043PacketGetRSSIOffset(uint8_t interfaceID);
void AX5043PacketSetRSSIAbsThreshold(uint8_t interfaceID, uint8_t threshold);
uint8_t AX5043PacketGetRSSIAbsThreshold(uint8_t interfaceID);
void AX5043PacketSetBGNDRSSITimeConstant(uint8_t interfaceID, uint8_t timeConstant);
uint8_t AX5043PacketGetBGNDRSSITimeConstant(uint8_t interfaceID);
void AX5043PacketSetRSSIRelativeThreshold(uint8_t interfaceID, uint8_t threshold);
uint8_t AX5043PacketGetRSSIRelativeThreshold(uint8_t interfaceID);
void AX5043PacketSetPacketChunkSize(uint8_t interfaceID, PacketChunckSize packetChuckSize);
PacketChunckSize AX5043PacketGetPacketChunkSize(uint8_t interfaceID);
void AX5043PacketSetRSSIClockSource(uint8_t interfaceID, uint8_t clockSource);
uint8_t AX5043PacketGetRSSIClockSource(uint8_t interfaceID);
void AX5043PacketSetAGCClockSource(uint8_t interfaceID, uint8_t clockSource);
uint8_t AX5043PacketGetAGCClockSource(uint8_t interfaceID);
void AX5043PacketEnableBGNDRSSI(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043PacketIsEnabeldBGNDRSSI(uint8_t interfaceID);
void AX5043PacketSetAGCSettlingDetection(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043PacketGetAGCSettlingDetection(uint8_t interfaceID);
void AX5043PacketSetKeepRadiOn(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043PacketGetKeepRadiOn(uint8_t interfaceID);
void AX5043PacketEnableStoreTimerValue(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043PacketIsStoreTimerValueEnabled(uint8_t interfaceID);
void AX5043PacketEnableStoreFrequencyValue(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043PacketIsStoreFrequencyValueEnabled(uint8_t interfaceID);
void AX5043PacketEnableStoreRFFrequencyValue(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043PacketIsStoreRFFrequencyValueEnabled(uint8_t interfaceID);
void AX5043PacketEnableStoreDatarateValue(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043PacketIsStoreDatarateValueEnabled(uint8_t interfaceID);
void AX5043PacketEnableStoreRSSI(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043PacketIsStoreRSSIEnabled(uint8_t interfaceID);
void AX5043PacketEnableStoreCRCBytes(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043PacketIsStoreCRCBytesEnabled(uint8_t interfaceID);
void AX5043PacketEnableStoreRSSIAndBGND(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043PacketIsStoreRSSIAndBGNDEnabled(uint8_t interfaceID);
void AX5043PacketSetAcceptPacketsResidual(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043PacketGetAcceptPacketsResidual(uint8_t interfaceID);
void AX5043PacketSetAcceptPacketsAborted(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043PacketGetAcceptPacketsAborted(uint8_t interfaceID);
void AX5043PacketSetAcceptPacketsCRCFailed(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043PacketGetAcceptPacketsCRCFailed(uint8_t interfaceID);
void AX5043PacketSetAcceptPacketsAddressFailed(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043PacketGetAcceptPacketsAddressFailed(uint8_t interfaceID);
void AX5043PacketSetAcceptPacketsOverSize(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043PacketGetAcceptPacketsOverSize(uint8_t interfaceID);
void AX5043PacketSetAcceptPacketsMultiChuck(uint8_t interfaceID, uint8_t enable);
uint8_t AX5043PacketGetAcceptPacketsMultiChuck(uint8_t interfaceID);

#ifdef __cplusplus
}
#endif

#endif /* AX5043_AX5043_PACKET_H_ */
