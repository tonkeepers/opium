#include "core/opium_core.h"

opium_signal_t *current_signal_table = NULL;

   opium_s32_t
opium_signal_install(opium_signal_t *signal_table, opium_log_t *log)
{
   opium_signal_t *sig;

   struct sigaction sa;
   sa.sa_sigaction = sig->handler;
   sa.sa_flags     = SA_SIGINFO | SA_RESTART;
   opium_memzero(&sa, sizeof(struct sigaction));
   sigemptyset(&sa.sa_mask);

   for (sig = signal_table; sig->signo != 0; sig++) {
      sigaddset(&sa.sa_mask, sig->signo);

      if (!sig->handler) {
         if (signal(sig->signo, SIG_IGN) == SIG_ERR) {
            opium_log_err(log, "sig(%d, SIG_IGN) failed", sig->signo);
            return OPIUM_RET_ERR;
         }
         continue;
      }

      if (sigaction(sig->signo, &sa, NULL) == -1) {
         opium_log_err(log, "sigaction(%s%s) failed", sig->name ? sig->name : "", 
               sig->name ? "" : "unknown");
         return OPIUM_RET_ERR;
      }

      opium_log_debug(log, "Installed handler for sig %s (%d)", sig->name ? sig->name : "unnamed",
            sig->signo);
   }

   current_signal_table = signal_table;

   return OPIUM_RET_OK;
}

   void
opium_signal_handler(int signo, siginfo_t *info, void *ucontext)
{

   switch (signo) {
      case OPIUM_REOPEN_SIGNAL:

         break;
      case OPIUM_SHUTDOWN_SIGNAL:

         break;
      case OPIUM_TERMINATE_SIGNAL:

         break;
      default:
   }

}
