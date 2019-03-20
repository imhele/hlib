#ifndef __HLIB_METHODS
#define __HLIB_METHODS
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "./types.h"
#include "./utils.h"

/**
 ** *******************
 **     Primitive
 ** *******************
 */

void PrimitiveSetProps(struct Object *this, void *value)
{
  if (this->props.value != null)
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

struct Object *ArrayGetProp(struct Object *this, char *prop)
{
  if (this->props.list == null)
    return null;
  struct LinkList *tmp = this->props.list;
  while (tmp->value != null)
  {
    if (((struct Object *)tmp->value)->name)
      if (!strcmp(((struct Object *)tmp->value)->name, prop))
        return tmp->value;
    tmp = tmp->prev;
  }
  return null;
}

int *ArrayPush(struct Object *this, ...)
{
  struct Object *curr = this->props.list->value;
  va_list argv;
  va_start(argv, this);
  struct Object *element;
  int *length = PrimitiveGetProps(ArrayGetProp(this, "length"));
  *length -= *(curr->name);
  while ((element = va_arg(argv, struct Object *)) != null)
  {
    curr->props.value = createLinkList(curr->props.value, element);
    *(curr->name) = (char)(*(curr->name) + 1);
    if (*(curr->name) >= 127)
    {
      *length += *(curr->name);
      curr = createPrimitive(HLIB_CALLOC(char), null);
      this->props.list = createLinkList(this->props.list, curr);
    }
  }
  *length += *(curr->name);
  va_end(argv);
  return length;
}

struct Object *ArrayReverse(struct Object *this)
{
  char *reverse = PrimitiveGetProps(ArrayGetProp(this, "reverse"));
  *reverse = *reverse ? 0 : 1;
  return this;
}

/**
 ** *******************
 **       Symbol
 ** *******************
 */

void SymbolSetProps(struct Object *this, struct Object *value)
{
  if (this->props.value != null)
    return console(ConsoleTypeError, "TypeError: Assignment to symbol variable.", null);
  this->props.value = (void *)(long)value;
}

void *SymbolGetProps(struct Object *this, struct Object *value)
{
  return this->props.value;
}

#endif /* __HLIB_METHODS */
