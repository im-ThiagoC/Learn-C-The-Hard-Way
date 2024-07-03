#ifndef __dbg_h__
#define __dbg_h__

#include <stdio.h>
#include <errno.h>
#include <string.h>

#ifdef NDEBUG
#define debug(M, ...)
#else
#define debug(M, ...) fprintf_s(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#define clean_errno() (errno == 0 ? "None" : strerror(errno))

#define log_err(M, ...)  fprintf_s (stderr, "[ERROR] (%s:%d: errno: %s in %s function) " M "\n", __FILE__, __LINE__, clean_errno(), __PRETTY_FUNCTION__, ##__VA_ARGS__)
#define log_warn(M, ...) fprintf_s (stderr, "[WARN] (%s:%d: errno: %s in %s function) " M "\n", __FILE__, __LINE__, clean_errno(), __PRETTY_FUNCTION__, ##__VA_ARGS__)
#define log_info(M, ...) fprintf_s (stderr, "[INFO] (%s:%d in %s function) " M "\n", __FILE__, __LINE__,__PRETTY_FUNCTION__, ##__VA_ARGS__)

#define check(A, M, ...) if(!(A)) \
    { log_err(M, ##__VA_ARGS__); errno = 0; goto error; }

#define sentinel(M, ...) \
    { log_err(M, ##__VA_ARGS__); errno = 0; goto error; }

#define check_mem(A) check((A), "Out of Memory.")

#define check_debug(A, M, ...) if(!(A)) \
    { debug(M, ##__VA_ARGS__); errno = 0; goto error; }

#endif