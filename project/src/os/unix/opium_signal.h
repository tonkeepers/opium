#ifndef OPIUM_SIGNAL_INCLUDED_H
#define OPIUM_SIGNAL_INCLUDED_H

#include "core/opium_core.h"

struct opium_signal_s {
   char       *name;
   opium_s32_t signo;
   void       (*handler)(int signo, siginfo_t *info, void *ucontext);
};

opium_s32_t opium_signal_install(opium_signal_t *signal_table, opium_log_t *log);

#endif /* OPIUM_SIGNAL_INCLUDED_H */
