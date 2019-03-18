#ifndef __HLIB_UTILS
#define __HLIB_UTILS
#include <assert.h>
#include <stdlib.h>
#include "./colors.h"

#define HLIB_MALLOC(type) ((type *)malloc(sizeof(type)))
#define HLIB_CALLOC(type) ((type *)calloc(1, sizeof(type)))

/**
 * Test utils
 */
#ifdef NDEBUG
#define HLIB_ASSERT_FUNC(ignore) ((void)0)
#else
#define HLIB_ASSERT_FUNC(func)                                                      \
  ({                                                                                \
    printf(coloredStr(" TEST ", BCGr, CBl) "  " coloredStr(#func, BCDe, CGr) "\n"); \
    assert(func());                                                                 \
  })
#endif /* NDEBUG */

#endif /* __HLIB_UTILS */
