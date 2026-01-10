#include "core/opium_core.h"

#define OPIUM_CPU_NICE_MIN sched_get_priority_min(SCHED_OTHER)
#define OPIUM_CPU_NICE_MAX sched_get_priority_max(SCHED_OTHER)

static opium_s32_t cpu_nice_apply(opium_pid_t pid, opium_s32_t nice)
{
   if (nice < OPIUM_CPU_NICE_MIN || nice > OPIUM_CPU_NICE_MAX) {
      return OPIUM_RET_ERR;
   }

   if (setpriority(PRIO_PROCESS, pid, nice) == -1) {
      return OPIUM_RET_ERR;
   }

   return OPIUM_RET_OK;
}

static opium_s32_t cpu_nice_get(opium_pid_t pid)
{
   return getpriority(PRIO_PROCESS, pid);
} 

static opium_s32_t cpu_policy_apply(opium_pid_t pid, opium_s32_t policy)
{
   struct sched_param param;
   opium_s32_t        result;

   opium_memzero(&param, sizeof(param));
   param.sched_priority = 1;

   result = sched_setscheduler(pid, policy, &param);
   if (result < 0) {
      return OPIUM_RET_ERR;
   }

   return OPIUM_RET_OK;
}

static opium_s32_t cpu_policy_get(opium_pid_t pid)
{
   return sched_getscheduler(pid);
}

static opium_s32_t cpu_affinity_apply(opium_pid_t pid, opium_cpuset_t *mask)
{
   if (sched_setaffinity(pid, sizeof(*mask), mask) < 0) {
      return OPIUM_RET_ERR;
   }

   return OPIUM_RET_OK;
}

static opium_s32_t cpu_affinity_get(opium_pid_t pid, opium_cpuset_t *set)
{
   CPU_ZERO(set);

   if (sched_getaffinity(pid, sizeof(*set), set) < 0) {
      return OPIUM_RET_ERR;
   }

   return OPIUM_RET_OK;
}

   void 
opium_process_cpu_sync(opium_process_cpu_t *cpu, opium_pid_t pid)
{
   cpu->nice = cpu_nice_get(pid);

   cpu->policy = cpu_policy_get(pid);

   cpu_affinity_get(pid, &cpu->affinity);
}

   opium_s32_t 
opium_process_cpu_apply(opium_process_cpu_t *cpu, opium_pid_t pid)
{
   opium_s32_t result;

   if (cpu->flags & OPIUM_CPU_F_NICE) {
      result = cpu_nice_apply(pid, cpu->nice); 
      if (result != OPIUM_RET_OK) {
         return result;
      }

      cpu->flags = cpu->flags & ~OPIUM_CPU_F_NICE;
   }

   if (cpu->flags & OPIUM_CPU_F_POLICY) {
      result = cpu_policy_apply(pid, cpu->policy);
      if (result != OPIUM_RET_OK) {
         return result;
      }

      cpu->flags = cpu->flags & ~OPIUM_CPU_F_POLICY;
   }

   if (cpu->flags & OPIUM_CPU_F_AFFINITY) {
      result = cpu_affinity_apply(pid, &cpu->affinity); 
      if (result != OPIUM_RET_OK) {
         return result;
      }

      cpu->flags = cpu->flags & ~OPIUM_CPU_F_AFFINITY;
   }

   return OPIUM_RET_OK;
}

   opium_s32_t 
opium_process_cpu_nice_set(opium_process_cpu_t *cpu, opium_s32_t nice)
{
   cpu->nice  = nice;
   cpu->flags = cpu->flags | OPIUM_CPU_F_NICE;

   return OPIUM_RET_OK;
}

   opium_s32_t
opium_process_cpu_nice_get(opium_process_cpu_t *cpu)
{
   return cpu->nice;
}

   opium_s32_t 
opium_process_cpu_policy_set(opium_process_cpu_t *cpu, opium_s32_t policy)
{
   cpu->policy = policy;
   cpu->flags  = cpu->flags | OPIUM_CPU_F_POLICY;

   return OPIUM_RET_OK;
}

   opium_s32_t
opium_process_cpu_policy_get(opium_process_cpu_t *cpu)
{
   return cpu->policy;
}

   opium_s32_t
opium_process_cpu_affinity_set(opium_process_cpu_t *cpu, opium_u64_t *mask, size_t n)
{
   opium_cpuset_t affinity;
   CPU_ZERO(&affinity);

   for (size_t index = 0; index < n; index++) {
      CPU_SET(mask[index], &affinity);
   }

   cpu->affinity = affinity;
   cpu->flags    = cpu->flags | OPIUM_CPU_F_AFFINITY;

   return OPIUM_RET_OK;
}

   opium_cpuset_t 
opium_process_cpu_affinity_get(opium_process_cpu_t *cpu)
{
   return cpu->affinity;
}
