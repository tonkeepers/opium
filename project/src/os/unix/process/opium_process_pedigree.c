#include "core/opium_core.h"   

/*
   opium_pid_t
   opium_process_spawn(char *name, void *data, opium_proc_func_t func, opium_log_t *log)
   {
   opium_s32_t      index; 
   for (index = 0; index < OPIUM_MAX_PROCESSES; index++) {
   if (opium_processes[index].pid == -1) {
   break;
   }
   }

   if (index == OPIUM_MAX_PROCESSES) {
   opium_log_err(log, "Limit of the processes %d was reached!\n", OPIUM_MAX_PROCESSES);
   return OPIUM_INVALID_PID;
   }

   opium_process_t process = opium_processes[index];

   opium_channel_t channel;
   if (opium_channel_init(&channel, log) != OPIUM_RET_OK) {
   opium_log_err(log, "Failed to allocate channel!\n");
   return OPIUM_RET_ERR;
   }

   opium_pid_t pid = fork(); 

   switch (pid) {
   case -1:
   opium_log_err(log, "Failed to fork()\n");
   return OPIUM_INVALID_PID;

   case 0:
   opium_ppid = opium_pid; 
   opium_pid  = getpid();

   opium_log_debug(log, "child pid: %d\n", opium_pid);

   opium_channel_fetch(&channel, OPIUM_CHANNEL_CHILD);

   func(data);

   exit(0);
   break;

   default:
   opium_log_debug(log, "parent pid: %d\n", getpid());
   opium_channel_fetch(&channel, OPIUM_CHANNEL_PARENT);
   break;

   } 


   process.pid  = pid;

   if (respawn >= 0) {
   return pid;
   }

   opium_signals_init(log);

   process.name    = name;
   process.data    = data;
   process.func    = func;
   process.channel = channel;
   return pid;
   return OPIUM_RET_OK;
   }

   void
   opium_process_handler(opium_whatsapp_t *wa, opium_log_t *log)
   {

}

*/
