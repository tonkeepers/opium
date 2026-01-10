#include "core/opium_core.h"

opium_master_t master;

   opium_s32_t 
opium_master_main(size_t proc_max, opium_log_t *log)
{
   opium_s32_t result;

   result = opium_master_worker_init(&master.mw, proc_max, log);
   if (opium_unlikely(result != OPIUM_RET_OK)) {

      return OPIUM_RET_ERR;
   }



   return OPIUM_RET_OK;
}
