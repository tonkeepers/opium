#include "core/opium_core.h"

opium_process_t self;

   void 
opium_process_self_init(opium_log_t *log)
{
   opium_memzero(&self, sizeof(opium_process_t));

   self.pid  = getpid();
   self.ppid = getppid();


}
