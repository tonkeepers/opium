#ifndef OPIUM_SOCKET_INCLUDED_H
#define OPIUM_SOCKET_INCLUDED_H

#include "core/opium_core.h"

typedef int opium_socket_t;

#define OPIUM_WRITE_SHUTDOWN  SHUT_WR
#define OPIUM_READ_SHUTDOWN   SHUT_RD
#define OPIUM_RDWR_SHUTDOWN   SHUT_RDWR

#define opium_socket            socket
#define opium_socket_f          "socket()"

#define opium_socket_shutdown    shutdown
#define opium_socket_shutdown_f "shutdown()"

#define opium_socket_close       close 
#define opium_socket_close_f     "close()"

#if OPIUM_LINUX
#else
#endif

#ifdef OPIUM_FIONBIO

int opium_nonblocking(opium_socket_t fd);
int opium_blocking(opium_socket_t fd);

#else

#define opium_nonblocking(fd) fcntl(fd, S_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK) 
#define opium_blocking(fd)    fcntl(fd, S_SETFL, fcntl(fd, F_GETFL) & ~O_NONBLOCK)

#endif

#ifdef OPIUM_FIONREAD



#else



#endif

#endif /* OPIUM_SOCKET_INCLUDED_H */
