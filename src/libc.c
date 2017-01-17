#include "libc.h"

void *memcpy(void *dest, const void *src, int count)
{
    const char *sp = (const char *)src;
    char *dp = (char *)dest;
    for(; count != 0; count--) *dp++ = *sp++;
    return dest;
}

void *memset(void *dest, char val, int count)
{
    char *temp = (char *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, int count)
{
    unsigned short *temp = (unsigned short *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

int strlen(const char *str)
{
    int retval;
    for(retval = 0; *str != '\0'; str++) retval++;
    return retval;
}

int strcmp(char *str1, char *str2)
{
    while (*str1 && *str2 && (*str1++ == *str2++));
    
    if (*str1 == '\0' && *str2 == '\0')
        return 0;
    
    if (*str1 == '\0')
        return -1;
    else return 1;
}

unsigned char inb (unsigned short port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (port));
    return rv;
}

void outb (unsigned short port, unsigned char data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (port), "a" (data));
}

void cli ()
{
    __asm__ __volatile__ ("cli");
}
void sti ()
{
    __asm__ __volatile__ ("sti");
}

void sitoa( char *buf, int base, int d )
{
    char *p = buf;
    char *p1, *p2;
    unsigned long ud = d;
    int divisor = 10;
    
    if(base == 10 && d < 0)
    {
        *p++ = '-';
        buf++;
        ud = -d;
        
    }
    else if(base == 16)
        divisor = 16;
    else if ( base == 2 )
    {
        divisor = base;
        
    }
    
    do
    {
        int remainder = ud % divisor;
        
        *p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
        //length--;
    }
    while(ud /= divisor);
    *p = 0;
    
    p1 = buf;
    p2 = p - 1;
    while(p1 < p2)
    {
        char tmp = *p1;
        
        *p1 = *p2;
        *p2 = tmp;
        p1++;
        p2--;
    }
}