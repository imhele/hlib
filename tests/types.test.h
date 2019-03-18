#include "../main.h"

int testCreateLinkList()
{
  char *val = "TEST";
  struct LinkList *tmp = createLinkList(null, val);
  return tmp->value == val;
}

void testTypes()
{
  HLIB_ASSERT_FUNC(testCreateLinkList);
}
