#ifndef OPIUM_SIGNAL_INCLUDED_H
#define OPIUM_SIGNAL_INCLUDED_H

#include "core/opium_core.h"

typedef struct {
   opium_s32_t           signo;
   volatile sig_atomic_t received;
   void                 *user_data;
   void                  (*handler)(int signo, siginfo_t *info, void *ucontext, void *ud);
} opium_signal_entry_t;

struct opium_signal_s {
   opium_signal_entry_t  table[OPIUM_SIGNAL_COUNT];
   opium_signal_entry_t  *bind;
   opium_log_t          *log;
};

opium_s32_t opium_signal_install(opium_signal_t *signal, opium_log_t *log);
void        opium_signal_handler(int signo, siginfo_t *info, void *ucontext);
opium_s32_t opium_signal_bind(opium_signal_t *signal, opium_signal_entry_t *entry);

#endif /* OPIUM_SIGNAL_INCLUDED_H */
