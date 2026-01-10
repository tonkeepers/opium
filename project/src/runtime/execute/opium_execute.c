#include "core/opium_core.h"
#include "runtime/execute/opium_execute.h"

/* Default value for daemon flag (0 = not running as daemon) */
#define OPIUM_DEFAULT_DAEMON              0

/* Default server address to bind (0.0.0.0 means bind to all interfaces) */
#define OPIUM_DEFAULT_SERVER_ADDRESS      "0.0.0.0"

/* Default port for the server to listen on */
#define OPIUM_DEFAULT_PORT               8080

/* Default maximum number of simultaneous client connections */
#define OPIUM_DEFAULT_MAX_CONNECTIONS    1000

/* Default maximum number of simultaneous process */
#define OPIUM_DEFAULT_MAX_PROCESSES      32 

/* Default number of worker processes */
#define OPIUM_DEFAULT_WORKER_PROCESSES   1

/* Default value for CPU affinity auto-calculation (1 = enabled) */
#define OPIUM_DEFAULT_CPU_AFFINITY_AUTO  1

/* Default number of CPUs for CPU affinity */
#define OPIUM_DEFAULT_CPU_AFFINITY_N     4

/* Default flag for console logging (1 = enabled) */
#define OPIUM_DEFAULT_CONSOLE_LOG        1

/* Default log file path */
#define OPIUM_DEFAULT_LOG_FILE           "/var/log/opium.log"

/* Default error log file path */
#define OPIUM_DEFAULT_ERROR_LOG          "/var/log/opium_error.log"

/* Default log level (2 = Debug, 1 = Info, etc.) */
#define OPIUM_DEFAULT_LOG_LEVEL          2

/* Default flag for encryption (0 = disabled) */
#define OPIUM_DEFAULT_ENCRYPTION_ENABLED 0

/* Default maximum message size for incoming messages (in bytes) */
#define OPIUM_DEFAULT_MAX_MESSAGE_SIZE   1024

   opium_s32_t 
opium_supervisor_conf_init(opium_supervisor_conf_t *conf)
{
   /* Initialize the conf with default values */
   conf->daemon = OPIUM_DEFAULT_DAEMON;

   /* Initialize network and other parameters */
   conf->server_address = opium_str(OPIUM_DEFAULT_SERVER_ADDRESS);
   conf->port = OPIUM_DEFAULT_PORT;
   conf->max_connections = OPIUM_DEFAULT_MAX_CONNECTIONS;
   conf->worker_processes = OPIUM_DEFAULT_WORKER_PROCESSES;
   conf->cpu_affinity_auto = OPIUM_DEFAULT_CPU_AFFINITY_AUTO;
   conf->cpu_affinity_n = OPIUM_DEFAULT_CPU_AFFINITY_N;

   /* Initialize logging settings */
   conf->console_log = OPIUM_DEFAULT_CONSOLE_LOG;
   conf->log_file = opium_str(OPIUM_DEFAULT_LOG_FILE);
   conf->error_log = opium_str(OPIUM_DEFAULT_ERROR_LOG);
   conf->log_level = OPIUM_DEFAULT_LOG_LEVEL;

   /* Initialize encryption settings */
   conf->encryption_enabled = OPIUM_DEFAULT_ENCRYPTION_ENABLED;

   conf->max_message_size = OPIUM_DEFAULT_MAX_MESSAGE_SIZE;

   conf->work_dir = opium_str("");

   return OPIUM_RET_OK; 
}

void sighandler_func(int signo) {
   printf("signo: %d\n", signo);
}

opium_signal_entry_t signals[] = {
   { OPIUM_SIGNAL_REOPEN,  0, NULL, NULL },
   { OPIUM_SIGNAL_SHUTDOWN,   0, NULL, NULL },
   { OPIUM_SIGNAL_TERMINATE,  0, NULL, NULL },
   { OPIUM_SIGNAL_HANGUP,     0, NULL, NULL },
   { 0, 0, NULL, NULL }
};

int main(int argc, void *argv[]) {
   opium_s32_t ret;

   printf("argv: %s\n", argv[0]);

   opium_log_t *log = opium_log_init(NULL, NULL, NULL);
   if (!log) {
      return OPIUM_RET_ERR;
   }

   printf("pid: %d\n", getpid());

   opium_process_self_init("yes", NULL, log);

   opium_shm_t shm;
   shm.size = sizeof(opium_process_t) * OPIUM_DEFAULT_MAX_PROCESSES;
   opium_s32_t result = opium_shm_alloc(&shm);
   if (opium_unlikely(result != OPIUM_RET_OK)) {
      return OPIUM_RET_ERR;
   }

   opium_master_main(OPIUM_DEFAULT_MAX_PROCESSES, log);

   printf("fsdfsd\n");
   while (1) {

      sleep(1);
   }

   return OPIUM_RET_OK;
}
