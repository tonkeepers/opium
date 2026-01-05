#ifndef OPIUM_WHATSAPP_INCLUDED_H
#define OPIUM_WHATSAPP_INCLUDED_H

#include "core/opium_core.h"

#define OPIUM_WA_EMPTY -5
#define OPIUM_WA_COUNT 5

// Event when the descriptor is ready for reading
#define OPIUM_WA_SR EPOLLIN 

// Event when the descriptor is ready for writing
#define OPIUM_WA_SW EPOLLOUT

// Event when the descriptor encounters an error
#define OPIUM_WA_SE EPOLLERR

// Event when the peer closes the write side of the connection (TCP FIN)
#define OPIUM_WA_SD EPOLLRDHUP

// Event when the descriptor is hung up or closed
#define OPIUM_WA_SH EPOLLHUP 

typedef struct {
   opium_fd_t  fd;
   opium_s32_t type; 
} opium_whatsapp_signal_t;

struct opium_whatsapp_s {
   opium_s32_t         fd;
   struct epoll_event *events;
   size_t              events_n;

   opium_log_t        *log;
};

opium_s32_t opium_whatsapp_init(opium_whatsapp_t *wa, size_t n, opium_log_t *log);
void opium_whatsapp_exit(opium_whatsapp_t *wa);

opium_s32_t opium_whatsapp_track(opium_whatsapp_t *wa, opium_fd_t fd, opium_s32_t flags);
void opium_whatsapp_untrack(opium_whatsapp_t *wa, opium_fd_t fd);

opium_s32_t opium_whatsapp_read(opium_whatsapp_t *wa, opium_fd_t fd, opium_whatsapp_signal_t *signal);

#endif /* OPIUM_WHATSAPP_INCLUDED_H */
