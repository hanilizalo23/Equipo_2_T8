/*
 * RTC.c
 *
 *  Created on: 22 mar 2022
 *      Author: Mauricio Peralta
 */

#include "RTC.h"
#include "I2C.h"

void set_12_or_24(is_12_or_24_t select)
{
	uint8_t temp = 0;
	temp = i2c_master_read(HOUR_ADDRESS);
	if(select)
	{
		i2c_master_write(HOUR_ADDRESS,(temp | SET_12));
	}
	else
	{
		i2c_master_write(HOUR_ADDRESS,(temp & SET_24));
	}
}

void set_AM_or_PM(AM_or_PM_t select)
{
	uint8_t temp = 0;
	temp = i2c_master_read(HOUR_ADDRESS);
	if(select)
	{
		i2c_master_write(HOUR_ADDRESS,(temp & PM_SET ));
	}
	else
	{
		i2c_master_write(HOUR_ADDRESS,(temp | AM_SET));
	}
}

void set_hour(uint8_t hour)
{

	uint8_t temp = 0;
	temp = i2c_master_read(HOUR_ADDRESS);
	temp &= CLEAR_HOUR;
	temp |= (hour & HOUR_READ_MASK);
	i2c_master_write(HOUR_ADDRESS,temp);
}

void set_minute(uint8_t minute)
{
	i2c_master_write(MIN_ADDRESS,minute);
}

