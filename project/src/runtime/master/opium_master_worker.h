#ifndef OPIUM_MASTER_WORKER_INCLUDED_H
#define OPIUM_MASTER_WORKER_INCLUDED_H

#include "core/opium_core.h"

typedef struct {
   opium_shm_t     worker;

   size_t          elt_max;
   size_t          elt_n;
} opium_master_worker_t;

opium_s32_t opium_master_worker_init(opium_master_worker_t *mw, size_t elt_max, 
      opium_log_t *log);
void        opium_master_worker_exit(opium_master_worker_t *mw);

#endif /* OPIUM_MASTER_WORKER_INCLUDED_H */
