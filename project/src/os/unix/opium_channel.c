#include "core/opium_core.h"

#define OPIUM_CHANNEL_BUFF_LEN 2048

   opium_s32_t 
opium_channel_init(opium_channel_t *channel, opium_log_t *log)
{
   opium_channel_peer_t *peer = channel->peers;
   opium_socket_t pipe[2];

   if (socketpair(AF_UNIX, SOCK_STREAM, 0, pipe) == -1) {
      opium_log_err(log, "socketpair() failed\n");
      return OPIUM_INVALID_PID;
   }

   if (opium_nonblocking(pipe[0]) == -1) {
      opium_log_err(log, "opium_nonblocking(pipe[0]) failed\n");
      goto fail;
   }

   if (opium_nonblocking(pipe[1]) == -1) {
      opium_log_err(log, "opium_nonblocking(pipe[1]) failed\n");
      goto fail;
   }

   if (fcntl(pipe[0], F_SETFD, FD_CLOEXEC) == -1) {
      opium_log_err(log, "fnctl(F_SETFD CLOEXEC pipe[0]) failed\n");
      goto fail;
   }

   if (fcntl(pipe[1], F_SETFD, FD_CLOEXEC) == -1) {
      opium_log_err(log, "fnctl(F_SETFD CLOEXEC pipe[1]) failed\n");
      goto fail;
   }

   peer[0].fd = pipe[0];
   peer[1].fd = pipe[1];

   channel->log = log;

   return OPIUM_RET_OK;

fail:
   if (close(pipe[0]) == -1) {
      opium_log_err(log, "pipe[0] close() failed\n");
   }

   if (close(pipe[1]) == -1) {
      opium_log_err(log, "pipe[1] close() failed\n");
   }

   return OPIUM_RET_ERR;
}

   opium_s32_t 
opium_channel_fetch(opium_channel_t *channel, opium_channel_role_t role)
{
   if (opium_unlikely(role != OPIUM_CHANNEL_PARENT && role != OPIUM_CHANNEL_CHILD)) {
      opium_log_err(channel->log, "Role doesn't correspond to the expected values!\n");
      return OPIUM_RET_ERR;
   }

   opium_channel_peer_t *peer    = &channel->peers[role];
   opium_channel_peer_t *partner = &channel->peers[1 - role];
   opium_s32_t success;

   if (close(partner->fd) == -1) {
      opium_log_err(channel->log, "Failed to close partner socket\n");
   }

   channel->role = role;

   return OPIUM_RET_OK;
}

   opium_s32_t
opium_channel_write(opium_channel_t *channel, const void *data, size_t size)
{
   if (opium_unlikely(size > OPIUM_CHANNEL_BUFF_LEN)) {
      opium_log_err(channel->log, "Data size exceeds buffer limit: %zu bytes\n", size);
      return OPIUM_RET_ERR;
   }

   opium_channel_peer_t *peer = &channel->peers[channel->role];

   ssize_t written = write(peer->fd, data, size);
   if (opium_unlikely(written == -1)) {
      opium_log_err(channel->log, "Write failed on socket %d\n", peer->fd);
      return OPIUM_RET_ERR;
   }

   while (written < size) {
      ssize_t more = write(peer->fd, (char*)data + written, size - written);
      if (more == -1) {
         opium_log_err(channel->log, "Partial write failed on socket %d\n", peer->fd);
         return OPIUM_RET_ERR;
      }

      written = written + more;
   }

   return OPIUM_RET_OK;
}

   opium_s32_t 
opium_channel_read(opium_channel_t *channel, void *buffer, size_t size)
{
   if (opium_unlikely(size > OPIUM_CHANNEL_BUFF_LEN)) {
      opium_log_err(channel->log, "Data size exceeds buffer limit: %zu bytes\n", size);
      return OPIUM_RET_ERR;
   }

   opium_channel_peer_t *peer = &channel->peers[channel->role];

   ssize_t read_bytes = read(peer->fd, buffer, size);
   if (read_bytes == -1) {
      opium_log_err(channel->log, "Read failed on socket %d\n", peer->fd);
      return OPIUM_RET_ERR;
   }

   if (read_bytes < size) {
      opium_log_err(channel->log, "Partial read occurred on socket %d\n", peer->fd);
      return OPIUM_RET_ERR; 
   }

   return OPIUM_RET_OK;
}

   opium_socket_t
opium_channel_socket(opium_channel_t *channel)
{
   return channel->peers[channel->role].fd;
}
