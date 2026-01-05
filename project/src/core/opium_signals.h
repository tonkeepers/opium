#ifndef OPIUM_SIGNALS_INCLUDE_H
#define OPIUM_SIGNALS_INCLUDE_H

/**
 * @file opium_signals.h
 * @brief Centralized definitions of all signals used. 
 *
 * This file provides human-readable names for all important system signals
 * and custom signals. 
 *
 * Use these constants instead of raw numbers everywhere in the code.
 */

/* SIGUSR1 equivalent: reopen log files, reload configuration */
#define OPIUM_SIGNAL_REOPEN     SIGUSR1

/* Immediate but clean shutdown (SIGQUIT style) */
#define OPIUM_SIGNAL_SHUTDOWN   SIGQUIT

/* Graceful termination (standard SIGTERM) */
#define OPIUM_SIGNAL_TERMINATE  SIGTERM

/* Interrupt from keyboard (Ctrl+C) */
#define OPIUM_SIGNAL_INTERRUPT      SIGINT

/* Hangup detected on controlling terminal or death of controlling process */
#define OPIUM_SIGNAL_HANGUP         SIGHUP

/* * User-defined signal 2 */
#define OPIUM_SIGNAL_USER2          SIGUSR2

/* Child process stopped or terminated (useful for master-worker) */
#define OPIUM_SIGNAL_CHILD          SIGCHLD

/* Alarm clock (used for timers) */
#define OPIUM_SIGNAL_ALARM          SIGALRM

/* Immediate termination */
#define OPIUM_SIGNAL_KILL           SIGKILL   // Note: cannot be caught!

/* Core dump signals (for debugging crashes) */
#define OPIUM_SIGNAL_ABORT          SIGABRT
#define OPIUM_SIGNAL_SEGFAULT       SIGSEGV
#define OPIUM_SIGNAL_BUS_ERROR      SIGBUS

/* Stop process */
#define OPIUM_SIGNAL_STOP           SIGTSTP
/* Continue process after stop */
#define OPIUM_SIGNAL_CONTINUE       SIGCONT

/* Number of signals available on the system (including 0) */
#define OPIUM_SIGNAL_COUNT          _NSIG

#endif /* OPIUM_SIGNALS_INCLUDE_H */
