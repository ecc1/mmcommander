// Print "hello, world" over USB serial port

#include <stdio.h>
#include "delay.h"
#include "serial.h"
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

// SDCC requires interrrupt handlers to be declared
// in the file that defines main()

extern void PORT1_ISR(void) __interrupt (P1INT_VECTOR);
extern void usbirqResumeHandler(void) __interrupt (P0INT_VECTOR);
extern void usbirqHandler(void) __interrupt (P2INT_VECTOR);
extern void TIMER1_ISR(void) __interrupt (T1_VECTOR);

uint8  __xdata uartRxBuffer[SIZE_OF_UART_RX_BUFFER];
uint8  __xdata uartTxBuffer[SIZE_OF_UART_TX_BUFFER];
int    __xdata uartTxLength;
int    __xdata uartTxIndex;
int    __xdata uartRxIndex;

static int usb_ready = 0;

int main(void)
{
    int counter = 0;

    /* Configure system */
    initGlobals();
    configureIO();
    configureOsc();
    serial_init();
    printf("initializing USB ... ");
    halUartInit(HAL_UART_BAUDRATE_57600, 0);
    printf("done.\r\n");
    usb_ready = 1;

    while (1) {
        printf("Hello, world from CC1111! (%u)\r\n", ++counter);
        usbUartProcess();
        delay(1000);
    }
}

extern ringBuf_t __xdata rbTxBuf;

void putchar(char c) {
    serial_putc(c);
    if (usb_ready && bufNumBytes(&rbTxBuf) != 0)
        halUartWrite(&c, 1);
}
