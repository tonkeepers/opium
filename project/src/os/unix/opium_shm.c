#include "core/opium_core.h"
#include "core/opium_config.h"

/* Philosophies of Shared Memory
 * In LINUX/UNIX processes are closed universes.
 *
 * When a process is created (fork() or exec()):
 * - Creates its OWN virtual address space.
 * - Copies/creates its OWN resources.
 * - Establishes its OWN boundaries.
 *
 * It`s like parallel realities:
 * - Can`t see each other`s memory
 * - Can`t directly influence each other`s data
 * - Have their own copies of variables
 * 
 * The magic of virtual memory: everyone in their own sandbox.
 *
 * *** Example ***
 *
 * Need to monitor:
 * - Number of HTTP requests per second
 * - CPU usage
 * - Volume of transferred data
 *
 * Problem: 10 processes, each collecting statistics
 * Need to aggregate into a single dashboard
 *
 * WITHOUT shared memory:
 * 1. Each process writes to ITS OWN file
 * 2. A separate process reads 10 files
 * 3. Aggregates and displays
 *
 * Slow: disk I/O, synchronization, latency
 *
 * With shared memory:
 * 1. Allocate a SHARED buffer in memory
 * 2. Each process writes to ITS OWN buffer segment
 * 3. The dashboard reads ONE memory area
 *
 * Fast: memory, atomic operations, real time
 *
 */

/* Parameters mmap()
 * 1. addr   - with the help of NULL we tell the kernel to decide for itself
 * which address to allocate;
 * 2. len    - how many bytes are needed;
 * 3. prot   - what access rights (read/write/execute);
 * 4. flags  - how to allocate memory (anonymous/file, shared/private);
 * 5. fd     - which file to map (-1 for anonymous);
 * 6. offset - from which place in the file (0 for anonymous);
 *
 * The munmap() function - unmaps memory
 *
 * Prototype: int munmap(void *addr, size_t length);
 *
 * Parameters:
 * 1. addr - the exact same address returned by mmap()
 * 2. len  - the exact same size passed to mmap()
 */

#ifdef OPIUM_HAVE_MAP_ANON
/* *** SEMANTICS *** 
 * "Kernel, be my direct allocator. Give me raw memory."
 * We use MAP_ANON/MAP_ANONYMOUS - the most efficient method
 * of allocating shared memory on modern systems.
 *
 * Advantages:
 * - One system call instead of several
 * - Does not require a file descriptor
 * - Direct allocation from the free memory pool
 */

   opium_s32_t
opium_shm_alloc(opium_shm_t *shm)
{
   shm->addr = (u_char*) mmap(NULL, shm->size, PROT_READ|PROT_WRITE, 
         MAP_ANON|MAP_SHARED, -1, 0);

   if (opium_unlikely(shm->addr == MAP_FAILED)) {
      opium_log_err(shm->log, "mmap(MAP_ANON|MAP_SHARED, %uz) failed", shm->size);
      return OPIUM_RET_ERR;
   } 

   return OPIUM_RET_OK;
}

   void
opium_shm_free(opium_shm_t *shm)
{
   if (opium_unlikely(munmap((void*)shm->addr, shm->size) == -1)) {
      opium_log_err(shm->log, "munmap(%p, %uz) failed", shm->addr, shm->size);
   }
}

#elif OPIUM_HAVE_DEV_ZERO

#elif OPIUM_HAVE_SYSV_SHM

#endif

void opium_shm_setsize(opium_shm_t *shm, size_t size)
{
   shm->size = size; 
}

size_t opium_shm_getsize(opium_shm_t *shm)
{
   return shm->size;
}
