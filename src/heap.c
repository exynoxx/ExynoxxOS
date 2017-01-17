#include "heap.h"
#include "vmm.h"

unsigned int *heap_start;
unsigned int index_alloc;

void free(void *mem)
{
    heap_block *alloc = (mem - sizeof(heap_block));
    alloc->status = 0;
}

char* mallocnew (unsigned int size)
{
    heap_block *alloc = (heap_block *)index_alloc;
    alloc->status = 1;
    alloc->size = size;
    
    index_alloc += size;
    index_alloc += sizeof(heap_block);
    
    return (char *)((unsigned int)alloc + sizeof(heap_block));
}

char* malloc(unsigned int size)
{
    char *mem = (char *) heap_start;
    while((unsigned int)mem < index_alloc)
    {
        heap_block *a = (heap_block *)mem;
        
        if(!a->size)
            return mallocnew (size);
        
        if(a->status) {
            mem += a->size;
            mem += sizeof(heap_block);
            continue;
        }
        
        if(a->size < size)
        {
            mem += a->size;
            mem += sizeof(heap_block);
            continue;
        }
        
        a->status = 1;
        return (char *)(mem + sizeof(heap_block));
    }
    return mallocnew (size);
}

void heap_init (unsigned int addr)
{
    heap_start = (unsigned int *) addr;
    index_alloc = heap_start;
    
    printk ("[heap] start: %x\n", heap_start);
    printk ("[heap] init\n");
}



