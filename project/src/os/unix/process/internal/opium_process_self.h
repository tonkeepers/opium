#ifndef OPIUM_PROCESS_INCLUDED_H 
#define OPIUM_PROCESS_INCLUDED_H 

#include "core/opium_core.h"

#define OPIUM_INVALID_PID      -1

typedef enum {
   OPIUM_PROC_RUNNING,
   OPIUM_PROC_SLEEPING,
   OPIUM_PROC_DISK_SLEEP,
   OPIUM_PROC_STOPPED,
   OPIUM_PROC_ZOMBIE,
} opium_proc_state_t;

struct opium_process_s {
   opium_pid_t              pid;
   opium_pid_t              ppid;

   char                    *name;
   void                    *data;

   opium_process_entrails_t entrails;
   opium_process_channel_t  channel;
   opium_process_signal_t   signal;

   opium_proc_state_t       state;

   unsigned                 can_spawn:1;

   opium_log_t             *log;
};

void opium_process_self_init(char *name, void *data, opium_log_t *log);

#endif /* OPIUM_PROCESS_INCLUDED_H  */
