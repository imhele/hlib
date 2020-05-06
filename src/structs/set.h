#ifndef __HLIB_STRUCTS_SET
#define __HLIB_STRUCTS_SET

#include <string.h>
#include "../symbols.h"
#include "bool.h"
#include "linklist.h"

#define Set LinkList

/**
 * @return the head of set is always an empty node, or stores meta data.
 **/
struct Set *SetCreate(void *meta)
{
  struct Set *set = HLIB_CALLOC(struct Set);
  set->value = meta, set->next = NULL;
  return set;
}

bool __SetDefaultIsValueEqual(void *a, void *b)
{
  return a == b;
}

bool SetIsStringValueEqual(void *a, void *b)
{
  return !strcmp((char *)a, (char *)b);
}

void *SetGet(struct Set *head, void *value, bool (*isValueEqual)(void *a, void *b))
{
  if (isValueEqual == DEFAULTARG)
    isValueEqual = __SetDefaultIsValueEqual;
  while ((head = head->next) != NULL)
    if (isValueEqual(head->value, value))
      return head->value;
  return NULL;
}

bool SetHas(struct Set *head, void *value, bool (*isValueEqual)(void *a, void *b))
{
  return SetGet(head, value, isValueEqual) != NULL;
}

bool SetInsert(struct Set *head, void *value, bool (*isValueEqual)(void *a, void *b))
{
  if (SetHas(head, value, isValueEqual))
    return false;

  head->next = LinkListUnshift(head->next, value, ENDARG);
  return true;
}

bool SetRemove(struct Set *head, void *value, bool (*isValueEqual)(void *a, void *b))
{
  if (isValueEqual == DEFAULTARG)
    isValueEqual = __SetDefaultIsValueEqual;
  struct Set *prev = head;
  for (head = head->next; head != NULL; prev = head, head = head->next)
    if (isValueEqual(head->value, value))
    {
      prev->next = head->next;
      free(head), head = NULL;
      return true;
    }
  return false;
}

#define SetFree LinkListFree
#define SetFreeN LinkListFreeN
#define SetFreeEach LinkListFreeEach

#endif /* __HLIB_STRUCTS_SET */
