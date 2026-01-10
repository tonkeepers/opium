#include "core/opium_core.h"

   void
opium_process_entrails_sync(opium_process_entrails_t *entrails, opium_pid_t pid)
{
   opium_process_cpu_sync(&entrails->cpu, pid);
   opium_process_memory_sync(&entrails->mem);
}

   opium_s32_t
opium_process_entrails_init(opium_process_entrails_t *entrails, opium_pid_t pid)
{
   opium_s32_t result;

   opium_process_entrails_sync(entrails, pid);

   opium_u64_t cores[] = {1,5};
   size_t n = sizeof(cores) / sizeof(cores[0]);
   opium_process_cpu_affinity_set(&entrails->cpu, cores, n);
   opium_process_cpu_apply(&entrails->cpu, pid);

   opium_cpuset_t mask = opium_process_cpu_affinity_get(&entrails->cpu);

   opium_process_entrails_sync(entrails, pid);

   mask = opium_process_cpu_affinity_get(&entrails->cpu);

   for (int index = 0; index < CPU_SETSIZE; index++) {
      if (CPU_ISSET(index, &mask)) {
         printf("core: %d\n", index);
      }
   }

   opium_rlimit_t lim = opium_process_memory_as_get(&entrails->mem);
   printf("lim soft: %ld, hard: %ld\n", lim.soft, lim.hard);

   lim = opium_process_memory_stack_get(&entrails->mem);
   printf("lim soft: %ld, hard: %ld\n", lim.soft, lim.hard);

   lim = opium_process_memory_core_get(&entrails->mem);
   printf("core lim soft: %ld, hard: %ld\n", lim.soft, lim.hard);

   lim = opium_process_memory_memlock_get(&entrails->mem);
   printf("memlim soft: %ld, hard: %ld\n", lim.soft, lim.hard);

   lim = opium_process_memory_rss_get(&entrails->mem);
   printf("rss lim soft: %ld, hard: %ld\n", lim.soft, lim.hard);

   lim = opium_process_memory_data_get(&entrails->mem);
   printf("data lim soft: %ld, hard: %ld\n", lim.soft, lim.hard);

   return OPIUM_RET_OK; 
}
