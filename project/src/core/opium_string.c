#include "core/opium_core.h"

   u_char *
opium_cpystrn(u_char *dst, const u_char *src, size_t n)
{
   if (n == 0) {
      return dst;
   }

   while (--n) {
      *dst = *src;

      if (*dst == '\0') {
         return dst;
      }

      dst++;
      src++;
   }

   *dst = '\0';
   return dst;
}

   opium_s32_t
opium_snprintf(u_char *buf, size_t max, const char *fmt, ...)
{
   va_list args;
   opium_s32_t n;

   if (max == 0) {
      return 0;
   }

   va_start(args, fmt);
   n = vsnprintf((char *)buf, max, fmt, args);
   va_end(args);

   /* Ensure null termination */
   if (n >= (opium_s32_t)max) {
      buf[max - 1] = '\0';
   }

   return (n < 0) ? 0 : n;
}
