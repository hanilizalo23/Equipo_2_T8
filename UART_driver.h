/*
 * UART_driver.c
 *
 *  Created on: 21 mar 2022
 *      Author: Nelida Hernández
 */

#include "fsl_uart.h"

#ifndef UART_H_
#define UART_H_

void UART_init(void); /**Function who initialize everything**/
void UART_loop(void); /**Function for configure the menu and refresh it**/
void UART_UserCallback(UART_Type *base, uart_handle_t *handle, status_t status, void *userData); /**Callback that might help, from SDK*/

#endif /* UART_H_ */
