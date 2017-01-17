#ifndef MONITOR_H
#define MONITOR_H

void monitor_put(char c);
void monitor_clear();
void monitor_write(char *c);
void monitor_write_hex(unsigned int n);
void monitor_write_dec(unsigned int n);
int printk( const char *fmt, ... );

#endif