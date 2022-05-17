#ifndef AX5043_AX5043_REGS_H_
#define AX5043_AX5043_REGS_H_

#ifdef __cplusplus
extern "C" {
#endif

//Revision & Interface Probing
#define REVISION						0x0000	//Silicon Revision
#define	SCRATCH							0x0001	//Scratch Register

//Operating Mode
#define PWRMODE							0x0002	//Power Mode

//Voltage Regulator
#define POWSTAT							0x0003	//Power Management Status
#define POWSTICKYSTAT					0x0004	//Power Management Sticky Status
#define POWIRQMASK						0x0005	//Power Management Interrupt Mask

//Interrupt Control
#define IRQMASK1						0x0006	//IRQ Mask
#define IRQMASK0						0x0007	//IRQ Mask
#define RADIOEVENTMASK1					0x0008	//Radio EventMask
#define RADIOEVENTMASK0					0x0009	//Radio EventMask
#define IRQINVERSION1					0x000A	//IRQ Inversion
#define IRQINVERSION0					0x000B	//IRQ Inversion
#define IRQREQUEST1						0x000C	//IRQ Request
#define IRQREQUEST0						0x000D	//IRQ Request
#define RADIOEVENTREQ1					0x000E	//Radio Event Request
#define RADIOEVENTREQ0					0x000F	//Radio Event Request

//Modulation & Framing
#define MODULATION						0x0010	//Modulation
#define ENCODING						0x0011	//Encoder/Decoder Settings
#define FRAMING							0x0012	//Framing settings
#define CRCINIT3						0x0014	//CRC Initialization Data
#define CRCINIT2						0x0015	//CRC Initialization Data
#define CRCINIT1						0x0016	//CRC Initialization Data
#define CRCINIT0						0x0017	//CRC Initialization Data

//Forward Error Correction
#define FEC								0x0018	//FEC (Viterbi) Configuration
#define FECSYNC							0x0019	//Interleaver Synchronization Threshold
#define FECSTATUS						0x001A	//FEC Status

//Status
#define RADIOSTATE						0x001C	//Radio Controller State
#define XTALSTATUS						0x001D	//Crystal Oscillator Status

//Pin Configuration
#define PINSTATE						0x0020	//Pinstate
#define PINFUNCSYSCLK					0x0021	//SYSCLK Pin Function
#define PINFUNCDCLK						0x0022	//DCLK Pin Function
#define PINFUNCDATA						0x0023	//DATA Pin Function
#define PINFUNCIRQ						0x0024	//IRQ Pin Function
#define PINFUNCANTSEL					0x0025	//ANTSEL Pin Function
#define PINFUNCPWRAMP					0x0026	//PWRAMP Pin Function
#define PWRAMP							0x0027	//PWRAMP Control

//FIFO
#define FIFOSTAT						0x0028	//FIFO Control
#define FIFODATA						0x0029	//FIFO Data
#define FIFOCOUNT1						0x002A	//Number of Words currently in FIFO
#define FIFOCOUNT0						0x002B	//Number of Words currently in FIFO
#define FIFOFREE1						0x002C	//Number of Words that can be written to FIFO
#define FIFOFREE0						0x002D	//Number of Words that can be written to FIFO
#define FIFOTHRESH1						0x002E	//FIFO Threshold
#define FIFOTHRESH0						0x002F	//FIFO Threshold

//Synthesizer
#define PLLLOOP							0x0030	//PLL Loop Filter Settings
#define PLLCPI							0x0031	//PLL Charge Pump Current (Boosted)
#define PLLVCODIV						0x0032	//PLL Divider Settings
#define PLLRANGINGA						0x0033	//PLL Autoranging
#define FREQA3							0x0034	//Synthesizer Frequency
#define FREQA2							0x0035	//Synthesizer Frequency
#define FREQA1							0x0036	//Synthesizer Frequency
#define FREQA0							0x0037	//Synthesizer Frequency
#define PLLLOOPBOOST					0x0038	//PLL Loop Filter Settings (Boosted)
#define PLLCPIBOOST						0x0039	//PLL Charge Pump Current
#define PLLRANGINGB						0x003B	//PLL Autoranging
#define FREQB3							0x003C	//Synthesizer Frequency
#define FREQB2							0x003D	//Synthesizer Frequency
#define FREQB1							0x003E	//Synthesizer Frequency
#define FREQB0							0x003F	//Synthesizer Frequency

//Signal Strength
#define RSSI							0x0040	//Received Signal Strength Indicator
#define BGNDRSSI						0x0041	//Background RSSI
#define DIVERSITY						0x0042	//Antenna Diversity Configuration
#define AGCCOUNTER						0x0043	//AGC Current Value

//Receiver Tracking
#define TRKDATARATE2					0x0045	//Datarate Tracking
#define TRKDATARATE1					0x0046	//Datarate Tracking
#define TRKDATARATE0					0x0047	//Datarate Tracking
#define TRKAMPL1						0x0048	//Amplitude Tracking
#define TRKAMPL0						0x0049	//Amplitude Tracking
#define TRKPHASE1						0x004A	//Phase Tracking
#define TRKPHASE0						0x004B	//Phase Tracking
#define TRKRFFREQ2						0x004D	//RF Frequency Tracking
#define TRKRFFREQ1						0x004E	//RF Frequency Tracking
#define TRKRFFREQ0						0x004F	//RF Frequency Tracking
#define TRKFREQ1						0x0050	//RF Frequency Tracking
#define TRKFREQ0						0x0051	//RF Frequency Tracking
#define TRKFSKDEMOD1					0x0052	//FSK DemodulatorTracking
#define TRKFSKDEMOD0					0x0053	//FSK DemodulatorTracking
#define TRKAFSKDEMOD1					0x0054	//AFSK DemodulatorTracking
#define TRKAFSKDEMOD0					0x0055	//AFSK DemodulatorTracking

//Timer
#define TIMER2							0x0059	//1 MHz Timer
#define TIMER1							0x005A	//1 MHz Timer
#define TIMER0							0x005B	//1 MHz Timer

//Wakeup Timer
#define WAKEUPTIMER1					0x0068	//Wakeup Timer
#define WAKEUPTIMER0					0x0069	//Wakeup Timer
#define WAKEUP1							0x006A	//Wakeup Timer
#define WAKEUP0							0x006B	//Wakeup Timer
#define WAKEUPFREQ1						0x006C	//Wakeup Frequency
#define WAKEUPFREQ0						0x006D	//Wakeup Frequency
#define WAKEUPXOEARLY					0x006E	//Wakeup Crystal Oscillator Early

//Physical Layer Parameters

//Receiver Parameters
#define IFFREQ1							0x0100	//2nd LO/IF Frequency
#define IFFREQ0							0x0101	//2nd LO/IF Frequency
#define DECIMATION						0x0102	//Decimation Factor
#define RXDATARATE2						0x0103	//Receiver Datarate
#define RXDATARATE1						0x0104	//Receiver Datarate
#define RXDATARATE0						0x0105	//Receiver Datarate
#define MAXDROFFSET2					0x0106	//Maximum Receiver Datarate Offset
#define MAXDROFFSET1					0x0107	//Maximum Receiver Datarate Offset
#define MAXDROFFSET0					0x0108	//Maximum Receiver Datarate Offset
#define MAXRFOFFSET2					0x0109	//Maximum Receiver Datarate Offset
#define MAXRFOFFSET1					0x010A	//Maximum Receiver Datarate Offset
#define MAXRFOFFSET0					0x010B	//Maximum Receiver Datarate Offset
#define FSKDMAX1						0x010C	//Four FSK Rx Deviation
#define FSKDMAX0						0x010D	//Four FSK Rx Deviation
#define FSKDMIN1						0x010E	//Four FSK Rx Deviation
#define FSKDMIN0						0x010F	//Four FSK Rx Deviation
#define AFSKSPACE1						0x0110	//AFSK Space(0) Frequency
#define AFSKSPACE0						0x0111	//AFSK Space(0) Frequency
#define AFSKMARK1						0x0112	//AFSK Mark(1) Frequency
#define AFSKMARK0						0x0113	//AFSK Mark(1) Frequency
#define AFSKCTRL						0x0114	//AFSK Control
#define AMPLFILTER						0x0115	//Amplitude Filter
#define FREQUENCYLEAK					0x0116	//Baseband Frequency Recovery Loop Leakiness
#define RXPARAMSETS						0x0117	//Receiver Parameter Set Indirection
#define RXPARAMCURSET					0x0118	//Receiver Parameter Current Set

//Receiver Parameter Set 0
#define AGCGAIN0						0x0120	//AGC Speed
#define AGCTARGET0						0x0121	//AGC Target
#define AGCAHYST0						0x0122	//AGC Digital Threshold Range
#define AGCMINMAX0						0x0123	//AGC Digital Minimum/Maximum Set Points
#define TIMEGAIN0						0x0124	//Timing Gain
#define DRGAIN0							0x0125	//Data Rate Gain
#define PHASEGAIN0						0x0126	//Filter Index, Phase Gain
#define FREQGAINA0						0x0127	//Frequency Gain A
#define FREQGAINB0						0x0128	//Frequency Gain B
#define FREQGAINC0						0x0129	//Frequency Gain C
#define FREQGAIND0						0x012A	//Frequency Gain D
#define AMPLGAIN0						0x012B	//Amplitude Gain
#define FREQDEV10						0x012C	//Receiver Frequency Deviation
#define FREQDEV00						0x012D	//Receiver Frequency Deviation
#define FOURFSK0						0x012E	//Four FSK Control
#define BBOFFSRES0						0x012F	//Baseband Offset Compensation Resistors

//Receiver Parameter Set 1
#define AGCGAIN1						0x0130	//AGC Speed
#define AGCTARGET1						0x0131	//AGC Target
#define AGCAHYST1						0x0132	//AGC Digital Threshold Range
#define AGCMINMAX1						0x0133	//AGC Digital Minimum/Maximum Set Points
#define TIMEGAIN1						0x0134	//Timing Gain
#define DRGAIN1							0x0135	//Data Rate Gain
#define PHASEGAIN1						0x0136	//Filter Index, Phase Gain
#define FREQGAINA1						0x0137	//Frequency Gain A
#define FREQGAINB1						0x0138	//Frequency Gain B
#define FREQGAINC1						0x0139	//Frequency Gain C
#define FREQGAIND1						0x013A	//Frequency Gain D
#define AMPLGAIN1						0x013B	//Amplitude Gain
#define FREQDEV11						0x013C	//Receiver Frequency Deviation
#define FREQDEV01						0x013D	//Receiver Frequency Deviation
#define FOURFSK1						0x013E	//Four FSK Control
#define BBOFFSRES1						0x013F	//Baseband Offset Compensation Resistors

//Receiver Parameter Set 2
#define AGCGAIN2						0x0140	//AGC Speed
#define AGCTARGET2						0x0141	//AGC Target
#define AGCAHYST2						0x0142	//AGC Digital Threshold Range
#define AGCMINMAX2						0x0143	//AGC Digital Minimum/Maximum Set Points
#define TIMEGAIN2						0x0144	//Timing Gain
#define DRGAIN2							0x0145	//Data Rate Gain
#define PHASEGAIN2						0x0146	//Filter Index, Phase Gain
#define FREQGAINA2						0x0147	//Frequency Gain A
#define FREQGAINB2						0x0148	//Frequency Gain B
#define FREQGAINC2						0x0149	//Frequency Gain C
#define FREQGAIND2						0x014A	//Frequency Gain D
#define AMPLGAIN2						0x014B	//Amplitude Gain
#define FREQDEV12						0x014C	//Receiver Frequency Deviation
#define FREQDEV02						0x014D	//Receiver Frequency Deviation
#define FOURFSK2						0x014E	//Four FSK Control
#define BBOFFSRES2						0x014F	//Baseband Offset Compensation Resistors

//Receiver Parameter Set 3
#define AGCGAIN3						0x0150	//AGC Speed
#define AGCTARGET3						0x0151	//AGC Target
#define AGCAHYST3						0x0152	//AGC Digital Threshold Range
#define AGCMINMAX3						0x0153	//AGC Digital Minimum/Maximum Set Points
#define TIMEGAIN3						0x0154	//Timing Gain
#define DRGAIN3							0x0155	//Data Rate Gain
#define PHASEGAIN3						0x0156	//Filter Index, Phase Gain
#define FREQGAINA3						0x0157	//Frequency Gain A
#define FREQGAINB3						0x0158	//Frequency Gain B
#define FREQGAINC3						0x0159	//Frequency Gain C
#define FREQGAIND3						0x015A	//Frequency Gain D
#define AMPLGAIN3						0x015B	//Amplitude Gain
#define FREQDEV13						0x015C	//Receiver Frequency Deviation
#define FREQDEV03						0x015D	//Receiver Frequency Deviation
#define FOURFSK3						0x015E	//Four FSK Control
#define BBOFFSRES3						0x015F	//Baseband Offset Compensation Resistors

//Transmitter Parameters
#define MODCFGF							0x0160	//Modulator Configuration F
#define FSKDEV2							0x0161	//FSK Frequency Deviation
#define FSKDEV1							0x0162	//FSK Frequency Deviation
#define FSKDEV0							0x0163	//FSK Frequency Deviation
#define MODCFGA							0x0164	//Modulator Configuration A
#define TXRATE2							0x0165	//Transmitter Bitrate
#define TXRATE1							0x0166	//Transmitter Bitrate
#define TXRATE0							0x0167	//Transmitter Bitrate
#define TXPWRCOEFFA1					0x0168	//Transmitter Predistortion Coefficient A
#define TXPWRCOEFFA0					0x0169	//Transmitter Predistortion Coefficient A
#define TXPWRCOEFFB1					0x016A	//Transmitter Predistortion Coefficient B
#define TXPWRCOEFFB0					0x016B	//Transmitter Predistortion Coefficient B
#define TXPWRCOEFFC1					0x016C	//Transmitter Predistortion Coefficient C
#define TXPWRCOEFFC0					0x016D	//Transmitter Predistortion Coefficient C
#define TXPWRCOEFFD1					0x016E	//Transmitter Predistortion Coefficient D
#define TXPWRCOEFFD0					0x016F	//Transmitter Predistortion Coefficient D
#define TXPWRCOEFFE1					0x0170	//Transmitter Predistortion Coefficient E
#define TXPWRCOEFFE0					0x0171	//Transmitter Predistortion Coefficient E
#define MODCFGP							0x0F5F	//Modulator Configuration P: PSK settings

//PLL Parameters
#define PLLVCOI							0x0180	//VCO Current
#define PLLVCOIR						0x0181	//VCO Current Readback
#define PLLLOCKDET						0x0182	//PLL Lock Detect Delay
#define PLLRNGCLK						0x0183	//PLL Ranging Clock

//Crystal Oscillator
#define XTALCAP							0x0184	//Crystal Oscillator Load Capacitance Configuration

//Baseband
#define BBTUNE							0x0188	//Baseband Tuning
#define BBOFFSCAP						0x0189	//Baseband Offset Compensation Capacitors

//MAC Layer Parameters

//Packet Format
#define PKTADDRCFG						0x200	//Packet Address Configuration
#define PKTLENCFG						0x201	//Packet Length Configuration
#define PKTLENOFFSET					0x202	//Packet Length Configuration
#define PKTMAXLEN						0x203	//Packet Maximum Length
#define PKTADDR3						0x204	//Packet Address 3
#define PKTADDR2						0x205	//Packet Address 2
#define PKTADDR1						0x206	//Packet Address 1
#define PKTADDR0						0x207	//Packet Address 0
#define PKTADDRMASK3					0x208	//Packet Address Mask 3
#define PKTADDRMASK2					0x209	//Packet Address Mask 2
#define PKTADDRMASK1					0x20A	//Packet Address Mask 1
#define PKTADDRMASK0					0x20B	//Packet Address Mask 0

//Pattern Match
#define MATCH0PAT3						0x0210	//Pattern Match Unit 0, Pattern
#define MATCH0PAT2						0x0211	//Pattern Match Unit 0, Pattern
#define MATCH0PAT1						0x0212	//Pattern Match Unit 0, Pattern
#define MATCH0PAT0						0x0213	//Pattern Match Unit 0, Pattern
#define MATCH0LEN						0x0214	//Pattern Match Unit 0, Pattern Length
#define MATCH0MIN						0x0215	//Pattern Match Unit 0, Minimum Match
#define MATCH0MAX						0x0216	//Pattern Match Unit 0, Maximum Match
#define MATCH1PAT1						0x0218	//Pattern Match Unit 1, Pattern
#define MATCH1PAT0						0x0219	//Pattern Match Unit 1, Pattern
#define MATCH1LEN						0x021C	//Pattern Match Unit 1, Pattern Length
#define MATCH1MIN						0x021D	//Pattern Match Unit 1, Minimum Match
#define MATCH1MAX						0x021E	//Pattern Match Unit 1, Maximum Match

//Packet Controller
#define TMGTXBOOST						0x0220	//Transmit PLL Boost Time
#define TMGTXSETTLE						0x0221	//Transmit PLL(post Boost) Settling Time
#define TMGRXBOOST						0x0223	//Receive PLL Boost Time
#define TMGRXSETTLE						0x0224	//Receive PLL(post Boost) Settling Time
#define TMGRXOFFSACQ					0x0225	//Receive Baseband DC Offset Acquisition Time
#define TMGRXCOARSEAGC					0x0226	//Receive Coarse AGC Time
#define TMGRXAGC						0x0227	//Receiver AGC Settling Time
#define TMGRXRSSI						0x0228	//Receiver RSSI Settling Time
#define TMGRXPREAMBLE1					0x0229	//Receiver Preamble 1 Timeout
#define TMGRXPREAMBLE2					0x022A	//Receiver Preamble 2 Timeout
#define TMGRXPREAMBLE3					0x022B	//Receiver Preamble 3 Timeout
#define RSSIREFERENCE					0x022C	//RSSI Offset
#define RSSIABSTHR						0x022D	//RSSI Absolute Threshold
#define BGNDRSSIGAIN					0x022E	//Background RSSI Averaging Time Constant
#define BGNDRSSITHR						0x022F	//Background RSSI Relative Threshold
#define PKTCHUNKSIZE					0x0230	//Packet Chunk Size
#define PKTMISCFLAGS					0x0231	//Packet Controller Miscellaneous Flags
#define PKTSTOREFLAGS					0x0232	//Packet Controller Store Flags
#define PKTACCEPTFLAGS					0x0233	//Packet Controller Accept Flags

//Special Functions

//General Purpose ADC
#define GPADCCTRL						0x0300	//General Purpose ADC Control
#define GPADCPERIOD						0x0301	//GPADC Sampling Period
#define GPADC13VALUE1					0x0308	//GPADC13 Value
#define GPADC13VALUE0					0x0309	//GPADC13 Value

//Low Power Oscillator Calibration
#define LPOSCCONFIG						0x0310	//Low Power Oscillator Configuration
#define LPOSCSTATUS						0x0311	//Low Power Oscillator Status
#define LPOSCKFILT1						0x0312	//Low Power Oscillator Calibration Filter Constant
#define LPOSCKFILT0						0x0313	//Low Power Oscillator Calibration Filter Constant
#define LPOSCREF1						0x0314	//Low Power Oscillator Calibration Reference
#define LPOSCREF0						0x0315	//Low Power Oscillator Calibration Reference
#define LPOSCFREQ1						0x0316	//Low Power Oscillator Calibration Frequency
#define LPOSCFREQ0						0x0317	//Low Power Oscillator Calibration Frequency
#define LPOSCPER1						0x0318	//Low PowerOscillator Calibration Period
#define LPOSCPER0						0x0319	//Low PowerOscillator Calibration Period

//DAC
#define DACVALUE1						0x0330	//DAC Value
#define DACVALUE0						0x0331	//DAC Value
#define DACCONFIG						0x0332	//DAC Configuration

//Experimental Features Registers

//Analog IQ Mode
#define TMMUX							0x0F02	//TMMUX
#define BBDETECTOR0						0x0F46	//Baseband Power Detector 0

//DSPmode2
#define DSPMODESHREG					0x006F	//DSPmode SPI Shift Register Access

//DSP Mode Interface
#define DSPMODECFG						0x0320	//DSP Mode Setting
#define DSPMODESKIP1					0x0321	//DSP Mode Skip 1
#define DSPMODESKIP0					0x0322	//DSP Mode Skip 2

//Performance Tuning Registers
#define PERFTUNE0						0x0F00	//Performance Tuning Register 0
#define PERFTUNE1						0x0F01	//Performance Tuning Register 1
#define PERFTUNE2						0x0F02	//Performance Tuning Register 2
#define PERFTUNE3						0x0F03	//Performance Tuning Register 3
#define PERFTUNE4						0x0F04	//Performance Tuning Register 4
#define PERFTUNE5						0x0F05	//Performance Tuning Register 5
#define PERFTUNE6						0x0F06	//Performance Tuning Register 6
#define PERFTUNE7						0x0F07	//Performance Tuning Register 7
#define PERFTUNE8						0x0F08	//Performance Tuning Register 8
#define PERFTUNE9						0x0F09	//Performance Tuning Register 9
#define PERFTUNE10						0x0F0A	//Performance Tuning Register 10
#define PERFTUNE11						0x0F0B	//Performance Tuning Register 11
#define PERFTUNE12						0x0F0C	//Performance Tuning Register 12
#define PERFTUNE13						0x0F0D	//Performance Tuning Register 13
#define PERFTUNE14						0x0F0E	//Performance Tuning Register 14
#define PERFTUNE15						0x0F0F	//Performance Tuning Register 15
#define PERFTUNE16						0x0F10	//Performance Tuning Register 16
#define PERFTUNE17						0x0F11	//Performance Tuning Register 17
#define PERFTUNE18						0x0F12	//Performance Tuning Register 18
#define PERFTUNE19						0x0F13	//Performance Tuning Register 19
#define PERFTUNE20						0x0F14	//Performance Tuning Register 20
#define PERFTUNE21						0x0F15	//Performance Tuning Register 21
#define PERFTUNE22						0x0F16	//Performance Tuning Register 22
#define PERFTUNE23						0x0F17	//Performance Tuning Register 23
#define PERFTUNE24						0x0F18	//Performance Tuning Register 24
#define PERFTUNE25						0x0F19	//Performance Tuning Register 25
#define PERFTUNE26						0x0F1A	//Performance Tuning Register 26
#define PERFTUNE27						0x0F1B	//Performance Tuning Register 27
#define PERFTUNE28						0x0F1C	//Performance Tuning Register 28
#define PERFTUNE29						0x0F1D	//Performance Tuning Register 29
#define PERFTUNE30						0x0F1E	//Performance Tuning Register 30
#define PERFTUNE31						0x0F1F	//Performance Tuning Register 31
#define PERFTUNE32						0x0F20	//Performance Tuning Register 32
#define PERFTUNE33						0x0F21	//Performance Tuning Register 33
#define PERFTUNE34						0x0F22	//Performance Tuning Register 34
#define PERFTUNE35						0x0F23	//Performance Tuning Register 35
#define PERFTUNE36						0x0F24	//Performance Tuning Register 36
#define PERFTUNE37						0x0F25	//Performance Tuning Register 37
#define PERFTUNE38						0x0F26	//Performance Tuning Register 38
#define PERFTUNE39						0x0F27	//Performance Tuning Register 39
#define PERFTUNE40						0x0F28	//Performance Tuning Register 40
#define PERFTUNE41						0x0F29	//Performance Tuning Register 41
#define PERFTUNE42						0x0F2A	//Performance Tuning Register 42
#define PERFTUNE43						0x0F2B	//Performance Tuning Register 43
#define PERFTUNE44						0x0F2C	//Performance Tuning Register 44
#define PERFTUNE45						0x0F2D	//Performance Tuning Register 45
#define PERFTUNE46						0x0F2E	//Performance Tuning Register 46
#define PERFTUNE47						0x0F2F	//Performance Tuning Register 47
#define PERFTUNE48						0x0F30	//Performance Tuning Register 48
#define PERFTUNE49						0x0F31	//Performance Tuning Register 49
#define PERFTUNE50						0x0F32	//Performance Tuning Register 50
#define PERFTUNE51						0x0F33	//Performance Tuning Register 51
#define PERFTUNE52						0x0F34	//Performance Tuning Register 52
#define PERFTUNE53						0x0F35	//Performance Tuning Register 53
#define PERFTUNE54						0x0F36	//Performance Tuning Register 54
#define PERFTUNE55						0x0F37	//Performance Tuning Register 55
#define PERFTUNE56						0x0F38	//Performance Tuning Register 56
#define PERFTUNE57						0x0F39	//Performance Tuning Register 57
#define PERFTUNE58						0x0F3A	//Performance Tuning Register 58
#define PERFTUNE59						0x0F3B	//Performance Tuning Register 59
#define PERFTUNE60						0x0F3C	//Performance Tuning Register 60
#define PERFTUNE61						0x0F3D	//Performance Tuning Register 61
#define PERFTUNE62						0x0F3E	//Performance Tuning Register 62
#define PERFTUNE63						0x0F3F	//Performance Tuning Register 63
#define PERFTUNE64						0x0F40	//Performance Tuning Register 64
#define PERFTUNE65						0x0F41	//Performance Tuning Register 65
#define PERFTUNE66						0x0F42	//Performance Tuning Register 66
#define PERFTUNE67						0x0F43	//Performance Tuning Register 67
#define PERFTUNE68						0x0F44	//Performance Tuning Register 68
#define PERFTUNE69						0x0F45	//Performance Tuning Register 69
#define PERFTUNE70						0x0F46	//Performance Tuning Register 70
#define PERFTUNE71						0x0F47	//Performance Tuning Register 71
#define PERFTUNE72						0x0F48	//Performance Tuning Register 72
#define PERFTUNE73						0x0F49	//Performance Tuning Register 73
#define PERFTUNE74						0x0F4A	//Performance Tuning Register 74
#define PERFTUNE75						0x0F4B	//Performance Tuning Register 75
#define PERFTUNE76						0x0F4C	//Performance Tuning Register 76
#define PERFTUNE77						0x0F4D	//Performance Tuning Register 77
#define PERFTUNE78						0x0F4E	//Performance Tuning Register 78
#define PERFTUNE79						0x0F4F	//Performance Tuning Register 79
#define PERFTUNE95						0x0F5F	//Performance Tuning Register 95
#define PERFTUNE114						0x0F72	//Performance Tuning Register 114
#define PERFTUNE255						0x0FFF	//Performance Tuning Register 255

#ifdef __cplusplus
}
#endif

#endif /* AX5043_AX5043_REGS_H_ */
