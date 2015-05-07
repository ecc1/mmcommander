// Listen for Medtronic packets and print them over the UART

#include <stdio.h>
#include <stdint.h>
#include <cc1110.h>
#include "constants.h"
#include "crc_4b6b.h"
#include "init.h"
#include "interrupts.h"
#include "medtronicRF.h"
#include "serial.h"

// SDCC requires interrrupt handlers to be declared
// in the file that defines main()

extern void PORT1_ISR(void) __interrupt (P1INT_VECTOR);
extern void TIMER1_ISR(void) __interrupt (T1_VECTOR);

uint8_t  __xdata uartRxBuffer[SIZE_OF_UART_RX_BUFFER];
uint8_t  __xdata uartTxBuffer[SIZE_OF_UART_TX_BUFFER];
int      __xdata uartTxLength;
int      __xdata uartTxIndex;
int      __xdata uartRxIndex;

int main(void)
{
    static uint8_t __xdata dataPacket[256];
    char dataErr;
    unsigned int dataLength;
    char i;

    /* Configure system */
    initGlobals();
    configureIO();
    configureOsc();
    serial_init();
    crc16Init();
    configureMedtronicRFMode();
    enablePushButtonInt();
    
    /* Reception loop */
    while (1) {
        dataErr = receiveMedtronicMessage(dataPacket, &dataLength); 
        printf("len = %d, err = %d\r\n", dataLength, dataErr);
        for (i=0; i<dataLength; i++)
            printf("%02X ", dataPacket[i]);
        printf("\r\n");
    }
}

void putchar(char c) {
    serial_putc(c);
}
