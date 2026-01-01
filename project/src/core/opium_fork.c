#include "core/opium_core.h"

   opium_s32_t
opium_fork_init(opium_fork_t *fork, opium_log_t *log)
{
   opium_memzero(fork, sizeof(opium_fork_t));

   fork->pid  = getpid();
   fork->ppid = getppid();
   fork->pgid = getpgrp(); 

   u_char proc_path[OPIUM_FORK_PATH_LEN];
   snprintf(proc_path, sizeof(proc_path), "/proc/%d/comm", fork->pid);
   
   /* FILE ACTIONS */
   FILE *file = fopen(proc_path, "rw");
   if (!file) {
      return OPIUM_RET_ERR;
   }

   fgets((u_char*)fork->name, OPIUM_FORK_NAME_LEN, file);

   size_t len = opium_strlen((u_char*)fork->name);
   if (len > 0 && fork->name[len - 1] == "\n") {
      fork->name[len - 1] = '\0';
   }

   /* GET CWD */
   void *ret = getcwd((u_char*)fork->cwd, OPIUM_FORK_CWD_LEN);
   if (ret == NULL) {
      opium_cpystrn((u_char*)fork->cwd, ".", OPIUM_FORK_CWD_LEN);
   }

   opium_log_debug(log, "process name: %s\n cwd: %s\n", 
         fork->name, fork->cwd);

   return OPIUM_RET_ERR;
}
