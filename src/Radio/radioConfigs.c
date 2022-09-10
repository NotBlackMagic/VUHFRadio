#include "radioConfigs.h"

//Radio A (UHF) Configurations
volatile RadioBaseConfigs radioABaseConfigs;			//Base Radio Configs Module
volatile RadioConfigsStruct radioAConfig;

//Radio A (UHF) Memory Bank/Channel in use/selected
volatile uint8_t radioAMemoryBank;
volatile uint8_t radioAMemoryChannel;

//Tracking Variables
volatile RadioTrackingStruct radioATracking;
volatile RadioTrackingStruct radioAPacketTracking;
