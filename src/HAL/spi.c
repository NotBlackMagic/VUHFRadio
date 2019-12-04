#include "spi.h"

/**
  * @brief	This function initializes the SPI1 interface, also sets the respective GPIO pins
  * @param	None
  * @return	None
  */
void SPI1Init() {
	//Enable bus clocks
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI1);		//Enable Clock to SPI1
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_AFIO);

	//Configure GPIOs
	LL_GPIO_AF_Remap_SWJ_NOJTAG();		//Disable JTAG Interface
	while((AFIO->MAPR & AFIO_MAPR_SWJ_CFG_JTAGDISABLE) != AFIO_MAPR_SWJ_CFG_JTAGDISABLE);
	LL_GPIO_AF_EnableRemap_SPI1();		//Remap SPI1 GPIOs to Alternative GPIOs
	//Set SCLK, on PB3
	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_3, LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_3, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinOutputType(GPIOB, LL_GPIO_PIN_3, LL_GPIO_OUTPUT_PUSHPULL);
	//Set MISO, on PB4
	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_4, LL_GPIO_MODE_FLOATING);
	LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_4, LL_GPIO_SPEED_FREQ_HIGH);
	//Set MOSI, on PB4
	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_5, LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_5, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinOutputType(GPIOB, LL_GPIO_PIN_5, LL_GPIO_OUTPUT_PUSHPULL);

	//Configure SPI Interface
	LL_SPI_SetBaudRatePrescaler(SPI1, LL_SPI_BAUDRATEPRESCALER_DIV128);
	LL_SPI_SetTransferDirection(SPI1,LL_SPI_FULL_DUPLEX);
	LL_SPI_SetClockPhase(SPI1, LL_SPI_PHASE_1EDGE);
	LL_SPI_SetClockPolarity(SPI1, LL_SPI_POLARITY_LOW);
	LL_SPI_SetTransferBitOrder(SPI1, LL_SPI_MSB_FIRST);
	LL_SPI_SetDataWidth(SPI1, LL_SPI_DATAWIDTH_8BIT);
	LL_SPI_SetNSSMode(SPI1, LL_SPI_NSS_SOFT);
	LL_SPI_SetMode(SPI1, LL_SPI_MODE_MASTER);

	//Configure SPI Interrupts
//	LL_SPI_EnableIT_TXE(SPI1);
//	LL_SPI_EnableIT_RXNE(SPI1);
//	LL_SPI_EnableIT_ERR(SPI1);

	//Enable SPI
	LL_SPI_Enable(SPI1);
}

/**
  * @brief	This function initializes the SPI2 interface, also sets the respective GPIO pins
  * @param	None
  * @return	None
  */
void SPI2Init() {
	//Enable bus clocks
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI2);		//Enable Clock to SPI2
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_AFIO);

	//Configure GPIOs
	//Set SCLK, on PB13
	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_13, LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_13, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinOutputType(GPIOB, LL_GPIO_PIN_13, LL_GPIO_OUTPUT_PUSHPULL);
	//Set MISO, on PB14
	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_14, LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_14, LL_GPIO_SPEED_FREQ_HIGH);
	//Set MOSI, on PB15
	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_15, LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_15, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinOutputType(GPIOB, LL_GPIO_PIN_15, LL_GPIO_OUTPUT_PUSHPULL);

	//Configure SPI Interface
	LL_SPI_SetBaudRatePrescaler(SPI2, LL_SPI_BAUDRATEPRESCALER_DIV128);
	LL_SPI_SetTransferDirection(SPI2,LL_SPI_FULL_DUPLEX);
	LL_SPI_SetClockPhase(SPI2, LL_SPI_PHASE_1EDGE);
	LL_SPI_SetClockPolarity(SPI2, LL_SPI_POLARITY_LOW);
	LL_SPI_SetTransferBitOrder(SPI2, LL_SPI_MSB_FIRST);
	LL_SPI_SetDataWidth(SPI2, LL_SPI_DATAWIDTH_8BIT);
	LL_SPI_SetNSSMode(SPI2, LL_SPI_NSS_SOFT);
	LL_SPI_SetMode(SPI2, LL_SPI_MODE_MASTER);

	//Configure SPI Interrupts
//	LL_SPI_EnableIT_TXE(SPI2);
//	LL_SPI_EnableIT_RXNE(SPI2);
//	LL_SPI_EnableIT_ERR(SPI2);

	LL_SPI_Enable(SPI2);
}

/**
  * @brief	This function performs a byte transfer on SPI1 (read and write 1 byte)
  * @param	txByte: Single Byte to be transmitted
  * @return	received single byte
  */
uint8_t SPI1ReadWrite(uint8_t txByte) {
	uint8_t rxByte;

	while(!LL_SPI_IsActiveFlag_TXE(SPI1));
	LL_SPI_TransmitData8(SPI1, txByte);
	while(!LL_SPI_IsActiveFlag_RXNE(SPI1));
	rxByte = LL_SPI_ReceiveData8(SPI1);

	return rxByte;
}

/**
  * @brief	This function performs a byte transfer on SPI2 (read and write 1 byte)
  * @param	txByte: Single Byte to be transmitted
  * @return	received single byte
  */
uint8_t SPI2ReadWrite(uint8_t txByte) {
	uint8_t rxByte;

	while(!LL_SPI_IsActiveFlag_TXE(SPI2));
	LL_SPI_TransmitData8(SPI2, txByte);
	while(!LL_SPI_IsActiveFlag_RXNE(SPI2));
	rxByte = LL_SPI_ReceiveData8(SPI2);

	return rxByte;
}
