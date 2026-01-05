#include "core/opium_core.h"

   opium_s32_t 
opium_whatsapp_init(opium_whatsapp_t *wa, size_t n, opium_log_t *log)
{
   if (n <= 0) {
      opium_log_err(log, "Invalid size for events: n <= 0\n"); 
      return OPIUM_RET_ERR;
   }

   wa->fd = epoll_create1(EPOLL_CLOEXEC);
   if (wa->fd == -1) {
      opium_log_err(log, "Failed to create epoll instance\n"); 
      return OPIUM_RET_ERR;
   }

   size_t size = n * sizeof(struct epoll_event);
   wa->events = opium_calloc(size, log);
   if (!wa->events) {
      opium_log_err(log, "Failed to allocate memory for events\n");
      goto fail;
   }

   wa->events_n = n;

   return OPIUM_RET_OK;
fail:
   close(wa->fd);
   return OPIUM_RET_ERR;
}

   void
opium_whatsapp_exit(opium_whatsapp_t *wa)
{
   if (wa->fd) {
      close(wa->fd);
      wa->fd = -1;
   }

   if (wa->events) {
      opium_free(wa->events, wa->log);
      wa->events = NULL;
   }

   wa->events_n = 0;
   wa->log = NULL;
}

   opium_s32_t 
opium_whatsapp_track(opium_whatsapp_t *wa, opium_fd_t fd, opium_s32_t flags)
{
   struct epoll_event bindable;
   bindable.events = flags;
   bindable.data.fd = fd;

   if (epoll_ctl(wa->fd, EPOLL_CTL_ADD, fd, &bindable) == -1) {
      opium_log_err(wa->log, "epoll_ctl failed to add fd %d\n", fd);
      return OPIUM_RET_ERR;
   }

   return OPIUM_RET_OK;
}

   void
opium_whatsapp_untrack(opium_whatsapp_t *wa, opium_fd_t fd) 
{
   if (epoll_ctl(wa->fd, EPOLL_CTL_DEL, fd, NULL) == -1) {
      opium_log_err(wa->log, "epoll_ctl failed to remove fd %d\n", fd);
   }
} 

   opium_s32_t 
opium_whatsapp_read(opium_whatsapp_t *wa, opium_fd_t fd, opium_whatsapp_signal_t *signal)
{
   int n = epoll_wait(wa->fd, wa->events, wa->events_n, -1);

   if (n <= 0) {
      return OPIUM_WA_EMPTY;
   }

   for (opium_s32_t index = 0; index < n; index++) {
      struct epoll_event bindable = wa->events[index];

      signal->fd = bindable.data.fd;
      signal->type = bindable.events;         

      if (fd < 0) {
         return OPIUM_RET_OK;
      } else {
         if (bindable.data.fd == fd) {
            return OPIUM_RET_OK;
         }
      }
   }

   return OPIUM_RET_ERR;
}
