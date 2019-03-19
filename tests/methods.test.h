#ifndef METHODS_TEST
#define METHODS_TEST
#include "../src/methods.h"

int testSymbolSetProps()
{
  int testVal = 0;
  struct Object *tmp = createSymbol(null);
  SymbolSetProps(tmp, (void *)&testVal);
  return tmp->props.value != &testVal && tmp->props.value == tmp;
}

void testMethods()
{
  HLIB_ASSERT_FUNC(testSymbolSetProps);
}

#endif /* METHODS_TEST */
