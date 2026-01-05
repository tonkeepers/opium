#ifndef OPIUM_PROCESS_INCLUDED_H 
#define OPIUM_PROCESS_INCLUDED_H 

#include "core/opium_core.h"

#define OPIUM_INVALID_PID      -1
#define OPIUM_MAX_PROCESSES     6 

typedef enum {
   OPIUM_PROC_RUNNING,
   OPIUM_PROC_SLEEPING,
   OPIUM_PROC_DISK_SLEEP,
   OPIUM_PROC_STOPPED,
   OPIUM_PROC_ZOMBIE,
} opium_proc_state_t;

typedef void (*opium_proc_func_t)(void *data);

struct opium_process_s {
   opium_pid_t          pid;
   opium_pid_t          ppid;

   opium_s32_t          daemon;

   char                *name;
   void                *data;
   opium_proc_func_t    func;

   opium_signal_t       signal;
   opium_channel_t      channel;

   opium_u64_t          cpu_affinity;

   opium_proc_state_t   state;

   void                *parent;
   void                *children[OPIUM_MAX_PROCESSES];
   opium_s32_t          children_count;

   opium_log_t         *log;
};

void opium_process_self_init(opium_signal_t *signal, opium_log_t *log);

opium_pid_t opium_process_spawn(char *name, void *data, opium_proc_func_t func, opium_log_t *log);


void        opium_processes_init();

#endif /* OPIUM_PROCESS_INCLUDED_H  */
