#ifndef __HLIB_TYPES
#define __HLIB_TYPES
#include <stdio.h>
#include <stdlib.h>

/**
 ** Types definition
 */
/**
 * A null value represents a reference that points, generally intentionally,
 * to a nonexistent or invalid object or address.
 */
#define null ((void *)0)
/**
 * Object refers to a data structure containing data and instructions for working with the data.
 */
#define object ((void *)1)
/**
 * A value having the data type "symbol" can be referred to as a "symbol value."
 * A symbol value is created as an anonymous, unique value. A symbol may be used as an object property.
 */
#define symbol ((void *)2)

/**
 * Basic object type
 */
struct Object
{
  char *name;
  void *type;
  struct Object **prototype;
  struct Object *__proto__;
};

struct Object *Object;

struct Symbol
{
  char *name;
  void *type;
  struct Object **prototype;
  struct Object *__proto__;
};

struct Symbol *Symbol;

void createSymbol(char *name);

/**
 * Variables defined in a closure can be used anywhere in the closure after the definition of it.
 */
void useClosure(char exit);

void useSymbol(void);

/**
 * Use object in C lang!
 */
#define useObject(varName)

/**
 * Initialize the contents of the entire library.
 */
void useLib(void)
{
  Object = (struct Object *)malloc(sizeof(struct Object));
  Object->name = "object";
  Object->type = object;
  // Object->prototype = Object;
  Object->__proto__ = null;

  Symbol = (struct Symbol *)malloc(sizeof(struct Symbol));
  Symbol->name = "symbol";
  Symbol->type = symbol;
  // Symbol->prototype = Object;
  Symbol->__proto__ = null;
}

#endif /* __HLIB_SYMBOL */
