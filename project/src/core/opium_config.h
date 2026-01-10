#ifndef OPIUM_CONFIG_INCLUDE_H
#define OPIUM_CONFIG_INCLUDE_H

#include "core/opium_core.h"

#ifdef OPIUM_LINUX 
    #define OPIUM_HAVE_MAP_ANON       1
    #define OPIUM_HAVE_POSIX_SHM      1
    #define OPIUM_HAVE_SYSV_SHM       1
    #define OPIUM_HAVE_DEV_ZERO       1
#endif

#endif /* OPIUM_CONFIG_INCLUDE_H */
