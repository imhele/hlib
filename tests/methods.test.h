#ifndef METHODS_TEST
#define METHODS_TEST
#include <stdlib.h>
#include "../src/utils.h"
#include "../src/methods.h"

/**
 ** *******************
 **      LinkList
 ** *******************
 */

struct LinkList *__createLinkListWithLength(long length)
{
  if (length <= 0)
    return null;
  long index = 0;
  struct LinkList *list = null;
  while (length--)
    list = createLinkList(list, (void *)++index);
  return list;
}

int testLinkListGetItem()
{
  long nullChar = 0;
  if (LinkListGetItem((struct LinkList **)&nullChar, 0))
    return 0;
  // [1, 2, 3] <-- Pointer
  struct LinkList *tmp = __createLinkListWithLength(3);
  if (LinkListGetItem(&tmp, 3))
    return 0;
  return LinkListGetItem(&tmp, 0) == (void *)3 && LinkListGetItem(&tmp, 2) == (void *)1;
}

int testLinkListReverse()
{
  // [1, 2, 3] <-- Pointer
  struct LinkList *tmp = __createLinkListWithLength(3);
  // [3, 2, 1] <-- Pointer
  LinkListReverse(&tmp);
  return LinkListGetItem(&tmp, 2) == (void *)3 && LinkListGetItem(&tmp, 0) == (void *)1;
}

int __testLinkListFilterCallback(void *item, int offset, struct LinkList *this)
{
  if (item == (void *)2)
    return 1;
  free(item);
  return 0;
}

int testLinkListFilter()
{
  int *value = HLIB_CALLOC(int);
  // [value, 2] <-- Pointer
  struct LinkList *tmp = createLinkList(null, value);
  tmp = createLinkList(tmp, (void *)2);
  if (LinkListGetItem(&tmp, 1) != value)
    return 0;
  if (LinkListGetItem(&tmp, 0) != (void *)2)
    return 0;
  // [2] <-- Pointer
  struct LinkList *res = LinkListFilter(&tmp, __testLinkListFilterCallback);
  return LinkListGetItem(&res, 0) == (void *)2;
}

int testLinkListSplice()
{
  // [1, 2, 3] <-- Pointer
  struct LinkList *tmp = __createLinkListWithLength(3);
  // [2, 3] <-- Pointer
  LinkListSplice(&tmp, 2, 1, null);
  if (LinkListGetItem(&tmp, 2))
    return 0;
  if (LinkListGetItem(&tmp, 1) != (void *)2)
    return 0;
  if (LinkListGetItem(&tmp, 0) != (void *)3)
    return 0;
  // [3] <-- Pointer
  LinkListSplice(&tmp, 1, 1, null);
  if (LinkListGetItem(&tmp, 1))
    return 0;
  if (LinkListGetItem(&tmp, 0) != (void *)3)
    return 0;
  // [2, 3] <-- Pointer
  LinkListSplice(&tmp, 1, 0, (void *)2, null);
  if (LinkListGetItem(&tmp, 1) != (void *)2)
    return 0;
  if (LinkListGetItem(&tmp, 0) != (void *)3)
    return 0;
  // [2, 3, 4] <-- Pointer
  LinkListSplice(&tmp, 0, 0, (void *)4, null);
  if (LinkListGetItem(&tmp, 0) != (void *)4)
    return 0;
  // [2, 3] <-- Pointer
  LinkListSplice(&tmp, 0, 1, null);
  return LinkListGetItem(&tmp, 0) == (void *)3;
}

int __testLinkListFindCallback(void *item, int offset, struct LinkList *this)
{
  if (item == (void *)2)
    return 1;
  return 0;
}

int testLinkListFind()
{
  int *value = HLIB_CALLOC(int);
  // [value, 2] <-- Pointer
  struct LinkList *tmp = createLinkList(null, value);
  tmp = createLinkList(tmp, (void *)2);
  void *res = LinkListFind(&tmp, __testLinkListFindCallback);
  return res == (void *)2;
}

/**
 ** *******************
 **       Array
 ** *******************
 */

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

/**
 ** *******************
 **       Symbol
 ** *******************
 */

int testSymbolSetProps()
{
  int testVal = 0;
  struct Object *tmp = createSymbol("tmp");
  SymbolSetProps(tmp, (void *)&testVal);
  return tmp->props.value != &testVal && tmp->props.value == tmp;
}

int __test3_1(char *inputStr)
{
  int strOffset = -1;
  struct LinkList *Stack = null;
  while (*(inputStr + ++strOffset))
  {
    printf("%c\n", *(inputStr + strOffset));
    if (*(inputStr + strOffset) == '{' || *(inputStr + strOffset) == '[' || *(inputStr + strOffset) == '(')
      Stack = createLinkList(Stack, inputStr + strOffset);
    else if (*(inputStr + strOffset) == '}')
    {
      struct LinkList *deleted = (struct LinkList *)LinkListSplice(&Stack, 0, 1, null);
      char *prev = (char *)LinkListGetItem(&deleted, 0);
      printf("%p\n", prev);
      if (!prev || *prev != '{')
        return 0;
    }
    else if (*(inputStr + strOffset) == ']')
    {
      struct LinkList *deleted = (struct LinkList *)LinkListSplice(&Stack, 0, 1, null);
      char *prev = (char *)LinkListGetItem(&deleted, 0);
      if (!prev || *prev != '[')
        return 0;
    }
    else if (*(inputStr + strOffset) == ')')
    {
      struct LinkList *deleted = (struct LinkList *)LinkListSplice(&Stack, 0, 1, null);
      char *prev = (char *)LinkListGetItem(&deleted, 0);
      if (!prev || *prev != '(')
        return 0;
    }
  }
  // Length of Stack should be 0
  if (LinkListGetItem(&Stack, 0))
    return 0;
  return 1;
}

int test3_1()
{
  return __test3_1("...[...{...}...[...]...]...[...]...(...)...");
}

void testMethods()
{
  // HLIB_ASSERT_FUNC(test3_1);
  /* LinkList */
  console(ConsoleStart, "LinkList", null);
  HLIB_ASSERT_FUNC(testLinkListGetItem);
  HLIB_ASSERT_FUNC(testLinkListReverse);
  HLIB_ASSERT_FUNC(testLinkListFilter);
  HLIB_ASSERT_FUNC(testLinkListSplice);
  HLIB_ASSERT_FUNC(testLinkListFind);
  printf("\n");

  /* Array */
  console(ConsoleStart, "Array", null);
  HLIB_ASSERT_FUNC(testArrayGetProp);
  HLIB_ASSERT_FUNC(testArrayPush);
  HLIB_ASSERT_FUNC(testArrayGetItem);
  printf("\n");

  /* Symbol */
  console(ConsoleStart, "Symbol", null);
  HLIB_ASSERT_FUNC(testSymbolSetProps);
  printf("\n");
}

#endif /* METHODS_TEST */
