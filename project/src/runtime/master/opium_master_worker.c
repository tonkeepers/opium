#include "core/opium_core.h"

   opium_s32_t 
opium_master_worker_init(opium_master_worker_t *mw, size_t elt_max, opium_log_t *log)
{
   opium_s32_t  result;
   opium_shm_t *worker = &mw->worker;
   size_t       size = sizeof(opium_worker_t) * elt_max;

   opium_shm_setsize(worker, size);
   result = opium_shm_alloc(worker);
   if (opium_unlikely(result != OPIUM_RET_OK)) {
      opium_log_err(log, "Failed to allocate worker array!\n");
      return OPIUM_RET_ERR; 
   }

   mw->elt_max = elt_max;
   mw->elt_n   = 0;

   return OPIUM_RET_OK;
}

   void
opium_master_worker_exit(opium_master_worker_t *mw)
{

}
