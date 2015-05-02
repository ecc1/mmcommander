#include "hal_led.h"
#include "hal_mcu.h"

void blink(int count, int period_ms) {
    int n = 2 * count;
    int delay = period_ms / 2;
    do {
        halLedToggle(0);
        halMcuWaitMs(delay);
    } while (--n);
}
