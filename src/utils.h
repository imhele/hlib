#ifndef __HLIB_UTILS
#define __HLIB_UTILS
#include <stdlib.h>

#define HLIB_MALLOC(type) ((type *)malloc(sizeof(type)))
#define HLIB_CALLOC(type) ((type *)calloc(1, sizeof(type)))

#endif /* __HLIB_UTILS */
