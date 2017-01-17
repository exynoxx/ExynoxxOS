#ifndef TASK_H
#define TASK_H

typedef enum {TASK_READY, TASK_NULL, TASK_DIE} task_state;
typedef struct _task task;

struct _task {
    unsigned char pid;
    task_state    state;
    unsigned int  esp0;
    unsigned int  cr3;
};

task task_list[30];

void task_create (void (*entry)());
unsigned int get_current_task_id ();
void print_next_ids (unsigned int x);
void task_start ();
void task_stop ();
void task_init (unsigned int heap_loc);

#endif