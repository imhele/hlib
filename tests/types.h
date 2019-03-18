#include "../main.h"

int testCreateLinkList()
{
  char *val = "TEST";
  struct LinkList *tmp = createLinkList(null, val);
  return tmp->value == val;
}

#define types() createTestPart([])
