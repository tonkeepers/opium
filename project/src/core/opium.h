#ifndef OPIUM_INCLUDE_H
#define OPIUM_INCLUDE_H

#if defined (__linux)
#define OPIUM_LINUX   1
#include "os/unix/opium_lib.h"

#elif defined(_WIN32)

#define OPIUM_WINDOWS 1 
#error "Win No"

#else
#error "No"

#endif

int opium_is_little_endian(void);
size_t opium_round_of_two(size_t x);
size_t opium_log2(size_t x);

void opium_debug_point(void);

#endif /* OPIUM_INCLUDE_H */
