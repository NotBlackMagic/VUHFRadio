#ifndef AX5043_AX5043_INTERFACE_H_
#define AX5043_AX5043_INTERFACE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define AX5043_MAX_INTERFACES_INSTANCES				2

typedef struct {
	uint8_t (*SPIReadWrite)(uint8_t byte);
	void (*SPICS)(uint8_t on);
} AX5043InterfaceStruct;

typedef union {
	struct {
		uint8_t deepSleep : 1;		//1 (when transitioning out of deep sleep, this bit transitions from 0 -> 1 when the power becomes ready)
		uint8_t pllLock : 1;		//PLL Lock
		uint8_t fifoOver : 1;		//FIFO Over
		uint8_t fifoUnder : 1;		//FIFO Under
		uint8_t threshFree : 1;		//Threshold Free (FIFO Free > FIFO threshold)
		uint8_t threshCnt : 1;		//Threshold Count (FIFO count > FIFO threshold)
		uint8_t fifoFull : 1;		//FIFO Full
		uint8_t fifoEmpty : 1;		//FIFO Empty
		uint8_t pwrGood : 1;		//Power Good (not Brownout)
		uint8_t pwrInt : 1;			//Power Interrupt Pending
		uint8_t radioEvent : 1;		//Radio Event Pending
		uint8_t xtalRun : 1;		//XTAL Oscillator Running
		uint8_t wakeupInt : 1;		//Wakeup Interrupt Pending
		uint8_t lposcInt : 1;		//LPOSC Interrupt Pending
		uint8_t gpadcInt : 1;		//GPADC Interrupt Pending
		uint8_t undefiend : 1;		//Undefined
	};
	uint16_t raw;
} StatusBits;

uint8_t AX5043InterfacesInit(AX5043InterfaceStruct interfaces[], uint8_t numInterfaces);
StatusBits AX5043ReadLongAddress(uint8_t interfaceID, uint16_t address, uint8_t dataIn[], uint16_t length);
StatusBits AX5043WriteLongAddress(uint8_t interfaceID, uint16_t address, uint8_t dataOut[], uint16_t length);
StatusBits AX5043ReadShortAddress(uint8_t interfaceID, uint8_t address, uint8_t dataIn[], uint16_t length);
StatusBits AX5043WriteShortAddress(uint8_t interfaceID, uint8_t address, uint8_t dataOut[], uint16_t length);

#ifdef __cplusplus
}
#endif

#endif /* AX5043_AX5043_INTERFACE_H_ */
