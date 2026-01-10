#ifndef OPIUM_PROCESS_CPU_INCLUDED_H
#define OPIUM_PROCESS_CPU_INCLUDED_H

#include "core/opium_core.h"

typedef enum {
   OPIUM_CPU_F_NICE     = 1 << 0,
   OPIUM_CPU_F_POLICY   = 1 << 1,
   OPIUM_CPU_F_AFFINITY = 1 << 2,
} opium_process_cpu_flags_t;

typedef struct {
   opium_s32_t    nice;
   opium_s32_t    policy;
   opium_cpuset_t affinity;

   opium_u32_t    flags;
} opium_process_cpu_t;

void        opium_process_cpu_sync(opium_process_cpu_t *cpu, opium_pid_t pid);
opium_s32_t opium_process_cpu_apply(opium_process_cpu_t *cpu, opium_pid_t pid);

opium_s32_t    opium_process_cpu_nice_set(opium_process_cpu_t *cpu, opium_s32_t nice);
opium_s32_t    opium_process_cpu_nice_get(opium_process_cpu_t *cpu);

opium_s32_t    opium_process_cpu_policy_set(opium_process_cpu_t *cpu, opium_s32_t policy);
opium_s32_t    opium_process_cpu_policy_get(opium_process_cpu_t *cpu);

opium_s32_t    opium_process_cpu_affinity_set(opium_process_cpu_t *cpu, opium_u64_t *mask, size_t n);
opium_cpuset_t opium_process_cpu_affinity_get(opium_process_cpu_t *cpu);

#endif /* OPIUM_PROCESS_CPU_INCLUDED_H */
