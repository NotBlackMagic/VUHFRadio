#ifndef AX5043_AX5043_IRQ_H_
#define AX5043_AX5043_IRQ_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ax5043_interface.h"
#include "ax5043_regs.h"

//Register Configuration of IRQMASK0 & IRQMASK1 Register
#define IRQMASK0_MASK							0xFF		//IRQMASK0 Bit Values Mask (for IrqMask)
#define IRQMASK1_MASK							0x1F		//IRQMASK1 Bit Values Mask (for IrqMask)
//IRQMASK0 & IRQMASK1 Bits
typedef union {
	struct {
		uint8_t irqmfifonotempty : 1;	//FIFO not empty interrupt enable
		uint8_t irqmfifonotfull : 1;	//FIFO not full interrupt enable
		uint8_t irqmfifothrcnt : 1;		//FIFO count > threshold interrupt enable
		uint8_t irqmfifothrfree : 1;	//FIFO free > threshold interrupt enable
		uint8_t irqmfifoerror : 1;		//FIFO error interrupt enable
		uint8_t irqmpllunlock : 1;		//PLL lock lost interrupt enable
		uint8_t irqmradioctrl : 1;		//Radio Controller interrupt enable
		uint8_t irqmpower : 1;			//Power interrupt enable
		uint8_t irqmxtalready : 1;		//Crystal Oscillator Ready interrupt enable
		uint8_t irqmwakeuptimer : 1;	//Wakeup Timer interrupt enable
		uint8_t irqmlposc : 1;			//Low Power Oscillator interrupt enable
		uint8_t irqmgpadc : 1;			//GPADC interrupt enable
		uint8_t irqmpllrngdone : 1;		//PLL autoranging done interrupt enable
		uint8_t irqmnone : 3;			//No valid/used bits
	};
	uint16_t raw;
} IrqMask;

//Register Configuration of RADIOEVENTMASK0 & RADIOEVENTMASK1 Register
#define RADIOEVENTMASK0_MASK					0xFF		//RADIOEVENTMASK0 Bit Values Mask (for IrqMask)
#define RADIOEVENTMASK1_MASK					0x01		//RADIOEVENTMASK1 Bit Values Mask (for IrqMask)
//RADIOEVENTMASK0 & RADIOEVENTMASK1 Bits
typedef union {
	struct {
		uint8_t revmdone : 1;			//Transmit or Receive Done Radio Event Enable
		uint8_t revmsettled : 1;		//PLL Settled Radio Event Enable
		uint8_t revmradiostatechg : 1;	//Radio State Changed Event Enable
		uint8_t revmrxparamsetchg : 1;	//Receiver Parameter Set Changed Event Enable
		uint8_t revmframeclk : 1;		//Frame Clock Event Enable
		uint16_t revmnone : 11;			//No valid/used bits
	};
	uint16_t raw;
} RadioEventMask;

//Register Configuration of IRQINVERSION0 & IRQINVERSION1 Register
#define IRQINVERSION0_MASK						0xFF		//IRQINVERSION0 Bit Values Mask (for IrqInversion)
#define IRQINVERSION1_MASK						0x1F		//IRQINVERSION1 Bit Values Mask (for IrqInversion)
//IRQINVERSION0 & IRQINVERSION1 Bits
typedef union {
	struct {
		uint8_t irqinvfifonotempty : 1;	//FIFO not empty interrupt inversion
		uint8_t irqinvfifonotfull : 1;	//FIFO not full interrupt inversion
		uint8_t irqinvfifothrcnt : 1;	//FIFO count > threshold interrupt inversion
		uint8_t irqinvfifothrfree : 1;	//FIFO free > threshold interrupt inversion
		uint8_t irqinvfifoerror : 1;	//FIFO error interrupt inversion
		uint8_t irqinvpllunlock : 1;	//PLL lock lost interrupt inversion
		uint8_t irqinvradioctrl : 1;	//Radio Controller interrupt inversion
		uint8_t irqinvpower : 1;		//Power interrupt inversion
		uint8_t irqinvxtalready : 1;	//Crystal Oscillator Ready interrupt inversion
		uint8_t irqinvwakeuptimer : 1;	//Wakeup Timer interrupt inversion
		uint8_t irqinvlposc : 1;		//Low Power Oscillator interrupt inversion
		uint8_t irqinvgpadc : 1;		//GPADC interrupt inversion
		uint8_t irqinvpllrngdone : 1;	//PLL autoranging done interrupt inversion
		uint8_t irqinvnone : 3;			//No valid/used bits
	};
	uint16_t raw;
} IrqInversion;

//Register Configuration of IRQREQUEST0 & IRQREQUEST1 Register
#define IRQREQUEST0_MASK						0xFF		//IRQREQUEST0 Bit Values Mask (for IrqRequest)
#define IRQREQUEST1_MASK						0x1F		//IRQREQUEST1 Bit Values Mask (for IrqRequest)
//IRQREQUEST0 & IRQREQUEST1 Bits
typedef union {
	struct {
		uint8_t irqrqfifonotempty : 1;	//FIFO not empty interrupt pending
		uint8_t irqrqfifonotfull : 1;	//FIFO not full interrupt pending
		uint8_t irqrqfifothrcnt : 1;	//FIFO count > threshold interrupt pending
		uint8_t irqrqfifothrfree : 1;	//FIFO free > threshold interrupt pending
		uint8_t irqrqfifoerror : 1;		//FIFO error interrupt pending
		uint8_t irqrqpllunlock : 1;		//PLL lock lost interrupt pending
		uint8_t irqrqradioctrl : 1;		//Radio Controller interrupt pending
		uint8_t irqrqpower : 1;			//Power interrupt pending
		uint8_t irqrqxtalready : 1;		//Crystal Oscillator Ready interrupt pending
		uint8_t irqrqwakeuptimer : 1;	//Wakeup Timer interrupt pending
		uint8_t irqrqlposc : 1;			//Low Power Oscillator interrupt pending
		uint8_t irqrqgpadc : 1;			//GPADC interrupt pending
		uint8_t irqrqpllrngdone : 1;	//PLL autoranging done interrupt pending
		uint8_t irqrqnone : 3;			//No valid/used bits
	};
	uint16_t raw;
} IrqRequest;

//Register Configuration of RADIOEVENTREQ0 & RADIOEVENTREQ1 Register
#define RADIOEVENTREQ0_MASK						0xFF		//RADIOEVENTREQ0 Bit Values Mask (for RadioEventRequest)
#define RADIOEVENTREQ1_MASK						0x01		//RADIOEVENTREQ1 Bit Values Mask (for RadioEventRequest)
//RADIOEVENTREQ0 & RADIOEVENTREQ1 Bits
typedef union {
	struct {
		uint8_t revrdone : 1;			//Transmit or Receive Done Radio Event Pending
		uint8_t revrsettled : 1;		//PLL Settled Radio Event Pending
		uint8_t revrradiostatechg : 1;	//Radio State Changed Event Pending
		uint8_t revrrxparamsetchg : 1;	//Receiver Parameter Set Changed Event Pending
		uint8_t revrframeclk : 1;		//Frame Clock Event Pending
		uint16_t revrnone : 11;			//No valid/used bits
	};
	uint16_t raw;
} RadioEventRequest;

//void AX5043IrqSetIRQMask(uint8_t interfaceID, IrqMask irqMask);
void AX5043IrqEnableIRQs(uint8_t interfaceID, IrqMask irqMask);
void AX5043IrqDisableIRQs(uint8_t interfaceID, IrqMask irqMask);
IrqMask AX5043IrqGetIRQMask(uint8_t interfaceID);
//void AX5043IrqSetRadioEventMask(uint8_t interfaceID, RadioEventMask radioEventMask);
void AX5043IrqEnableRadioEvents(uint8_t interfaceID, RadioEventMask radioEventMask);
void AX5043IrqDisableRadioEvents(uint8_t interfaceID, RadioEventMask radioEventMask);
RadioEventMask AX5043IrqGetRadioEventMask(uint8_t interfaceID);
void AX5043IrqSetIRQInversion(uint8_t interfaceID, IrqInversion irqInversion);
IrqInversion AX5043IrqGetIRQInversion(uint8_t interfaceID);
IrqRequest AX5043IrqGetIRQRequest(uint8_t interfaceID);
RadioEventRequest AX5043IrqGetRadioEventRequest(uint8_t interfaceID);

#ifdef __cplusplus
}
#endif

#endif /* AX5043_AX5043_IRQ_H_ */
