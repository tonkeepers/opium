#ifndef OPIUM_SUPERVISOR_H 
#define OPIUM_SUPERVISOR_H 

#include "core/opium_core.h"

typedef struct {
   opium_s32_t   daemon:1;

   opium_str_t   server_address;
   opium_u64_t   port;
   opium_u64_t   max_connections;

   opium_u64_t   worker_processes;
   opium_u64_t   cpu_affinity_auto;
   opium_u64_t   cpu_affinity_n;

   opium_str_t   work_dir;

   opium_s32_t   console_log:1;
   opium_str_t   log_file;
   opium_str_t   error_log;
   opium_u64_t   log_level;

   opium_s32_t   encryption_enabled:1;
   //opium_str_t   encryption_method;

   opium_u64_t   max_message_size;
} opium_supervisor_conf_t;

typedef struct opium_supervisor_s opium_supervisor_t;
struct opium_supervisor_s {

};

#endif /* OPIUM_SUPERVISOR_H */

