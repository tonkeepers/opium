#ifndef OPIUM_STRING_INCLUDE_H
#define OPIUM_STRING_INCLUDE_H 

#include "core/opium_core.h"

typedef struct {
   char  *data;
   size_t len;
} opium_str_t;
#define opium_str(str)              (opium_str_t) { (u_char*)str, strlen(str) }
#define opium_null_string()         (opium_str_t) { NULL, 0 }

#define opium_str_set(str, text)    (opium_str_t) { (str)->data = (u_char*)text, (str)->len = strlen(text) }
#define opium_str_null(str)         (opium_str_t) { (str)->data = NULL, (str)->len = 0 }

#define opium_strncmp(s1, s2, n)    strncmp((const char *) s1, (const char *) s2, n)
#define opium_strcmp(s1, s2)        strcmp((const char *) s1, (const char *) s2)

#define opium_strstr(s1, s2)        strstr((const char *) s1, (const char *) s2)
#define opium_strchr(s1, c)         strchr((const char *) s1, (int) c)
#define opium_strlen(s)             strlen((const char *) s)

#define opium_memcpy(dst, src, n)   (void) memcpy(dst, src, n)
#define opium_cpymem(dst, src, n)   (((u_char *) memcpy(dst, src, n)) + (n))

#define opium_memzero(buf, n)       (void) memset(buf, 0, n)
#define opium_memset(buf, c, n)     (void) memset(buf, c, n)

#define opium_memmove(dst, src, n)  (void) memmove(dst, src, n)
#define opium_movemem(dst, src, n)  (((u_char *) memmove(dst, src, n)) + (n))
#define opium_memcmp(s1, s2, n)     memcmp(s1, s2, n)

#define opium_tolower(c)            (u_char) ((c >= 'A' && c <= 'Z') ? (c | 0x20) : c)
#define opium_toupper(c)            (u_char) ((c >= 'a' && c <= 'z') ? (c & ~0x20) : c)

u_char *opium_cpystrn(u_char *dst, const u_char *src, size_t n);
opium_s32_t opium_snprintf(u_char *buf, size_t max, const char *fmt, ...);

#endif /* OPIUM_STRING_INCLUDE_H */
