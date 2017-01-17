#ifndef MULTIBOOT_H
#define MULTIBOOT_H

struct multiboot
{
	unsigned int *flags;
	unsigned int *mem_lower;
	unsigned int *mem_upper;
	unsigned int *boot_device;
	unsigned int *cmdline;
	unsigned int *mods_count;
	unsigned int *mods_addr;
	unsigned int *num;
	unsigned int *size;
	unsigned int *addr;
	unsigned int *shndx;
	unsigned int *mmap_length;
	unsigned int *mmap_addr;
	unsigned int *drives_length;
	unsigned int *drives_addr;
	unsigned int *config_table;
	unsigned int *boot_loader_name;
	unsigned int *apm_table;
	unsigned int *vbe_control_info;
	unsigned int *vbe_mode_info;
	unsigned int *vbe_mode;
	unsigned int *vbe_interface_seg;
	unsigned int *vbe_interface_off;
	unsigned int *vbe_interface_len;
} __attribute__ ((packed));

typedef struct multiboot_memory_map {
	unsigned int size;
	unsigned int base_addr_low;
	unsigned int base_addr_high;
	unsigned int length_low;
	unsigned int length_high;
	unsigned int type;
} multiboot_mmap;

typedef struct multiboot_module {
    unsigned int mod_start;
    unsigned int mod_end;
    unsigned int string;
    unsigned int reserved;
} multiboot_mod;

#endif