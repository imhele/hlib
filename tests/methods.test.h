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

int testArrayGetProp()
{
  struct Object *arr = createArray(null);
  return *(int *)(PrimitiveGetProps(ArrayGetProp(arr, "length"))) == 0;
}

int testArrayPush()
{
  struct Object *element = createPrimitive(null, null);
  struct Object *arr = createArray(null);
  if (PrimitiveGetProps(ArrayGetProps(arr)->value) != null)
    return 0;
  int pushLength = 257;
  while (pushLength--)
    ArrayPush(arr, element, null);
  int *length = PrimitiveGetProps(ArrayGetProp(arr, "length"));
  struct LinkList *arrPart = PrimitiveGetProps(ArrayGetProps(arr)->value);
  return *length == 257 && arrPart->value == element;
}

void testMethods()
{
  HLIB_ASSERT_FUNC(testSymbolSetProps);
  HLIB_ASSERT_FUNC(testArrayGetProp);
  HLIB_ASSERT_FUNC(testArrayPush);
}

#endif /* METHODS_TEST */
