#ifndef TYPES_TEST
#define TYPES_TEST
#include "../src/types.h"

int testCreateLinkList()
{
  char *val = "TEST";
  struct LinkList *tmp = createLinkList(null, val);
  return tmp->value == val && tmp->prev == null;
}

void testTypes()
{
  HLIB_ASSERT_FUNC(testCreateLinkList);
}

#endif /* TYPES_TEST */
