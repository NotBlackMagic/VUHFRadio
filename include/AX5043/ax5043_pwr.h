#ifndef AX5043_AX5043_PWR_H_
#define AX5043_AX5043_PWR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ax5043_interface.h"
#include "ax5043_regs.h"

//Register Configuration of PWRMODE Register
#define PWRMODE_MASK						0x0F	//PWRMODE Bit Values Mask (for PwrModeSelection)
#define PWRMODE_WDS_MASK					0x10	//Wakeup from Deep Sleep Mask
#define PWRMODE_REFEN_MASK					0x20	//Reference Enable; set to 1 to power the internal reference circuitry
#define PWRMODE_XOEN_MASK					0x40	//Crystal Oscillator Enable
#define PWRMODE_RST_MASK					0x80	//Reset: Setting this bit to 1 resets the whole chip. This bit does not auto-reset: the chip remains in reset state until this bit is cleared.
//PWRMODE Bits
typedef enum {
	PwrMode_Powerdown = 0,				//Powerdown: All circuits powered down
	PwrMode_DeepSleep = 1,				//Deep Sleep Mode: Chip is fully powered down until SEL is lowered again; looses all register contents
	PwrMode_Standby = 5,				//Crystal Oscillator enabled
	PwrMode_FIFOEN = 7,					//FIFO enabled
	PwrMode_SytnhRXEN = 8,				//Synthesizer running, Receive Mode
	PwrMode_RXEN = 9,					//Receiver Running
	PwrMode_RXWakeOnRadioMode = 11,		//Receiver Wake-on-Radio Mode
	PwrMode_SynthTXEN = 12,				//Synthesizer running, Transmit Mode
	PwrMode_TXEN = 13					//Transmitter Running
} PwrModeSelection;

//Register Configuration of POWSTAT & POWSTICKYSTAT Register
//POWSTAT & POWSTICKYSTAT Bits
typedef union {
	struct {
		uint8_t svio : 1;				//(Sticky) IO Voltage Large Enough (not Brownout)
		uint8_t sbevmodem : 1;			//(Sticky) Modem Domain Voltage Brownout Error (Inverted; 0 = Brownout, 1 = Power OK)
		uint8_t sbevana : 1;			//(Sticky) Analog Domain Voltage Brownout Error (Inverted; 0 = Brownout, 1 = Power OK)
		uint8_t svmodem : 1;			//(Sticky) Modem Domain Voltage Regulator Ready
		uint8_t svana : 1;				//(Sticky) Analog Domain Voltage Regulator Ready
		uint8_t svref : 1;				//(Sticky) Reference Voltage Regulator Ready
		uint8_t sref : 1;				//(Sticky) Reference Ready
		uint8_t ssum : 1;				//(Sticky) Summary Ready Status (one when all unmasked POWIRQMASK power sources are ready)
	};
	uint8_t raw;
} PwrStatus;

//Register Configuration of POWIRQMASK Register
//POWIRQMASK Bits
typedef union {
	struct {
		uint8_t msvio : 1;				//IO Voltage Large Enough (not Brownout) Interrupt Mask
		uint8_t msbevmodem : 1;			//Modem Domain Voltage Brownout Error Interrupt Mask
		uint8_t msbevana : 1;			//Analog Domain Voltage Brownout Error Interrupt Mask
		uint8_t msvmodem : 1;			//Modem Domain Voltage Regulator Ready Interrupt Mask
		uint8_t msvana : 1;				//Analog Domain Voltage Regulator Ready Interrupt Mask
		uint8_t msvref : 1;				//Reference Voltage Regulator Ready Interrupt Mask
		uint8_t msref : 1;				//Reference Ready Interrupt Mask
		uint8_t mpwrgood : 1;			//If 0, interrupt whenever one of the unmasked power sources fail (clear interrupt by reading POWSTICKYSTAT); if 1, interrupt when all unmasked power sources are good
	};
	uint8_t raw;
} PwrIRQMask;

void AX5043PwrSetPowerMode(uint8_t interfaceID, PwrModeSelection pwrMode);
PwrModeSelection AX5043PwrGetPowerMode(uint8_t interfaceID);
void AX5043PwrSetEnableReference(uint8_t interfaceID, uint8_t enableRef);
uint8_t AX5043PwrGetEnableReference(uint8_t interfaceID);
void AX5043PwrSetEnableXO(uint8_t interfaceID, uint8_t enableXO);
uint8_t AX5043PwrGetEnableXO(uint8_t interfaceID);
void AX5043PwrReset(uint8_t interfaceID);
PwrStatus AX5043PwrStats(uint8_t interfaceID);
PwrStatus AX5043PwrStickyStats(uint8_t interfaceID);
void AX5043PwrSetIRQMask(uint8_t interfaceID, PwrIRQMask irqMask);
PwrIRQMask AX5043PwrGetIRQMask(uint8_t interfaceID);

#ifdef __cplusplus
}
#endif

#endif /* AX5043_AX5043_PWR_H_ */
