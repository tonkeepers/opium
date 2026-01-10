#ifndef OPIUM_WORKER_INCLUDE_H 
#define OPIUM_WORKER_INCLUDE_H 

#include "core/opium_core.h"

struct opium_worker_s {
   opium_process_t process;

   opium_log_t    *log;
};

#endif /* OPIUM_WORKER_INCLUDE_H */
