/*
 * I2C_driver.h
 *
 *  Created on: 22 mar 2022
 *      Author: Mauricio Peralta
 */

#ifndef I2C_H_
#define I2C_H_

#include <string.h>
#include "pin_mux.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_i2c.h"
#include "GPIO.h"
#include "Bits.h"

#define I2C_MASTER_CLK_SRC          I2C0_CLK_SRC
#define I2C_MASTER_CLK_FREQ         CLOCK_GetFreq(I2C0_CLK_SRC)
#define EXAMPLE_I2C_MASTER_BASEADDR I2C0

#define I2C_MASTER_SLAVE_ADDR_7BIT 0x6FU
#define I2C_BAUDRATE               100000U
#define I2C_DATA_LENGTH            1U

void i2c_master_init(void); /**Initialize*/


#endif /* I2C_H_ */
