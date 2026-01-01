#ifndef OPIUM_ALLOC_INCLUDE_H
#define OPIUM_ALLOC_INCLUDE_H

#include "core/opium_core.h"

void *opium_malloc(size_t size, opium_log_t *log);
void *opium_calloc(size_t size, opium_log_t *log);
void opium_free(void *ptr, opium_log_t *log);

void *opium_mmap(size_t size, opium_log_t *log);
void opium_munmap(void *data, size_t size, opium_log_t *log);

void *opium_memalign(size_t alignment, size_t size, opium_log_t *log);

#endif /* OPIUM_ALLOC_INCLUDE_H */
