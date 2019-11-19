VUHF USB Radio Module

This is a firmware for a VUHF Radio Module based on the AX5043.
To achieve both VHF and UHF on the same board it uses two AX5043 IC’s. 
Some characteristics of this firmware:
-	Costume AX5043 Library, Read/Write to it’s registers with a function to get or set each register
-	AX5043 Library Supports Multiple AX5043 Chips, multiple SPI Interfaces
-	The MCU used is an STM32F103 and this firmware uses mostly the LL Library, except the VCP (Virtual COM) Library is using HAL
-	Command interface is based on AT commands with a custom interpreter Library
