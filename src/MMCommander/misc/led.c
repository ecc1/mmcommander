#include <stdint.h>
#include <cc1110.h>
#include "delay.h"

void led_init(void) {
    P1DIR |= (1 << 1);  // set output for LED on P1_1
}

void blink_once(uint16_t period_ms) {
    uint16_t half = period_ms / 2;
    P1_1 ^= 1;
    delay(half);
    P1_1 ^= 1;
    delay(half);
}

void blink(uint16_t period_ms, uint16_t count) {
    uint16_t n = count;
    while (n-- || count == 0)
        blink_once(period_ms);
}
