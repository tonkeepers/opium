#ifndef OPIUM_PROCESS_CONTROL_INCLUDED_H
#define OPIUM_PROCESS_CONTROL_INCLUDED_H

#include "core/opium_core.h"

typedef struct {
   opium_process_cpu_t    cpu;
   opium_process_memory_t mem;


} opium_process_entrails_t;

void        opium_process_entrails_sync(opium_process_entrails_t *entrails, opium_pid_t pid);
opium_s32_t opium_process_entrails_init(opium_process_entrails_t *entrails, opium_pid_t pid);

#endif /* OPIUM_PROCESS_CONTROL_INCLUDED_H */
