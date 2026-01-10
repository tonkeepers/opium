#ifndef OPIUM_SHM_INCLUDED_H
#define OPIUM_SHM_INCLUDED_H

#include "core/opium_core.h"

struct opium_shm_s {
   opium_str_t  name;
   u_char      *addr;
   size_t       size;
   opium_s32_t  exists;
   opium_log_t *log;
};

void        opium_shm_setsize(opium_shm_t *shm, size_t size);
size_t      opium_shm_getsize(opium_shm_t *shm);

opium_s32_t opium_shm_alloc(opium_shm_t *shm);
void        opium_shm_free(opium_shm_t *shm);

#endif /* OPIUM_SHM_INCLUDED_H */
