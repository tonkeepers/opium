
#include "core/opium_core.h"

   opium_s32_t 
opium_daemon(opium_log_t *log)
{
   opium_pid_t pid, sid;
   opium_s32_t fd;

   switch (fork()) {
      case -1:
         opium_log_err(log, "fork() failed \n"); 
         return OPIUM_RET_ERR;

      case 0:
         break;

      default:
         exit(0);

   }

   sid = setsid();
   if (sid == -1) {
      opium_log_err(log, "setsid() failed \n"); 
      return OPIUM_RET_ERR;
   }

   umask(0);

   fd = open("/dev/null", O_RDWR);
   if (fd == -1) {
      opium_log_err(log, "open(/dev/null) failed\n");
      return OPIUM_RET_ERR;
   }

   if (dup2(fd, STDIN_FILENO) == -1) {
      opium_log_err(log, "dup2(fd, STDIN_FILENO) failed\n");
      return OPIUM_RET_ERR;
   }

   if (dup2(fd, STDOUT_FILENO) == -1) {
      opium_log_err(log, "dup2(fd, STDOUT_FILENO) failed\n");
      return OPIUM_RET_ERR;
   }

   if (dup2(fd, STDERR_FILENO) == -1) {
      opium_log_err(log, "dup2(fd, STDERR_FILENO) failed\n");
      return OPIUM_RET_ERR;
   }

   if (fd > STDERR_FILENO) {
      close(fd);
   }

   return OPIUM_RET_OK;
}
