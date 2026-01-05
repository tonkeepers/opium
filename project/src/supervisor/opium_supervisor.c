#include "core/opium_core.h"
#include "supervisor/opium_supervisor.h"

/* Default value for daemon flag (0 = not running as daemon) */
#define OPIUM_DEFAULT_DAEMON              0

/* Default server address to bind (0.0.0.0 means bind to all interfaces) */
#define OPIUM_DEFAULT_SERVER_ADDRESS      "0.0.0.0"

/* Default port for the server to listen on */
#define OPIUM_DEFAULT_PORT               8080

/* Default maximum number of simultaneous client connections */
#define OPIUM_DEFAULT_MAX_CONNECTIONS    1000

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

void master_main(void *data) {
   printf("Master say hello!\n");

   while (1) {

      sleep(1);
   }
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

   opium_supervisor_conf_t conf;

   ret = opium_supervisor_conf_init(&conf);
   if (ret != OPIUM_RET_OK) {
      return OPIUM_RET_ERR;
   }

   printf("pid: %d\n", getpid());
   //opium_processes_init();

   char *name = "yes";
   //opium_process_spawn(name, NULL, master_main, -1, log);

   /* EPOLL */

   int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
   int flags = fcntl(sock_fd, F_GETFL);
   fcntl(sock_fd, F_SETFL, flags | O_NONBLOCK);

   struct sockaddr_in addr;
   addr.sin_family = AF_INET;
   addr.sin_port = htons(8080);
   addr.sin_addr.s_addr = INADDR_ANY;

   bind(sock_fd, (struct sockaddr*)&addr, sizeof(addr));
   listen(sock_fd, 10);

   int ep_fd = epoll_create(EPOLL_CLOEXEC);
   struct epoll_event events[100];

   struct epoll_event event_fd;
   event_fd.events = EPOLLIN;
   event_fd.data.fd = sock_fd; 

   epoll_ctl(ep_fd, EPOLL_CTL_ADD, sock_fd, &event_fd);

   opium_signal_t signal;
   opium_signal_bind(&signal, signals);
   opium_process_self_init(&signal, log);

   /* sig */


   /*
      struct sigaction {
      void (*sa_handler)(int);       // Указатель на обработчик сигнала
      void (*sa_sigaction)(int, siginfo_t *, void *); // Альтернативный обработчик с дополнительной информацией
      sigset_t sa_mask;              // Маска сигналов, которые будут блокироваться во время обработки
      int sa_flags;                  // Флаги, управляющие поведением обработчика
      void (*sa_restorer)(void);     // Обработчик для восстановления состояния (устаревший, не используется в современных системах)
      };
      */


   while (1) {

      int n = epoll_wait(ep_fd, events, 100, -1);

      for (int index = 0; index < n; index++) {
         if (events[index].data.fd == sock_fd) {
            printf("socket!\n");
         }
      }

      sleep(1);
   }
   //opium_process_daemonize(&proc, log);

   return OPIUM_RET_OK;
}
