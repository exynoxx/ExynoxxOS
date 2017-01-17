#ifndef HEAP_H
#define HEAP_H

typedef struct {
    char status;
    unsigned int size;
} __attribute__((packed)) heap_block;

void free(void *mem);
char* malloc(unsigned int size);
void heap_init (unsigned int addr);

#endif