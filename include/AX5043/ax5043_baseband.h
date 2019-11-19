#ifndef AX5043_AX5043_BASEBAND_H_
#define AX5043_AX5043_BASEBAND_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ax5043_interface.h"
#include "ax5043_regs.h"

//Register Configuration of BBTUNE Register
#define BBTUNE_MASK							0x0F	//Baseband Tuning Value
#define BBTUNERUN_MASK						0x10	//Baseband Tuning Start

//Register Configuration of BBOFFSCAP Register
#define CAPINTA_MASK						0x07	//Baseband Gain Block A Offset Compensation Capacitors
#define CAPINTB_MASK						0x70	//Baseband Gain Block B Offset Compensation Capacitors

void AX5043BasebandSetTuneValue(uint8_t interfaceID, uint8_t value);
uint8_t AX5043BasebandGetTuneValue(uint8_t interfaceID);
void AX5043BasebandSetTuneRunning(uint8_t interfaceID, uint8_t start);
uint8_t AX5043BasebandGetTuneRunning(uint8_t interfaceID);
void AX5043BasebandSetGainOffsetCompCapA(uint8_t interfaceID, uint8_t cap);
uint8_t AX5043BasebandGetGainOffsetCompCapA(uint8_t interfaceID);
void AX5043BasebandSetGainOffsetCompCapB(uint8_t interfaceID, uint8_t cap);
uint8_t AX5043BasebandGetGainOffsetCompCapB(uint8_t interfaceID);

#ifdef __cplusplus
}
#endif

#endif /* AX5043_AX5043_BASEBAND_H_ */
