#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <regs.h>

void interrupt_install();
void irq_install_handler(int irq, void (*handler)(struct regs *r));
void irq_uninstall_handler(int irq);

#endif