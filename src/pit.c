#include "pit.h"
#include "libc.h"


//IRQ0 fire frequency (interrupt_s.s)
void pit_init (unsigned int hz)
{
    u32 divisor = 1193180 / hz;
    outb(0x43, 0x36); // Send the command byte.
    u8 l = (u8)(divisor & 0xFF);
    u8 h = (u8)( (divisor>>8) & 0xFF );
    outb(0x40, l);
    outb(0x40, h);
}