#include "timer.h"

void TimerCallback(struct ptRegs_t *regs)
{
    static unsigned int tick = 0;
    printkWithColor(black, magenta, "Tick: %d\n", tick++);
}

void initTimer(unsigned int frequency)
{
    registerInterruptHander(IRQ0, TimerCallback);
    unsigned int divisor = 1193180 / frequency;

    writeByte(0x43, 0x36);
    unsigned char low = (unsigned char)(divisor & 0xFF);
    unsigned char high = (unsigned char)((divisor >> 8) & 0xFF);

    writeByte(0x40, low);
    writeByte(0x40, high);
}