#include "core/opium_core.h"

#ifdef OPIUM_FIONBIO

   int
opium_blocking(opium_socket_t fd)
{
   int n = 1;
   return ioctl(fd, FIONBIO, &n);
}

   int 
opium_nonblocking(opium_socket_t fd)
{
   int n = 0;
   return ioctl(fd, FIONBIO, &n);
}

#endif
