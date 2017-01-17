#include "task.h"
#include "libc.h"

unsigned int id = 0;
unsigned int current_pid = 0;
unsigned int tasking_status = 0;
unsigned int heap_phys = 0;

void task_create (void (*entry)())
{
    cli ();
    unsigned int pd = (unsigned int) vmm_create_pd ();
    unsigned int tmp = (unsigned int) malloc (0x1000);
    unsigned int *stack = (unsigned int *) tmp + 0x1000;
    
    // processor data (iret)
    *--stack = 0x202;               // EFLAGS
    *--stack = 0x08;                // CS
    *--stack = (unsigned int) entry;// EIP
    
    // pusha
    *--stack = 0;		// EDI
    *--stack = 0;		// ESI
    *--stack = 0;		// EBP
    *--stack = 0;		// NULL
    *--stack = 0;		// EBX
    *--stack = 0;		// EDX
    *--stack = 0;		// ECX
    *--stack = 0;		// EAX
    
    // data segments
    *--stack = 0x10;	// DS
    *--stack = 0x10;	// ES
    *--stack = 0x10;	// FS
    *--stack = 0x10;	// GS
    
    //find task in structure
    unsigned int i = 0;
    while (task_list[i].state == TASK_READY) {
        i++;
    }
    
    id++;
    
    task_list[i].pid = id;
    task_list[i].state = TASK_READY;
    task_list[i].esp0 = (unsigned int) stack;
    task_list[i].cr3 = pd;
    
    vmm_switch_pd (pd);
    
    //this works. try it out first.
    vmm_map_pt ((unsigned int *)pd, 0xC0000000, heap_phys);
    
    sti ();
    
    printk ("[task] PD: %x. created PID: %i. esp: %x\n", pd, id, (unsigned int) stack);
}

//called from IRQ0 (interrupt_s.s)
unsigned int task_switch (unsigned int esp)
{
    if (!tasking_status) {
        return esp;
    }
    
    unsigned int cr3;
    __asm volatile("mov %%cr3, %0" : "=r" (cr3));
    task_list[current_pid].cr3 = cr3;
    task_list[current_pid].esp0 = esp;
    
    current_pid++;
    
    if (task_list[current_pid].state == TASK_NULL) {
        current_pid = 0;
    }
    
    __asm volatile("mov %0, %%cr3" : : "r" (task_list[current_pid].cr3));
    //printk ("##switch| %x |\n", task_list[current_pid].cr3);
    return task_list[current_pid].esp0;
}

unsigned int get_current_task_id ()
{
    return current_pid;
}

void task_start ()
{
    tasking_status = 1;
    current_pid = 0;
    
    vmm_switch_pd (task_list[current_pid].cr3);
    __asm volatile("mov %%eax, %%esp": :"a"(task_list[current_pid].esp0));
    __asm volatile("pop %gs");
    __asm volatile("pop %fs");
    __asm volatile("pop %es");
    __asm volatile("pop %ds");
    __asm volatile("popa");
    __asm volatile("iret");
}

void task_stop ()
{
    tasking_status = 0;
}

void task_init (unsigned int heap_loc)
{
    for (unsigned int j = 0; j <= 10; j++) {
        task_list[j].state = TASK_NULL;
        task_list[j].pid = 0;
    }
    
    heap_phys = heap_loc;
    
    printk ("[task] init\n");
}