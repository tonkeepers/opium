#ifndef OPIUM_PROCESS_MEMORY_INCLUDED_H
#define OPIUM_PROCESS_MEMORY_INCLUDED_H

#include "core/opium_core.h"

typedef enum {
   OPIUM_MEMORY_F_AS      = 1 << 0,
   OPIUM_MEMORY_F_DATA    = 1 << 1,
   OPIUM_MEMORY_F_RSS     = 1 << 2,
   OPIUM_MEMORY_F_STACK   = 1 << 3,
   OPIUM_MEMORY_F_CORE    = 1 << 4,
   OPIUM_MEMORY_F_MEMLOCK = 1 << 5,
} opium_process_memory_flags_t;

typedef struct {
   opium_s64_t soft;
   opium_s64_t hard;
} opium_rlimit_t;

#define OPIUM_RLIMIT_UNLIMITED      RLIM_INFINITY

#define OPIUM_RLIMIT_UNLIMITED_PAIR { OPIUM_RLIMIT_UNLIMITED, OPIUM_RLIMIT_UNLIMITED }
#define OPIUM_RLIMIT_ZERO           { 0, 0 }

typedef struct {
   opium_rlimit_t as;
   opium_rlimit_t data;
   opium_rlimit_t rss;
   opium_rlimit_t stack;
   opium_rlimit_t core; 
   opium_rlimit_t memlock;

   opium_u32_t    flags;
} opium_process_memory_t;

void           opium_process_memory_sync(opium_process_memory_t *mem);
opium_s32_t    opium_process_memory_apply(opium_process_memory_t *memory);

opium_s32_t    opium_process_memory_as_set(opium_process_memory_t *mem, opium_rlimit_t lim);
opium_rlimit_t opium_process_memory_as_get(opium_process_memory_t *mem);

opium_s32_t    opium_process_memory_data_set(opium_process_memory_t *mem, opium_rlimit_t lim);
opium_rlimit_t opium_process_memory_data_get(opium_process_memory_t *mem);

opium_s32_t    opium_process_memory_rss_set(opium_process_memory_t *mem, opium_rlimit_t lim);
opium_rlimit_t opium_process_memory_rss_get(opium_process_memory_t *mem);

opium_s32_t    opium_process_memory_stack_set(opium_process_memory_t *mem, opium_rlimit_t lim);
opium_rlimit_t opium_process_memory_stack_get(opium_process_memory_t *mem);

opium_s32_t    opium_process_memory_core_set(opium_process_memory_t *mem, opium_rlimit_t lim);
opium_rlimit_t opium_process_memory_core_get(opium_process_memory_t *mem);

opium_s32_t    opium_process_memory_memlock_set(opium_process_memory_t *mem, opium_rlimit_t lim);
opium_rlimit_t opium_process_memory_memlock_get(opium_process_memory_t *mem);

#endif /* OPIUM_PROCESS_MEMORY_INCLUDED_H */
