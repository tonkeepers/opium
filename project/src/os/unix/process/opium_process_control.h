#ifndef OPIUM_PROCESS_CONTROL_INCLUDED_H
#define OPIUM_PROCESS_CONTROL_INCLUDED_H

#include "core/opium_core.h"

#include "control/opium_process_control_cpu.h"
#include "control/opium_process_control_memory.h"
#include "control/opium_process_control_net.h"
#include "control/opium_process_control_io.h"
#include "control/opium_process_control_fd.h"
#include "control/opium_process_control_cgroup.h"

typedef struct {
   char       *name;
   void       *data;

   opium_s32_t nice;
   opium_s32_t state;

   opium_s32_t thread_n;

   opium_s32_t daemon;

} opium_process_control_t;

#endif /* OPIUM_PROCESS_CONTROL_INCLUDED_H */
