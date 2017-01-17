#ifndef VMM_H
#define VMM_H

void            vmm_map_pt (unsigned int *pd, unsigned int virt, unsigned int phys);
void            vmm_map_pg (unsigned int *pd, unsigned int virt, unsigned int phys);
unsigned int   *vmm_create_pd ();
void            vmm_switch_pd (unsigned int *pd);
unsigned int   *vmm_get_current_pd ();
void            vmm_init();

#endif