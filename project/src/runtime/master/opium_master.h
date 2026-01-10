#ifndef OPIUM_MASTER_INCLUDED_H
#define OPIUM_MASTER_INCLUDED_H

#include "core/opium_core.h"

struct opium_master_s {
   opium_master_worker_t mw;

   opium_process_t       process;

   opium_log_t          *log;
};

opium_s32_t opium_master_main(size_t proc_max, opium_log_t *log);

#endif /* OPIUM_MASTER_INCLUDED_H */
