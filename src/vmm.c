#include "pmm.h"
#include "vmm.h"
#include <regs.h>

unsigned int *kernel_pd;
unsigned int *current_pd;

void vmm_map_pt (unsigned int *pd, unsigned int virt, unsigned int phys)
{
    if (!pd) pd = kernel_pd;
    
    printk ("[vmm] mapping PT in PD: %x\n", pd);
    unsigned int id = virt >> 22;
    
    if (!pd[id]) pd[id] = pmm_alloc () | 0x3;
    
    unsigned int *pt = (unsigned int *) (pd[id] & 0xfffff000);
    for (unsigned int i = 0; i < 1024; i++) {
        pt[i] = (phys + (i * 0x1000)) | 0x3;
    }
}

void vmm_map_pg (unsigned int *pd, unsigned int virt, unsigned int phys)
{
    if (!pd) pd = kernel_pd;
    
    unsigned int pt_id = virt >> 22;
    unsigned int pg_id = (virt << 10) >> 22;
    
    if (!pd[pt_id]) pd[pt_id] = pmm_alloc () | 0x3;
    
    unsigned int *pt = (unsigned int *) (pd[pt_id] & 0xfffff000);
    pt[pg_id] = phys | 0x3;
    __asm volatile("invlpg %0" : : "m" (*(char*)virt));
}

void vmm_enable_paging ()
{
    unsigned int cr0;
    __asm volatile ("mov %%cr0, %0" : "=r" (cr0));
    cr0 |= 0x80000000;
    __asm volatile ("mov %0, %%cr0" : : "r" (cr0));
}

unsigned int *vmm_create_pd ()
{
    unsigned int *pd = (unsigned int *) pmm_alloc ();
    pd[0] = pmm_alloc () | 0x3;
    unsigned int *pt = (unsigned int *) (pd[0] & 0xfffff000);
    for (unsigned int i = 0; i < 1024; i++) {
        pt[i] = (i * 0x1000) | 0x3;
    }
    pd[1023] = (unsigned int) pd | 0x3;
    
    return pd;
}

void vmm_switch_pd (unsigned int *pd)
{
    current_pd = pd;
    __asm volatile ("mov %0, %%cr3" : : "r" (pd));
}

unsigned int *vmm_get_current_pd ()
{
    return current_pd;
}

void vmm_init ()
{
    //make sure pmm_alloc() is page-aligned!
    kernel_pd = vmm_create_pd ();
    printk ("[vmm] kernel PD: %x\n", kernel_pd);
    vmm_switch_pd (kernel_pd);
    vmm_enable_paging ();
    
    printk("[vmm] init\n");
}