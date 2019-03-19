#ifndef __HLIB_METHODS
#define __HLIB_METHODS
#include <stdarg.h>
#include <stdlib.h>
#include "./types.h"

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

void ArrayPush(struct Object *this, ...)
{
  struct Object *curr = this->props.list->value;
  va_list argv;
  va_start(argv, this);
  struct Object *element;
  while ((element = va_arg(argv, struct Object *)) != null)
  {
    if ((long)curr->name / 256 >= sizeof(ARRAY_SPLIT_TYPE))
    {
      curr = createPrimitive(0, null);
      this->props.list = createLinkList(this->props.list, curr);
    }
  }
  va_end(argv);
}

/**
 ** *******************
 **       Symbol
 ** *******************
 */

void SymbolSetProps(struct Object *this, struct Object *value)
{
  if (this->props.value != null)
    return console(ConsoleTypeError, "TypeError: Assignment to symbol variable.");
  this->props.value = (void *)(long)value;
}

#endif /* __HLIB_METHODS */
