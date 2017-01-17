#ifndef PMM_H
#define PMM_H

#include <multiboot.h>

unsigned int pmm_alloc ();
void         pmm_init (unsigned int addr);

#endif
