#ifndef OPIUM_CHANNEL_INCLUDED_H 
#define OPIUM_CHANNEL_INCLUDED_H

#include "core/opium_core.h"

typedef enum {
   OPIUM_CHANNEL_PARENT = 0,
   OPIUM_CHANNEL_CHILD  = 1
} opium_channel_role_t;

typedef struct {
   opium_socket_t   fd;
} opium_channel_peer_t;

struct opium_channel_s {
   opium_channel_peer_t peers[2];
   opium_channel_role_t role;

   opium_log_t         *log;
};

opium_s32_t opium_channel_init(opium_channel_t *channel, opium_log_t *log);
opium_s32_t opium_channel_fetch(opium_channel_t *channel, opium_channel_role_t role);

opium_s32_t opium_channel_write(opium_channel_t *channel, const void *data, size_t size);
opium_s32_t opium_channel_read(opium_channel_t *channel, void *buffer, size_t size);

opium_socket_t opium_channel_socket(opium_channel_t *channel);

#endif /* OPIUM_CHANNEL_INCLUDED_H */
