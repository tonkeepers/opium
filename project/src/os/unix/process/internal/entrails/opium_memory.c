#include "core/opium_core.h"

typedef struct {
   size_t      offset;
   int         rlimit_id;
   opium_u32_t flag;
} rlimit_entry;

static const rlimit_entry rlimit_entries[] = {
   { offsetof(opium_process_memory_t, as),      RLIMIT_AS,      OPIUM_MEMORY_F_AS      },
   { offsetof(opium_process_memory_t, data),    RLIMIT_DATA,    OPIUM_MEMORY_F_DATA    },
   { offsetof(opium_process_memory_t, rss),     RLIMIT_RSS,     OPIUM_MEMORY_F_RSS     },
   { offsetof(opium_process_memory_t, stack),   RLIMIT_STACK,   OPIUM_MEMORY_F_STACK   },
   { offsetof(opium_process_memory_t, core),    RLIMIT_CORE,    OPIUM_MEMORY_F_CORE    },
   { offsetof(opium_process_memory_t, memlock), RLIMIT_MEMLOCK, OPIUM_MEMORY_F_MEMLOCK },
};

#define RLIMIT_COUNT (sizeof(rlimit_entries) / sizeof(rlimit_entries[0]))

static inline opium_rlimit_t *opium_rlimit_ptr(opium_process_memory_t *mem, size_t index)
{
   return (opium_rlimit_t *)((uintptr_t)mem + rlimit_entries[index].offset);
}

static opium_s32_t opium_rlimit(opium_rlimit_t *lim, int rlimit_id, opium_s32_t is_set)
{
   opium_s32_t   result;
   struct rlimit limit;

   result = getrlimit(rlimit_id, &limit);
   if (result == -1) {
      return OPIUM_RET_ERR;
   }

   if (is_set) {
      if (lim->soft >= 0) {
         limit.rlim_cur = lim->soft;
      }

      if (lim->hard >= 0) {
         limit.rlim_max = lim->hard;
      }

      result = setrlimit(rlimit_id, &limit);
      if (result == -1) {
         return OPIUM_RET_ERR;
      }

   } else {
      lim->soft = (limit.rlim_cur == RLIM_INFINITY) ? OPIUM_RLIMIT_UNLIMITED : limit.rlim_cur;
      lim->hard = (limit.rlim_max == RLIM_INFINITY) ? OPIUM_RLIMIT_UNLIMITED : limit.rlim_max;
   }

   return OPIUM_RET_OK;
}

   void 
opium_process_memory_sync(opium_process_memory_t *mem)
{
   for (size_t index = 0; index < RLIMIT_COUNT; ++index) {
      opium_rlimit(opium_rlimit_ptr(mem, index), rlimit_entries[index].rlimit_id, 0);
   }
}

   opium_s32_t 
opium_process_memory_apply(opium_process_memory_t *mem)
{
   opium_s32_t result;

   for (size_t index = 0; index < RLIMIT_COUNT; ++index) {
      if (mem->flags & rlimit_entries[index].flag) {
         result = opium_rlimit(opium_rlimit_ptr(mem, index), rlimit_entries[index].rlimit_id, 1);
         if (result != OPIUM_RET_OK) {
            return result;
         }

         mem->flags = mem->flags & ~(rlimit_entries[index].flag);
      }
   }

   return OPIUM_RET_OK;
}

   opium_s32_t 
opium_process_memory_as_set(opium_process_memory_t *mem, opium_rlimit_t lim)
{
   mem->as = lim;
   mem->flags = mem->flags | OPIUM_MEMORY_F_AS;
   return OPIUM_RET_OK;
}

   opium_rlimit_t 
opium_process_memory_as_get(opium_process_memory_t *mem)
{
   return mem->as;
}

   opium_s32_t
opium_process_memory_data_set(opium_process_memory_t *mem, opium_rlimit_t lim)
{
   mem->data = lim;
   mem->flags = mem->flags | OPIUM_MEMORY_F_DATA;
   return OPIUM_RET_OK;
}

   opium_rlimit_t 
opium_process_memory_data_get(opium_process_memory_t *mem)
{
   return mem->data;
}

   opium_s32_t
opium_process_memory_rss_set(opium_process_memory_t *mem, opium_rlimit_t lim)
{
   mem->rss = lim;
   mem->flags = mem->flags | OPIUM_MEMORY_F_RSS;
   return OPIUM_RET_OK;
}

   opium_rlimit_t
opium_process_memory_rss_get(opium_process_memory_t *mem)
{
   return mem->rss;
}

   opium_s32_t
opium_process_memory_stack_set(opium_process_memory_t *mem, opium_rlimit_t lim)
{
   mem->stack = lim;
   mem->flags = mem->flags | OPIUM_MEMORY_F_STACK;
   return OPIUM_RET_OK;
}

   opium_rlimit_t
opium_process_memory_stack_get(opium_process_memory_t *mem)
{
   return mem->stack;
}

   opium_s32_t
opium_process_memory_core_set(opium_process_memory_t *mem, opium_rlimit_t lim)
{
   mem->core = lim;
   mem->flags = mem->flags | OPIUM_MEMORY_F_CORE;
   return OPIUM_RET_OK;
}

   opium_rlimit_t
opium_process_memory_core_get(opium_process_memory_t *mem)
{
   return mem->core;
}

   opium_s32_t
opium_process_memory_memlock_set(opium_process_memory_t *mem, opium_rlimit_t lim)
{
   mem->memlock = lim;
   mem->flags = mem->flags | OPIUM_MEMORY_F_MEMLOCK;
   return OPIUM_RET_OK;
}

   opium_rlimit_t
opium_process_memory_memlock_get(opium_process_memory_t *mem)
{
   return mem->memlock;
}
