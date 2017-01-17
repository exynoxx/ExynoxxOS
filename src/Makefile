SOURCES = bootstrap.o
SOURCES += dt.o
SOURCES += interrupt.o
SOURCES += interrupt_s.o
SOURCES += monitor.o
SOURCES += printk.o
SOURCES += libc.o
SOURCES += pit.o
SOURCES += task.o
SOURCES += pmm.o
SOURCES += vmm.o
SOURCES += heap.o

CC=/opt/local/bin/i386-elf-gcc
LD=/opt/local/bin/i386-elf-ld


CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector -m32 -I ../include -std=c99 -O
LDFLAGS=-Tlink.ld -melf_i386
ASFLAGS=-felf

all: $(SOURCES) main link

clean:
	rm *.o #../bin/kernel.bin
	clear

link:
	$(LD) $(LDFLAGS) -o ../bin/kernel.bin $(SOURCES) main.o

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

.s.o:
	nasm $(ASFLAGS) $<

main:
	$(CC) -nostdlib -nostdinc -fno-builtin -fno-stack-protector -m32 -I ../include -std=c99 -o main.o -c main.c

andrun: all main run

run:
	qemu-system-i386 -kernel ../bin/kernel.bin -m 1G
