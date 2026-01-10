#ifndef OPIUM_PROCESS_PEDIGREE_INCLUDED_H
#define OPIUM_PROCESS_PEDIGREE_INCLUDED_H

#include "core/opium_core.h"

#define OPIUM_MAX_PROCESSES 1024 

typedef opium_s32_t (*opium_process_main_t)(void *data);

typedef struct {
   void       *parent;
   void       *children[OPIUM_MAX_PROCESSES];
   opium_s32_t children_count;
} opium_process_pedigree_t;

opium_pid_t opium_process_spawn(opium_process_pedigree_t *pedigree, char *name, void *data,
      opium_process_main_t main, opium_log_t *log);

void opium_process_parent_set(opium_process_t *process, opium_process_t *parent);
void opium_process_child_add(opium_process_t *parent, opium_process_t *child);
void opium_process_child_del(opium_process_t *parent, opium_process_t *child);

#endif /* OPIUM_PROCESS_PEDIGREE_INCLUDED_H */
