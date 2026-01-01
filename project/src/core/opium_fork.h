#ifndef OPIUM_FORK_INCLUDE_H 
#define OPIUM_FORK_INCLUDE_H 

#include "core/opium_core.h"

#define OPIUM_FORK_PATH_LEN 32
#define OPIUM_FORK_NAME_LEN 32
#define OPIUM_FORK_CWD_LEN  1024

typedef enum {
   OPIUM_FORK_RUNNING,
   OPIUM_FORK_SLEEPING,
   OPIUM_FORK_DISK_SLEEP,
   OPIUM_FORK_STOPPED,
   OPIUM_FORK_ZOMBIE,
} OPIUM_FORK_STATE_T;

struct opium_fork_s {
   opium_pid_t        pid;
   opium_pid_t        ppid;
   opium_pid_t        pgid;

   u_char             path[OPIUM_FORK_PATH_LEN];
   u_char             name[OPIUM_FORK_NAME_LEN];
   u_char             cwd[OPIUM_FORK_CWD_LEN];

   FILE              *file;

   opium_u64_t        cpu_affinity;

   opium_u64_t        rss_kb;
   opium_u64_t        vsize_kb;
   opium_u64_t        cpu_ticks;
   opium_u64_t        cpu_last;

   opium_s32_t         signal;
   opium_s32_t         exit_code;

   OPIUM_FORK_STATE_T state;

   opium_log_t       *log;
};

opium_s32_t opium_fork_init(opium_fork_t *fork, opium_log_t *log);

#endif /* OPIUM_FORK_INCLUDE_H  */
