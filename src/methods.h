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
  console(ConsoleTypeError, "TypeError: Cannot get name of null", null);
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
  while (this->value && offset--)
    this = this->prev;
  return this->value;
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
    /* split */
    if (*(arrPartObj->name) >= 127)
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
  if (index >= offset)
    return null;
  // index >= 0
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

struct Object *ArrayReverse(struct Object *this)
{
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
    return console(ConsoleTypeError, "TypeError: Assignment to symbol variable.", null);
  this->props.value = (void *)(long)value;
}

void *SymbolGetProps(struct Object *this, struct Object *value)
{
  return this->props.value;
}

#endif /* __HLIB_METHODS */
