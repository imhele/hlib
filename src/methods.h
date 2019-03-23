#ifndef __HLIB_METHODS
#define __HLIB_METHODS
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "./types.h"
#include "./utils.h"

char *ObjectGetName(struct Object *this)
{
  if (this)
    return this->name;
  console(ConsoleError, "TypeError: Cannot get name of null", null);
  return null;
}

/**
 ** *******************
 **      LinkList
 ** *******************
 */

void *LinkListGetItem(struct LinkList *this, int offset)
{
  if (offset < 0)
    return null;
  while (this && offset--)
    this = this->prev;
  return this ? this->value : null;
}

struct LinkList *LinkListReverse(struct LinkList *this)
{
  struct LinkList *tmpA = null;
  struct LinkList *tmpB = this;
  while (tmpB)
  {
    this = tmpB;
    tmpB = this->prev;
    this->prev = tmpA;
    tmpA = this;
  }
  return this;
}

struct LinkList *LinkListFilter(struct LinkList *this, int (*filter)(void *item, int offset, struct LinkList *this))
{
  int offset = 0;
  struct LinkList *result = null;
  while (this)
  {
    if (filter(this->value, offset, this))
      result = createLinkList(result, this->value);
    offset++;
    this = this->prev;
  }
  return result;
}

struct LinkList *LinkListSplice(struct LinkList *this, int offset, int howmany, ...)
{
  /* init vars */
  struct Object *element;
  struct LinkList *tmp = null;
  struct LinkList *start = null;
  struct LinkList *deleted = null;

  /* need change head pointer */
  if (offset <= 0 || offset - howmany < 0 || !this)
  {
    tmp = this;
    if (this)
    {
      start = this->prev;
      start = createLinkList(start, this->value);
    }
    va_list argv;
    va_start(argv, howmany);
    while ((element = va_arg(argv, struct Object *)))
      start = createLinkList(start, element);
    va_end(argv);
    if (start)
      *this = *start;
    return deleted;
  }

  /* delete from `offset - howmany` */
  offset = offset - howmany - 1;
  /* move pointer */
  while (this->prev && offset-- >= 0)
    this = this->prev;
  tmp = this;
  this = this ? this->prev : null;
  /* start delete */
  while (this && howmany--)
  {
    deleted = createLinkList(deleted, this->value);
    start = this;
    this = this->prev;
    free(start);
  }

  /* insert will start from `start` */
  start = this;
  /* push elements */
  va_list argv;
  va_start(argv, howmany);
  while ((element = va_arg(argv, struct Object *)))
    start = createLinkList(start, element);
  va_end(argv);
  tmp->prev = start;
  return deleted;
}

struct LinkList *LinkListFind(struct LinkList *this, int (*find)(void *item, int offset, struct LinkList *this))
{
  int offset = 0;
  while (this)
  {
    if (find(this->value, offset, this))
      return this->value;
    offset++;
    this = this->prev;
  }
  return null;
}

/**
 ** *******************
 **     Primitive
 ** *******************
 */

void PrimitiveSetProps(struct Object *this, void *value)
{
  if (this->props.value)
    free(this->props.value);
  this->props.value = value;
}

/**
 * Get the address of actual value of primitive
 */
void *PrimitiveGetProps(struct Object *this)
{
  return this->props.value;
}

/**
 ** *******************
 **       Array
 ** *******************
 */

void ArraySetProps(struct Object *this, struct LinkList *value)
{
  // if (this->props.list != null)
  //  free(this->props.list);
  this->props.list = value;
}

struct LinkList *ArrayGetProps(struct Object *this)
{
  return this->props.list;
}

struct Object *ArrayGetProp(struct Object *this, char *propName)
{
  if (this->props.list == null)
    return null;
  struct LinkList *propsPointer = this->props.list;
  while (propsPointer->value)
  {
    /**
     * Primitive that name of it has only one letter will be treated as array parts
     */
    if (*(ObjectGetName(propsPointer->value) + 1))
      if (!strcmp(ObjectGetName(propsPointer->value), propName))
        return propsPointer->value;
    propsPointer = propsPointer->prev;
  }
  return null;
}

int ArrayPush(struct Object *this, ...)
{
  /**
   * @name: `*name` is the length of current part
   * @type: primitive
   * @props {LinkList}: Store some of array items
   */
  struct Object *arrPartObj = this->props.list->value;
  va_list argv;
  va_start(argv, this);
  /**
   * Get item from `...`
   * @type: object
   */
  struct Object *element;
  int *length = PrimitiveGetProps(ArrayGetProp(this, "length"));
  *length -= *(arrPartObj->name);
  while ((element = va_arg(argv, struct Object *)))
  {
    /**
     *? need to create a new array part after added any prop,
     *? or use the following code to avoid props being treated as array part:
     * ```c
     * if (PrimitiveGetProps(arrPartObj))
     *   continue;
     * ```
     */
    /* split */
    /**
     * Keep a space and try to avoid any array parts
     * that stores less than 10 elements after using `splice`
     */
    if (*(arrPartObj->name) >= 100)
    {
      /* increase length */
      *length += *(arrPartObj->name);
      /* create a new part */
      arrPartObj = createPrimitive(HLIB_CALLOC(char), null);
      /* link new part to old one in array */
      this->props.list = createLinkList(this->props.list, arrPartObj);
    }
    /* increase the length (`*name`) of current part */
    *(arrPartObj->name) = (char)(*(arrPartObj->name) + 1);
    /* push one element */
    arrPartObj->props.value = createLinkList(arrPartObj->props.value, element);
  }
  *length += *(arrPartObj->name);
  va_end(argv);
  return *length;
}

struct Object *ArrayGetItem(struct Object *this, int index)
{
  if (!this->props.list)
    return null;
  /**
   * the total length of the parts that from `0` to the tail pointer
   * of the nearest array part which contains `index`.
   */
  int offset = *(int *)PrimitiveGetProps(ArrayGetProp(this, "length"));
  if (index < 0)
    index += offset;
  if (index >= offset || index < 0)
    return null;
  struct LinkList *propsPointer = this->props.list;
  /**
   * the total length of the parts that from `0` to the tail pointer
   * of the nearest array part which **does not** contain `index`.
   */
  int nextOffset = offset - *ObjectGetName(propsPointer->value);
  while (nextOffset > index)
  {
    propsPointer = propsPointer->prev;
    offset = nextOffset;
    nextOffset -= *(int *)((struct Object *)propsPointer->value)->name;
  }
  return LinkListGetItem(PrimitiveGetProps(propsPointer->value), offset - index - 1);
}

struct Object *ArrayFilter(struct Object *this, int (*filter)(struct Object *item, int index))
{
  /**
   * TODO filter
   */
  if (!this->props.list)
    return this;
  return null;
}

struct Object *ArrayReverse(struct Object *this)
{
  /**
   * TODO reverse
   */
  return this;
}

/**
 ** *******************
 **       Symbol
 ** *******************
 */

void SymbolSetProps(struct Object *this, struct Object *value)
{
  if (this->props.value)
    return console(ConsoleError, "TypeError: Assignment to symbol variable.", null);
  this->props.value = (void *)(long)value;
}

void *SymbolGetProps(struct Object *this, struct Object *value)
{
  return this->props.value;
}

#endif /* __HLIB_METHODS */
