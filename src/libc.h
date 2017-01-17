#ifndef LIBC_H
#define LIBC_H

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;

void *memcpy(void *dest, const void *src, int count);
void *memset(void *dest, char val, int count);
unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);
int strlen(const char *str);
int strcmp(char *str1, char *str2);
unsigned char inb (unsigned short port);
void outb (unsigned short port, unsigned char data);
void cli ();
void sti ();
void sitoa( char *buf, int base, int d );

#endif