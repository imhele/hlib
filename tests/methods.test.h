#ifndef METHODS_TEST
#define METHODS_TEST
#include "../src/methods.h"

int testLinkListGetItem()
{
  // [1, 2, 3] <-- Pointer
  struct LinkList *tmp = createLinkList(null, (void *)1);
  tmp = createLinkList(createLinkList(tmp, (void *)2), (void *)3);
  return LinkListGetItem(tmp, 0) == (void *)3 && LinkListGetItem(tmp, 2) == (void *)1;
}

int testLinkListReverse()
{
  // [1, 2, 3] <-- Pointer
  struct LinkList *tmp = createLinkList(null, (void *)1);
  tmp = createLinkList(createLinkList(tmp, (void *)2), (void *)3);
  // [3, 2, 1] <-- Pointer
  tmp = LinkListReverse(tmp);
  return LinkListGetItem(tmp, 2) == (void *)3 && LinkListGetItem(tmp, 0) == (void *)1;
}

int testSymbolSetProps()
{
  int testVal = 0;
  struct Object *tmp = createSymbol("tmp");
  SymbolSetProps(tmp, (void *)&testVal);
  return tmp->props.value != &testVal && tmp->props.value == tmp;
}

int testArrayGetProp()
{
  struct Object *arr = createArray("arr");
  return *(int *)(PrimitiveGetProps(ArrayGetProp(arr, "length"))) == 0;
}

int testArrayPush()
{
  struct Object *element = createPrimitive("element", null);
  struct Object *arr = createArray("arr");
  if (PrimitiveGetProps(ArrayGetProps(arr)->value) != null)
    return 0;
  char pushLength = 127;
  while (pushLength--)
    ArrayPush(arr, element, element, null);
  int *length = PrimitiveGetProps(ArrayGetProp(arr, "length"));
  // [...127..., ...127...] <-- Pointer
  struct LinkList *arrPart = PrimitiveGetProps(ArrayGetProps(arr)->value);
  return *length == 127 * 2 && arrPart->value == element;
}

int testArrayGetItem()
{
  struct Object *element = createPrimitive("element", null);
  struct Object *arr = createArray("arr");
  // [(void *)1] <-- Pointer
  ArrayPush(arr, (void *)1, null);
  if (ArrayGetItem(arr, 0) != (void *)1)
    return 0;
  short pushLength = 125;
  // [(void *)1, ...125...] <-- Pointer
  while (pushLength--)
    ArrayPush(arr, element, null);
  if (ArrayGetItem(arr, 125) != element)
    return 0;
  if (ArrayGetItem(arr, 126) != null)
    return 0;
  // [(void *)1, ...125..., (void *)2] <-- Pointer
  ArrayPush(arr, (void *)2, null);
  return ArrayGetItem(arr, -1) == (void *)2;
}

void testMethods()
{
  HLIB_ASSERT_FUNC(testLinkListGetItem);
  HLIB_ASSERT_FUNC(testLinkListReverse);
  HLIB_ASSERT_FUNC(testSymbolSetProps);
  HLIB_ASSERT_FUNC(testArrayGetProp);
  HLIB_ASSERT_FUNC(testArrayPush);
  HLIB_ASSERT_FUNC(testArrayGetItem);
}

#endif /* METHODS_TEST */
