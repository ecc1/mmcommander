/*
 * print "Hello, world!" over UART
 */
#include "clock.h"
#include "hal_board.h"
#include "cc1111.h"
#include <stdio.h>

extern void blink(int, int);

int main(void)
{
    int counter = 0;

    P1DIR |= BIT1;  // set output for LED on P1_1

    clockSetMainSrc(CLOCK_SRC_XOSC);

    // set up UART0 using Alternative Location 1
    PERCFG &= ~PERCFG_U0CFG_ALT_MASK;
    PERCFG |= PERCFG_U0CFG_ALT_1;

    U0CSR |= UxCSR_MODE_UART;

    // TX on P0_3, RX on P0_2
    P0SEL |= BIT2 | BIT3;
    P0DIR &= ~BIT2; P0DIR |= BIT3;

    // 9600 baud
    U0BAUD = 163;
    U0GCR = 8;
    U0UCR = (UxUCR_FLUSH |
             UxUCR_FLOW_DISABLE |
             UxUCR_D9_EVEN_PARITY |
             UxUCR_BIT9_8_BITS |
             UxUCR_PARITY_DISABLE |
             UxUCR_SPB_1_STOP_BIT |
             UxUCR_STOP_HIGH |
             UxUCR_START_LOW);

    while (1) {
        printf("Hello, world from CC1111! (%u)\r\n", ++counter);
        blink(3, 300);
    }
}

void putchar(char c) {
    U0DBUF = c;
    while (!UTX0IF)
        NOP();
    UTX0IF = 0;
}
