#include "core/opium_core.h"

   void 
opium_process_init(opium_process_t self, char *name, void *data, opium_log_t *log)
{
   opium_s32_t result;

   opium_memzero(&self, sizeof(opium_process_t));

   self.pid  = getpid();
   self.ppid = getppid();

   self.name = name;
   self.data = data;

   self.log  = log;

   result = opium_process_entrails_init(&self.entrails, self.pid);
   if (result != OPIUM_RET_OK) {
      // Question
   } 

}
