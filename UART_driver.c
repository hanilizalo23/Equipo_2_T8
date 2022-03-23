/*
 * UART_driver.c
 *
 *  Created on: 21 mar 2022
 *      Author: Nelida Hernández
 */

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_uart.h"
#include "Bits.h"
#include "UART_driver.h"
#include <stdio.h>

#define DEMO_UART          UART0
#define DEMO_UART_CLKSRC   UART0_CLK_SRC
#define DEMO_UART_CLK_FREQ CLOCK_GetFreq(UART0_CLK_SRC)

#define KEY_ONE 49
#define KEY_TWO 50
#define KEY_ESC 27

typedef enum{MAIN_MENU, CLOCK, SET_CLOCK} function_t;
typedef enum{OFF, ON} functionality_state_t;

void UART_init(void)
{
    uart_config_t config;

    UART_GetDefaultConfig(&config);
    config.baudRate_Bps = BOARD_DEBUG_UART_BAUDRATE;
    config.enableTx     = true;
    config.enableRx     = true;

    UART_Init(DEMO_UART, &config, DEMO_UART_CLK_FREQ);

	CLOCK_EnableClock(kCLOCK_PortB);

	PORT_SetPinMux(PORTB, 16U, kPORT_MuxAlt3);

	PORT_SetPinMux(PORTB, 17U, kPORT_MuxAlt3);

	SIM->SOPT5 = ((SIM->SOPT5 & (~(SIM_SOPT5_UART0TXSRC_MASK))) | SIM_SOPT5_UART0TXSRC(SOPT5_UART0TXSRC_UART_TX));
}

void UART_loop(void)
{
    function_t function_state = MAIN_MENU;
    functionality_state_t functionality_state = TRUE;

    uint8_t key_pressed;

    while(1)
    {

    }
}
