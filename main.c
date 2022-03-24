/*
 *
 *  Created on: 21 mar 2022
 *      Author: Nelida Hernández & Mauricio Peralta
 */

#include "GPIO.h"
#include "Bits.h"
#include "I2C_driver.h"
#include "RTC.h"
#include "UART_driver.h"

#include <stdio.h>
#include <stdint.h>
#include "MK64F12.h"

int main (void)
{
	BOARD_InitDebugConsole();
	UART_init();
	UART_loop();
	i2c_master_init();

	while (1)
	{

	}
    return 0;
}
