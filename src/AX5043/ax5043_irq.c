#include "ax5043_irq.h"

/**
  * @brief	This function sets the Interrupt Control IRQ Mask, which interrupts are enabled
  * @param	interfaceID: Which interface (chip) used
  * @param	irqMask: Which interrupts should be enabled
  * @return	None
  */
//void AX5043IrqSetIRQMask(uint8_t interfaceID, IrqMask irqMask) {
//	uint8_t config = irqMask.raw & IRQMASK0_MASK;
//	AX5043WriteShortAddress(interfaceID, IRQMASK0, &config, 1);
//	config = (irqMask.raw >> 8) & IRQMASK1_MASK;
//	AX5043WriteShortAddress(interfaceID, IRQMASK1, &config, 1);
//}

/**
  * @brief	This function Enables the selected Interrupts, keeping the other interrupts as programmed
  * @param	interfaceID: Which interface (chip) used
  * @param	irqMask: Which interrupts should be enabled
  * @return	None
  */
void AX5043IrqEnableIRQs(uint8_t interfaceID, IrqMask irqMask) {
	uint8_t config;
	uint16_t irqConfig;

	//Get currently set IRQs
	AX5043ReadShortAddress(interfaceID, IRQMASK0, &config, 1);
	irqConfig = config;
	AX5043ReadShortAddress(interfaceID, IRQMASK1, &config, 1);
	irqConfig += (config & IRQMASK1_MASK) << 8;

	//Mask/add to be enabled interrupts
	irqConfig = irqConfig | irqMask.raw;

	//Write back new IRQ settings
	config = irqConfig & IRQMASK0_MASK;
	AX5043WriteShortAddress(interfaceID, IRQMASK0, &config, 1);
	config = (irqConfig >> 8) & IRQMASK1_MASK;
	AX5043WriteShortAddress(interfaceID, IRQMASK1, &config, 1);
}

/**
  * @brief	This function Disables the selected Interrupts, keeping the other interrupts as programmed
  * @param	interfaceID: Which interface (chip) used
  * @param	irqMask: Which interrupts should be disabled
  * @return	None
  */
void AX5043IrqDisableIRQs(uint8_t interfaceID, IrqMask irqMask) {
	uint8_t config;
	uint16_t irqConfig;

	//Get currently set IRQs
	AX5043ReadShortAddress(interfaceID, IRQMASK0, &config, 1);
	irqConfig = config;
	AX5043ReadShortAddress(interfaceID, IRQMASK1, &config, 1);
	irqConfig += (config & IRQMASK1_MASK) << 8;

	//Mask/add to be disabled interrupts
	irqConfig = irqConfig & (~irqMask.raw);

	//Write back new IRQ settings
	config = irqConfig & IRQMASK0_MASK;
	AX5043WriteShortAddress(interfaceID, IRQMASK0, &config, 1);
	config = (irqConfig >> 8) & IRQMASK1_MASK;
	AX5043WriteShortAddress(interfaceID, IRQMASK1, &config, 1);
}

/**
  * @brief	This function gets the Interrupt Control IRQ Mask, which interrupts are enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	IrqMask: Which interrupts are enabled
  */
IrqMask AX5043IrqGetIRQMask(uint8_t interfaceID) {
	IrqMask irqMask;
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, IRQMASK0, &config, 1);
	irqMask.raw = config & IRQMASK0_MASK;
	AX5043ReadShortAddress(interfaceID, IRQMASK1, &config, 1);
	irqMask.raw += (config & IRQMASK1_MASK) << 8;
	return irqMask;
}

/**
  * @brief	This function sets the Radio Event Control Mask, which events trigger and interrupt
  * @param	interfaceID: Which interface (chip) used
  * @param	radioEventMask: Which events should be enabled
  * @return	None
  */
//void AX5043IrqSetRadioEventMask(uint8_t interfaceID, RadioEventMask radioEventMask) {
//	uint8_t config = radioEventMask.raw & RADIOEVENTMASK0_MASK;
//	AX5043WriteShortAddress(interfaceID, RADIOEVENTMASK0, &config, 1);
//	config = (radioEventMask.raw >> 8) & RADIOEVENTMASK1_MASK;
//	AX5043WriteShortAddress(interfaceID, RADIOEVENTMASK1, &config, 1);
//}

/**
  * @brief	This function enables the selected Radio Events, keeping the other Radio Events as programmed
  * @param	interfaceID: Which interface (chip) used
  * @param	radioEventMask: Which events should be enabled
  * @return	None
  */
void AX5043IrqEnableRadioEvents(uint8_t interfaceID, RadioEventMask radioEventMask) {
	uint8_t config;
	uint16_t eventConfig;

	//Get currently set IRQs
	AX5043ReadShortAddress(interfaceID, RADIOEVENTMASK0, &config, 1);
	eventConfig = config;
	AX5043ReadShortAddress(interfaceID, RADIOEVENTMASK1, &config, 1);
	eventConfig += (config & RADIOEVENTMASK1_MASK) << 8;

	//Mask/add to be enabled Radio Events
	eventConfig = eventConfig | radioEventMask.raw;

	//Write back new IRQ settings
	config = eventConfig & RADIOEVENTMASK0_MASK;
	AX5043WriteShortAddress(interfaceID, RADIOEVENTMASK0, &config, 1);
	config = (eventConfig >> 8) & RADIOEVENTMASK1_MASK;
	AX5043WriteShortAddress(interfaceID, RADIOEVENTMASK1, &config, 1);
}

/**
  * @brief	This function disables the selected Radio Events, keeping the other Radio Events as programmed
  * @param	interfaceID: Which interface (chip) used
  * @param	radioEventMask: Which events should be disabled
  * @return	None
  */
void AX5043IrqDisableRadioEvents(uint8_t interfaceID, RadioEventMask radioEventMask) {
	uint8_t config;
	uint16_t eventConfig;

	//Get currently set IRQs
	AX5043ReadShortAddress(interfaceID, RADIOEVENTMASK0, &config, 1);
	eventConfig = config;
	AX5043ReadShortAddress(interfaceID, RADIOEVENTMASK1, &config, 1);
	eventConfig += (config & RADIOEVENTMASK1_MASK) << 8;

	//Mask/add to be disabled Radio Events
	eventConfig = eventConfig & (~radioEventMask.raw);

	//Write back new IRQ settings
	config = eventConfig & RADIOEVENTMASK0_MASK;
	AX5043WriteShortAddress(interfaceID, RADIOEVENTMASK0, &config, 1);
	config = (eventConfig >> 8) & RADIOEVENTMASK1_MASK;
	AX5043WriteShortAddress(interfaceID, RADIOEVENTMASK1, &config, 1);
}

/**
  * @brief	This function gets the Radio Event Control Mask, which events trigger and interrupt
  * @param	interfaceID: Which interface (chip) used
  * @return	RadioEventMask: Which events are enabled
  */
RadioEventMask AX5043IrqGetRadioEventMask(uint8_t interfaceID) {
	RadioEventMask radioEventMask;
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, RADIOEVENTMASK0, &config, 1);
	radioEventMask.raw = config & RADIOEVENTMASK0_MASK;
	AX5043ReadShortAddress(interfaceID, RADIOEVENTMASK1, &config, 1);
	radioEventMask.raw += (config & RADIOEVENTMASK1_MASK) << 8;
	return radioEventMask;
}

/**
  * @brief	This function sets the Interrupt Control IRQ Inversion, which interrupts are inverted
  * @param	interfaceID: Which interface (chip) used
  * @param	irqInversion: Which interrupts should be inverted
  * @return	None
  */
void AX5043IrqSetIRQInversion(uint8_t interfaceID, IrqInversion irqInversion) {
	uint8_t config = irqInversion.raw & IRQINVERSION0_MASK;
	AX5043WriteShortAddress(interfaceID, IRQINVERSION0, &config, 1);
	config = (irqInversion.raw >> 8) & IRQINVERSION1_MASK;
	AX5043WriteShortAddress(interfaceID, IRQINVERSION1, &config, 1);
}

/**
  * @brief	This function gets the Interrupt Control IRQ Mask, which interrupts are enabled
  * @param	interfaceID: Which interface (chip) used
  * @return	IrqInversion: Which interrupts are inverted
  */
IrqInversion AX5043IrqGetIRQInversion(uint8_t interfaceID) {
	IrqInversion irqInversion;
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, IRQINVERSION0, &config, 1);
	irqInversion.raw = config & IRQINVERSION0_MASK;
	AX5043ReadShortAddress(interfaceID, IRQINVERSION1, &config, 1);
	irqInversion.raw += (config & IRQINVERSION1_MASK) << 8;
	return irqInversion;
}


/**
  * @brief	This function gets the Pending Interrupt Requests
  * @param	interfaceID: Which interface (chip) used
  * @return	IrqRequest: Which interrupts are pending
  */
IrqRequest AX5043IrqGetIRQRequest(uint8_t interfaceID) {
	IrqRequest irqRequest;
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, IRQREQUEST0, &config, 1);
	irqRequest.raw = config & IRQREQUEST0_MASK;
	AX5043ReadShortAddress(interfaceID, IRQREQUEST1, &config, 1);
	irqRequest.raw += (config & IRQREQUEST1_MASK) << 8;
	return irqRequest;
}

/**
  * @brief	This function gets the Pending Radio Events
  * @param	interfaceID: Which interface (chip) used
  * @return	RadioEventMask: Which events are enabled
  */
RadioEventRequest AX5043IrqGetRadioEventRequest(uint8_t interfaceID) {
	RadioEventRequest radioEventRequest;
	uint8_t config;
	AX5043ReadShortAddress(interfaceID, RADIOEVENTREQ0, &config, 1);
	radioEventRequest.raw = config & RADIOEVENTREQ0_MASK;
	AX5043ReadShortAddress(interfaceID, RADIOEVENTREQ1, &config, 1);
	radioEventRequest.raw += (config & RADIOEVENTREQ1_MASK) << 8;
	return radioEventRequest;
}
