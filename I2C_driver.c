/*
 * I2C_driver.c
 *
 *  Created on: 22 mar 2022
 *      Author: Mauricio Peralta
 */

#include "I2C.h"

uint8_t g_master_txBuff[I2C_DATA_LENGTH];
uint8_t g_master_rxBuff[I2C_DATA_LENGTH];
i2c_master_config_t g_masterConfig;
uint32_t g_sourceClock;
i2c_master_transfer_t g_masterXfer;

void i2c_master_init(void)
{
	GPIO_clock_gating(GPIO_B);
	gpio_pin_control_register_t i2c_pin_config = GPIO_MUX2 | GPIO_PE;
	GPIO_pin_control_register(GPIO_B,bit_2,  &i2c_pin_config); /**SCL*/
	GPIO_data_direction_pin(GPIO_B, GPIO_OUTPUT,  bit_2);
	GPIO_pin_control_register(GPIO_B,bit_3,  &i2c_pin_config); /**SDA*/
	GPIO_data_direction_pin(GPIO_B, GPIO_OUTPUT,  bit_3);
    BOARD_BootClockRUN();

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