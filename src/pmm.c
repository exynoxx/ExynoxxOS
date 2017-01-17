#include <multiboot.h>
#include "pmm.h"
#include "libc.h"

unsigned int bitmap[32];
unsigned int offset;

unsigned int pmm_alloc ()
{
    unsigned int i = 0;
    unsigned int j = 0;
    
    while(bitmap[i] == 0xFFFFFFFF)
    {
        i++;
    }
    
    for (; j <= 31; j++) {
        if ((bitmap[i] & (1 << j)) == 0)
        {
            break;
        }
    }
    
    bitmap[i] |= (1 << j); //(set bit) this area is now reserved
    
    return offset + ((i * 32) + j) * 4096;
}

void pmm_init (unsigned int addr)
{
    offset = addr;
    printk("[pmm] init\n");
}
