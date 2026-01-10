#include "core/opium_core.h"
#include <sys/epoll.h>

struct opium_process_control_s {
   /* CPU CONTROL - что можно задать */
   struct {
      opium_s32_t    nice;          // Желаемый nice value
      opium_s32_t    policy;        // Политика планирования (SCHED_*)
      opium_cpuset_t affinity;      // На каких CPU разрешено работать
   } cpu;

   /* MEMORY CONTROL - ограничения */
   struct {
      opium_u64_t    limit_bytes;   // Лимит памяти (bytes)
      opium_u64_t    soft_limit;    // Мягкий лимит
      opium_s32_t    oom_score_adj; // OOM adjustment score
   } memory;

   /* IO CONTROL - приоритеты IO */
   struct {
      opium_s32_t    ioclass;       // Класс IO (IOPRIO_CLASS_*)
      opium_s32_t    ioprio;        // Приоритет внутри класса
      opium_u64_t    read_bps_limit; // Лимит чтения (bytes/sec)
      opium_u64_t    write_bps_limit;// Лимит записи
   } io;

   /* CGROUP CONTROL - куда поместить */
   struct {
      char          *cgroup_path;   // Путь в cgroup hierarchy
      opium_s32_t    cpu_shares;    // Доля CPU
      opium_u64_t    cpu_quota_us;  // Квота CPU (microseconds)
      opium_u64_t    cpu_period_us; // Период CPU
   } cgroup;

   /* NETWORK CONTROL - сетевое ограничение */
   struct {
      char          *network_class; // Класс сети (для traffic control)
      opium_u64_t    bandwidth_bps; // Лимит bandwidth
      opium_s32_t    net_cls_major; // Net class ID
      opium_s32_t    net_cls_minor;
   } network;

   /* SECURITY CONTROL - безопасность */
   struct {
      opium_s32_t    securebits;    // Secure bits flags
      char         **capabilities;  // Какие capabilities разрешены
      opium_s32_t    cap_count;
      opium_s32_t    no_new_privs;  // Флаг no_new_privs
   } security;

   /* NAMESPACE CONTROL - изоляция */
   struct {
      opium_s32_t    clone_flags;   // Флаги для clone()
      char          *uts_name;      // Hostname в UTS namespace
      char          *ipc_path;      // Путь для IPC namespace
      char          *net_path;      // Путь для Network namespace
      char          *pid_path;      // Путь для PID namespace
      char          *user_path;     // Путь для User namespace
      char          *mnt_path;      // Путь для Mount namespace
   } namespace;

   /* FILE DESCRIPTOR CONTROL - что делать с файлами */
   struct {
      opium_fdmap_t *fd_map;        // Маппинг файловых дескрипторов
      opium_s32_t    fd_count;
      opium_s32_t    close_on_exec; // Флаги close-on-exec
   } fd;
};
