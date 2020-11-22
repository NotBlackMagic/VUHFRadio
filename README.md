# VUHFRadio Module

This is a firmware for a VUHFRadio Module based on the AX5043.
To achieve both VHF and UHF on the same board it uses two AX5043 IC’s. 

Some characteristics of this firmware:
-	Custom AX5043 Library, Read/Write to it’s registers with a function to get or set each register
-	AX5043 Library Supports Multiple AX5043 Chips, multiple SPI Interfaces
-	The MCU used is an STM32F103 and this firmware uses mostly the LL Library, except the VCP (Virtual COM) Library is using HAL
-	Command interface is based on CAT commands, similar to what is used in popular HAM Radios from Yaesu or Kenwood

Current version is tested and works with:
- AX.25 Frames with HDLC and CRC handled in the radio.
- AFSK-1200: RX and TX compatible with HAM Radios using a TNC
- (G)MSK/(G)FSK: Both RX and TX, tested @ 9600 bits/s MSK and GMSK (with BT of 0.5 and 0.3)
- BPSK: Only RX working so far, TX has to high distortion currently
- Morse decoding using the RSSI tracking
- AM and FM Demodulation output by the DAC
- FM Modulation from ADC input

Results like spectrums and input matching and other tests: www.notblackmagic.com/projects/vuhf-radio/

Detailed explanation on the configuration of the AX5043 transceiver: www.notblackmagic.com/bitsnpieces/ax5043/

## File Organization

**src/HAL:** MCU peripheral drivers, custom HALs

**src/USB:** MCU USB HAL with custom wrapper functions

**src/AX5043:** AX5043 register read/write wrappers and defines

**src/AX5043/ax5043_interface.c:** SPI interface wrapper

**src/Commands/CATInterface.c:** CAT Command Handler and interpreter functions (The other files are deprecated and will be phased out)

**src/radioCommands.c:** Radio configuration functions/wrappers

**include/configs.c:** Radio configurations save files
