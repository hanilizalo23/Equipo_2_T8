/*
 * I2C_driver.c
 *
 *  Created on: 22 mar 2022
 *      Author: Mauricio Peralta
 */

#include "I2C_driver.h"
#include "NVIC.h"
#include "RTC.h"

uint8_t g_master_txBuff[I2C_DATA_LENGTH];
uint8_t g_master_rxBuff[I2C_DATA_LENGTH];
i2c_master_config_t g_masterConfig;
uint32_t g_sourceClock;
i2c_master_transfer_t g_masterXfer;

void i2c_master_init(void)
{
	CLOCK_EnableClock(kCLOCK_PortD);

	PORT_SetPinMux(PORTB, 2U, kPORT_MuxAlt2); /**SCL*/
	PORT_SetPinMux(PORTB, 3U, kPORT_MuxAlt2); /**SDA*/
	PORT_SetPinMux(PORTD, 0U, kPORT_MuxAsGpio); /**MFP*/

    BOARD_BootClockRUN();

    NVIC_set_basepri_threshold(PRIORITY_10); /**Limit for the priorities*/
    NVIC_enable_interrupt_and_priotity(PORTD_IRQ, PRIORITY_4); /**Set priority and enabling port D*/
    GPIO_callback_init(GPIO_D, add_one_second); /**Callback for MFP, couldn't find on SDK, using own GPIO drivers for this*/
    NVIC_global_enable_interrupts; /**Enabling NVIC*/

	I2C_MasterGetDefaultConfig(&g_masterConfig);
	g_masterConfig.baudRate_Bps = I2C_BAUDRATE;
	g_sourceClock = I2C_MASTER_CLK_FREQ;
	I2C_MasterInit(EXAMPLE_I2C_MASTER_BASEADDR, &g_masterConfig, g_sourceClock);
}

void i2c_master_write(uint8_t address, uint8_t data)
{
	g_master_txBuff[0] = data;
	uint8_t deviceAddress     = address;

	g_masterXfer.slaveAddress   = I2C_MASTER_SLAVE_ADDR_7BIT;
	g_masterXfer.direction      = kI2C_Write;
	g_masterXfer.subaddress     = (uint32_t)deviceAddress;
	g_masterXfer.subaddressSize = 1;
	g_masterXfer.data           = g_master_txBuff;
	g_masterXfer.dataSize       = I2C_DATA_LENGTH;
	g_masterXfer.flags          = kI2C_TransferDefaultFlag;

	I2C_MasterTransferBlocking(EXAMPLE_I2C_MASTER_BASEADDR, &g_masterXfer);
}

uint8_t i2c_master_read(uint8_t address)
{
	uint8_t deviceAddress     = address;
	g_masterXfer.slaveAddress   = I2C_MASTER_SLAVE_ADDR_7BIT;
	g_masterXfer.direction      = kI2C_Read;
	g_masterXfer.subaddress     = (uint32_t)deviceAddress;
	g_masterXfer.subaddressSize = 1;
	g_masterXfer.data           = g_master_rxBuff;
	g_masterXfer.dataSize       = I2C_DATA_LENGTH;
	g_masterXfer.flags          = kI2C_TransferDefaultFlag;

	I2C_MasterTransferBlocking(EXAMPLE_I2C_MASTER_BASEADDR, &g_masterXfer);

	return g_master_rxBuff[0];
}
