#include "libc.h"
#include "dt.h"
#include "interrupt.h"
#include "monitor.h"
#include "task.h"
#include "pit.h"
#include <multiboot.h>
#include "heap.h"

extern int end;
unsigned int kernelend = (unsigned int) &end;

int aa = 1;
int bb = 0;
int cc = 0;

void a ()
{
    while (1){
        
        if (aa) {
            printk ("a.");
            aa = 0;
            bb = 1;
        }
    }
}
void b ()
{
    while (1){
        
        if (bb) {
            printk ("b.");
            bb = 0;
            cc = 1;
            
        }
        
    }
}
void c ()
{
    while (1){
        
        if (cc) {
            printk ("c.");
            cc = 0;
            aa = 1;
        }
    }
}

void main(struct multiboot *mboot, unsigned int esp)
{
    kernelend = (unsigned int) ((kernelend + 0x1000) & 0xfffff000);
    
    gdt_install();
    idt_install();
    interrupt_install();
    monitor_clear();
    
    printk ("Stack: %x\n", esp);
    
    pit_init (200);
    pmm_init (kernelend);
    vmm_init ();
    
    vmm_map_pt (0, 0xC0000000, 0x10000000);
    heap_init (0xC0000000);
    
    task_init (0x10000000);
    task_create (a);
    task_create (b);
    task_create (c);
    task_start ();
    
    for (;;);
}
