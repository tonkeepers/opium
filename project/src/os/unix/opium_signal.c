#include "core/opium_core.h"

static opium_signal_t *signal_context;

static opium_signal_entry_t default_signals[] = {
   { OPIUM_SIGNAL_INTERRUPT,  0, NULL, NULL },
   { OPIUM_SIGNAL_SHUTDOWN,   0, NULL, NULL }, 
   { OPIUM_SIGNAL_TERMINATE,  0, NULL, NULL },
   { OPIUM_SIGNAL_HANGUP,     0, NULL, NULL }, 
   { 0, 0, NULL, NULL }
};

   static void
opium_signal_entry_set(opium_signal_t *signal, struct sigaction *sa, int signo, opium_log_t *log)
{
   if (signo <= 0 || signo >= OPIUM_SIGNAL_COUNT) {
      opium_log_err(log, "Invalid signal number %d in default list", signo);
      return;
   }

   opium_signal_entry_t *entry = &signal->table[signo];
   entry->signo    = signo;
   entry->received = 0;

   sigaddset(&sa->sa_mask, signo);

   if (sigaction(signo, sa, NULL) == -1) {
      opium_log_err(log, "sigaction(%d) failed\n", signo);
   } else {
      opium_log_debug(log, "Installed handler for signal %d (%s)\n", signo, strsignal(signo));
   }
}

   opium_s32_t
opium_signal_install(opium_signal_t *signal, opium_log_t *log)
{
   if (signal_context != NULL) {
      opium_log_err(log, "Signal handlers already installed (double init detected)\n");
      return OPIUM_RET_FULL;
   }

   opium_signal_entry_t *entries = signal->bind;

   struct sigaction sa = {0};

   sa.sa_sigaction = opium_signal_handler;
   sa.sa_flags     = SA_SIGINFO | SA_RESTART;
   sigemptyset(&sa.sa_mask);

   opium_signal_entry_t *def;
   for (def = default_signals; def->signo != 0; ++def) {
      opium_s32_t signo = def->signo;

      signal->table[signo].handler  = NULL;
      opium_signal_entry_set(signal, &sa, signo, log);
   }

   if (entries != NULL) {
      size_t index = 0;

      while (1) {
         opium_signal_entry_t *current = entries + index;
         index = index + 1;

         if (current->signo == 0 || current->handler == NULL) {
            break;
         }

         opium_s32_t signo = current->signo;

         if (signo <= 0 || signo >= NSIG) {
            opium_log_err(log, "Invalid signal number: %d — skipping\n", signo);
            continue;
         }

         opium_signal_entry_t *sig = &signal->table[signo];
         sig->user_data = current->user_data;
         sig->handler   = current->handler;

         opium_signal_entry_set(signal, &sa, signo, log);
      }
   }

   signal_context = signal;
   signal->log    = log;

   opium_log_debug(log, "All signal handlers successfully installed\n");

   return OPIUM_RET_OK;
}

   void
opium_signal_handler(int signo, siginfo_t *info, void *ucontext)
{
   if (!signal_context) {
      return;
   }

   opium_signal_entry_t *entry = &signal_context->table[signo];

   if (entry->signo != signo) {
      return;
   }

   entry->received = entry->received + 1;

   if (entry->handler) {
      entry->handler(signo, info, ucontext, entry->user_data);
   }

   opium_log_debug(signal_context->log, "Received signal %d, count: %d\n", signo, entry->received);

   switch (signo) {
      case OPIUM_SIGNAL_TERMINATE:
      case OPIUM_SIGNAL_INTERRUPT:
         opium_log_debug(signal_context->log, "Graceful shutdown requested");
         kill(getpid(), OPIUM_SIGNAL_KILL);
         break;

      case OPIUM_SIGNAL_SHUTDOWN:
         opium_log_debug(signal_context->log, "Immediate shutdown requested");
         break;

      case OPIUM_SIGNAL_HANGUP: 
         opium_log_debug(signal_context->log, "Reopen logs / reload config requested");
         break;

      default:
         break;
   }
}

   opium_s32_t 
opium_signal_bind(opium_signal_t *signal, opium_signal_entry_t *entry)
{
   signal->bind = entry;
}
