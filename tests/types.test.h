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
  console(ConsoleStart, "Create", null);
  HLIB_ASSERT_FUNC(testCreateLinkList);
  printf("\n");
}

#endif /* TYPES_TEST */
