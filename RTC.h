/*
 * RTC.c
 *
 *  Created on: 22 mar 2022
 *      Author: Mauricio Peralta
 */

#ifndef RTC_H_
#define RTC_H_

#include "I2C.h"

#define SEC_ADDRESS 0x00U
#define MIN_ADDRESS 0x01U
#define HOUR_ADDRESS 0x02U
#define HOUR_READ_MASK (0x1FU)
#define AM_SET (0x20U)
#define PM_SET (0XDFU)
#define SET_24 (0xBFU)
#define SET_12 (0x40U)
#define CLEAR_HOUR (0x60U)

typedef enum {
	TFOUR,
	TWELVE
} is_12_or_24_t;


typedef enum {
	AM,
	PM
} AM_or_PM_t;

void set_12_or_24(is_12_or_24_t select); /**Setter for hour format*/
void set_AM_or_PM(AM_or_PM_t select); /**Setter for hour format*/
void set_hour(uint8_t hour); /*Setter for hour*/
void set_minute(uint8_t minute); /**Setter for minute*/

#endif /* RTC_H_ */
