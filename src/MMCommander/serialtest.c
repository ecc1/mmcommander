// Print "Hello, world!" over UART

#include <stdio.h>
#include "clock.h"
#include "led.h"
#include "serial.h"

int main(void) {
    int counter = 0;

    clockSetMainSrc(CLOCK_SRC_XOSC);
    led_init();
    serial_init();

    while (1) {
        printf("Hello, world from CC1111! (%u)\r\n", ++counter);
        blink(333, 3);
    }
}

void putchar(char c) {
    serial_putc(c);
}
