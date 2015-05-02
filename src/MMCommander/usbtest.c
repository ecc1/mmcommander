
/***********************************************************************************
  Filename:     usbtest.c

  Description:  test USB serial port

***********************************************************************************/

/***********************************************************************************
* INCLUDE
*/
#include "init.h"
#include "constants.h"
#include "interrupts.h"
#include "hal_board.h"
#include "hal_led.h"
#include "hal_mcu.h"
#include "hal_uart.h"
#include "usb_uart.h"
#include "configuration.h"
#include "util_buffer.h"
#include <stdio.h>

/******************************************************************************
* ISR declarations
* SDCC requires these to be in the file that defines main()
*/

extern void PORT1_ISR(void) __interrupt (P1INT_VECTOR);
extern void usbirqResumeHandler(void) __interrupt (P0INT_VECTOR);
extern void usbirqHandler(void) __interrupt (P2INT_VECTOR);
extern void TIMER1_ISR(void) __interrupt (T1_VECTOR);

/******************************************************************************
* GLOBAL VARIABLES
*/

uint8  __xdata uartRxBuffer[SIZE_OF_UART_RX_BUFFER];
uint8  __xdata uartTxBuffer[SIZE_OF_UART_TX_BUFFER];
int    __xdata uartTxLength;
int    __xdata uartTxIndex;
int    __xdata uartRxIndex;

/******************************************************************************
* MAIN FUNCTION
*/

int main(void)
{
    /* Configure system */
    initGlobals();
    configureIO();
    configureOsc();
    halUartInit(HAL_UART_BAUDRATE_57600, 0);

    while (1) {
        printf("Hello, world from CC1111!\r\n");
        usbUartProcess();
        halMcuWaitMs(1000);
    }
}

extern ringBuf_t __xdata rbTxBuf;

void putchar(char c) {
    if (bufNumBytes(&rbTxBuf) != 0)
        halUartWrite(&c, 1);
}
