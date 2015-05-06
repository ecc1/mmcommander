#include <stdint.h>

#define nop()	__asm nop __endasm

void delay(uint16_t msec)
{
    while (msec--) {
        uint16_t n = 825;  // determined empirically
        while (n--)
            nop();
    }
}
