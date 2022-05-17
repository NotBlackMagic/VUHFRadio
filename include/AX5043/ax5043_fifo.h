#ifndef AX5043_AX5032_FIFO_H_
#define AX5043_AX5032_FIFO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ax5043_interface.h"
#include "ax5043_regs.h"

//FIFO Chunk types
//No Payload Commands
#define	FIFO_NOP					0x00	//Transmit: No Operation
//One Byte Payload Commands
#define FIFO_RSSI					0x31	//Receive: RSSI
#define FIFO_TXCTRL					0x3C	//Transmit: Transmit Control (Antenna, Power Amp)
//Two Byte Payload Commands
#define FIFO_FREQOFFS				0x52	//Receive: Frequency Offset, Payload: [FREQOFFS1][FREQOFFS0]
#define FIFO_ANTRSSI2				0x55	//Receive: Background Noise Calculation RSSI, Payload: [RSSI][BGNDNOISE]
//Three Byte Payload Commands
#define FIFO_REPEATDATA				0x62	//Transmit: Repeat Data, Payload: [Command Bits][REPEATCNT][DATA]
#define FIFO_TIMER					0x70	//Receive: Timer, Payload: [TIMER2][TIMER1][TIMER0]
#define FIFO_RFFREQOFFS				0x73	//Receive: RF Frequency Offset, Payload: [RFFREQOFFS2][RFFREQOFFS1][RFFREQOFFS0]
#define FIFO_DATARATE				0x74	//Receive: Datarate, Payload: [DATARATE2][DATARATE1][DATARATE0]
#define FIFO_ANTRSSI3				0x75	//Receive: Antenna Selection RSSI, Payload: [ANTORSSI2][ANTORSSI1][ANTORSSI0]
//Variable Length Payload Commands
#define FIFO_DATA					0xE1	//Transmit/Receive: Data, Payload: [LENGTH][Flag Bits][DATA]
#define FIFO_TXPWR					0xFD	//Transmit: Transmit Power, Payload: [LENGTH = 10][TXPWRCOEFFA (7:0)][TXPWRCOEFFA (15:8)][TXPWRCOEFFB (7:0)][TXPWRCOEFFB (15:8)][TXPWRCOEFFC (7:0)][TXPWRCOEFFC (15:8)][TXPWRCOEFFD (7:0)][TXPWRCOEFFD (15:8)][TXPWRCOEFFE (7:0)][TXPWRCOEFFE (15:8)]

//Transmit Control (Antenna, Power Amp) Command Bit Fields
#define TXCTRL_SETTX				0x40	//If set, TXSE and TXDIFF are copied into the register MODCFGA
#define TXCTRL_TXSE					0x20
#define TXCTRL_TXDIFF				0x10
#define TXCTRL_SETANT				0x08	//If set, ANTSTATE is copied into the register DIVERSITY
#define TXCTRL_ANTSTATE				0x04
#define TXCTRL_SETPA				0x02	//If set, PASTATE is copied into the register PWRAMP
#define TXCTRL_PASTATE				0x01

//Repeat Data Flag Bit Fields
#define REPEATDATA_UNENC			0x20	//Bypass Framing and encode
#define REPEATDATA_RAW				0x10	//Bypass Framing but not encode
#define REPEATDATA_NOCRC			0x08	//Surpess CRC Generation
#define REPEATDATA_RESIDUE			0x04	//Enable less the 8 bits in last byte (last bit is last high bit in last byte)
#define REPEATDATA_PKTEND			0x02	//For Data larger then FIFO: PKTEND: Radio Data End at end of this Data field
#define REPEATDATA_PKTSTART			0x01	//For Data larger then FIFO: PKTSTART: Radio Data Starts at beginning of this Data field

//FIFO Data for Transmit mode: Flag Bit Fields
#define DATA_UNENC					0x20	//Bypass Framing but not encode
#define DATA_RAW					0x10	//Bypass Framing and encode
#define DATA_NOCRC					0x08	//Surpess CRC Generation
//FIFO Data for Receive mode: Flag Bit Fields
#define DATA_ABORT					0x40	//Packet has been aborted
#define DATA_SIZEFAIL				0x20	//Packet not passed size check
#define DATA_ADDRFAIL				0x10	//Packet not passed address checks
#define DATA_CRCFAIL				0x08	//Packet not passed CRC check
//FIFO Data for Receive or Transmit mode: Flag Bit Fields
#define DATA_RESIDUE				0x04	//Enable less the 8 bits in last byte (last bit is last high bit in last byte)
#define DATA_PKTEND					0x02	//For Data larger then FIFO: PKTEND: Radio Data End at end of this Data field
#define DATA_PKTSTART				0x01	//For Data larger then FIFO: PKTSTART: Radio Data Starts at beginning of this Data field

//Register Configuration of FIFOSTAT Register
#define FIFOSTAT_MASK				0xBF	//FIFOSTAT Bit Values Mask (for FIFOStat), used when reading to FIFOSTAT
#define FIFOSTAT_CMD_MASK			0x1F	//FIFOSTAT CMD Bit mask, used when writing to FIFOSTAT
//FIFOSTAT Bits when Reading the register
typedef union {
	struct {
		uint8_t fifoEmpty : 1;				//FIFO is empty if 1. This bit is dangerous to use when PWRMODE is set to Receiver Wake-on-Radio mode.
		uint8_t fifoFull : 1;				//FIFO is full if 1
		uint8_t fifoUnder : 1;				//FIFO underrun occurred since last read of FIFOSTAT when 1
		uint8_t fifoOver : 1;				//FIFO overrun occurred since last read of FIFOSTAT when 1
		uint8_t fifoCountThreshold : 1;		//1 if the FIFO count is > FIFOTHRESH
		uint8_t fifoFreeThreshold : 1;		//1 if the FIFO free space is > FIFOTHRESH
		uint8_t none : 1;					//No valid/used bits
		uint8_t fifoAutoCommit : 1;			//If one, FIFO write bytes are automatically committed on every write
	};
	uint8_t raw;
} FIFOStat;
//FIFOSTAT CMD when writing the register
typedef enum {
	FIFOStat_NoOPeration = 0,				//No Operation
	FIFOStat_ASKCoherent = 1,				//ASK Coherent
	FIFOStat_ClearFIFOErrorFlag = 2,		//Clear FIFO Error (OVER and UNDER) Flags
	FIFOStat_ClearFIFO = 3,					//Clear FIFO Data and Flags
	FIFOStat_Commit = 4,					//Commit
	FIFOStat_Rollback = 5					//Rollback
} FIFOStatCmd;

//Register Configuration of FIFOCOUNT0 & FIFOCOUNT1 Registers
#define FIFOCOUNT0_MASK				0xFF	//FIFOCOUNT0 Bit Values Mask
#define FIFOCOUNT1_MASK				0x01	//FIFOCOUNT1 Bit Values Mask

//Register Configuration of FIFOFREE0 & FIFOFREE1 Registers
#define FIFOFREE0_MASK				0xFF	//FIFOFREE0 Bit Values Mask
#define FIFOFREE1_MASK				0x01	//FIFOFREE1 Bit Values Mask

//Register Configuration of FIFOTHRESH0 & FIFOTHRESH1 Registers
#define FIFOTHRESH0_MASK			0xFF	//FIFOTHRESH0 Bit Values Mask
#define FIFOTHRESH1_MASK			0x01	//FIFOTHRESH1 Bit Values Mask

FIFOStat AX5043FIFOGetFIFOStat(uint8_t interfaceID);
void AX5043FIFOSetFIFOStatCommand(uint8_t interfaceID, FIFOStatCmd fifoStatCommand);
void AX5043FIFOSetFIFO(uint8_t interfaceID, uint8_t *data, uint8_t length);
void AX5043FIFOGetFIFO(uint8_t interfaceID, uint8_t *data, uint8_t length);
uint16_t AX5043FIFOGetFIFOCount(uint8_t interfaceID);
uint16_t AX5043FIFOGetFIFOFree(uint8_t interfaceID);
uint16_t AX5043FIFOGetFIFOThreshold(uint8_t interfaceID);

#ifdef __cplusplus
}
#endif

#endif /* AX5043_AX5032_FIFO_H_ */
