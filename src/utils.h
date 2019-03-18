#ifndef __HLIB_UTILS
#define __HLIB_UTILS
#include <assert.h>
#include <stdlib.h>

#define HLIB_MALLOC(type) ((type *)malloc(sizeof(type)))
#define HLIB_CALLOC(type) ((type *)calloc(1, sizeof(type)))

/**
 * Test utils
 */
#ifdef NDEBUG
#define HLIB_ASSERT_FUNC(ignore) ((void)0)
#else
#define HLIB_ASSERT_FUNC(func) ({ printf("TEST  %s\n", #func); assert(func()); })
#endif /* NDEBUG */
/**
 * @param testCases: [[testFunc, description]]
 * @param length: testCases.length
 */
#define createTestPart(testCases, length) ({ \
  for (int i = 0; i < length; i++) { \
    printf("TEST  %s\n", testCases[i][1]); \
    assert((testCases[i][0])()); \
  } \
})

#endif /* __HLIB_UTILS */
