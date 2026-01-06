#ifndef OPIUM_WORKER_INCLUDE_H 
#define OPIUM_WORKER_INCLUDE_H 

#include "core/opium_core.h"

typedef enum {
   OPIUM_WORKER_STATE_IDLE,
   OPIUM_WORKER_STATE_ACTIVE,
   OPIUM_WORKER_STATE_TERMINATED,
} OPIUM_WORKER_STATE;

struct opium_worker_s {
   opium_fork_t       fork;
   opium_listening_t  listening;

   opium_s32_t        shutdown_flag:1;

   size_t             cpu_time;
   size_t             memory_usage;
   size_t             network_usage;

   OPIUM_WORKER_STATE state;
};

#endif /* OPIUM_WORKER_INCLUDE_H */
