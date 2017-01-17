#ifndef DT_H
#define DT_H

typedef struct tss_entry_struct
{
    unsigned int prev_tss;   // The previous TSS - if we used hardware task switching this would form a linked list.
    unsigned int esp0;       // The stack pointer to load when we change to kernel mode.
    unsigned int ss0;        // The stack segment to load when we change to kernel mode.
    unsigned int esp1;       // everything below here is unusued now..
    unsigned int ss1;
    unsigned int esp2;
    unsigned int ss2;
    unsigned int cr3;
    unsigned int eip;
    unsigned int eflags;
    unsigned int eax;
    unsigned int ecx;
    unsigned int edx;
    unsigned int ebx;
    unsigned int esp;
    unsigned int ebp;
    unsigned int esi;
    unsigned int edi;
    unsigned int es;
    unsigned int cs;
    unsigned int ss;
    unsigned int ds;
    unsigned int fs;
    unsigned int gs;
    unsigned int ldt;
    unsigned short trap;
    unsigned short iomap_base;
    
} __attribute__((packed)) tss_entry;

void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);
void gdt_install();
void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
void idt_install();
static void write_tss(int num, unsigned short ss0, unsigned int esp0);
void set_kernel_stack(unsigned int stack);

#endif