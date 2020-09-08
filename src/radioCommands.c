#include "radioCommands.h"

/**
  * @brief	This function sets the Radio Center Frequency
  * @param	radio: Selects the Radio
  * @param	frequency: The center frequency in Hz
  * @return	0-> Success, 1-> Failed/Error
  */
uint8_t RadioSetCenterFrequency(uint8_t radio, uint32_t frequency) {
	//Check limits
	if(radio == RADIO_A) {
		if(frequency < RADIO_A_FREQ_MIN || frequency > RADIO_A_FREQ_MAX) {
			return 1;
		}
	}
	else if(radio == RADIO_B) {
		if(frequency < RADIO_B_FREQ_MIN || frequency > RADIO_B_FREQ_MAX) {
			return 1;
		}
	}
	else {
		//Invalid Radio ID/Index
		return 1;
	}

	//Set Central Frequency
	uint32_t freq = (uint32_t)((frequency * (16777216.f / RADIO_A_XTAL)) + 0.5f);
	AX5043SynthSetFrequencyA(radio, freq);

	//Perform auto ranging
	AX5043SynthStartAutoRangingA(radio);
	while(AX5043SynthGetAutoRangingA(radio));	//Wait for Auto Ranging Complete

	return 0;
}
