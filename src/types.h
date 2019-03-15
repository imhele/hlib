#ifndef __HLIB_TYPES
#define __HLIB_TYPES
#include <stdio.h>
#include <stdlib.h>

/**
 ** *******************
 ** Types definition
 ** *******************
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
 * An array is an ordered collection of data.
 * Arrays are used to store multiple values in a single variable.
 */
#define array ((void *)3)
/**
 * A string is a sequence of characters used to represent text.
 */
#define string ((void *)4)

/**
 ** *******************
 ** Constant definition
 ** *******************
 */

#define ARRAY_SPLIT_SIZE 255

/**
 ** *******************
 ** Data structure definition
 ** *******************
 */

/**
 * A closure is the combination of a function and
 * the lexical environment within which that function was declared.
 */
struct Closure
{
  struct Closure *prev;
  struct Closure **next;
  struct ArrayItem *vars;
};

struct Object
{
  char *name;
  void *type;
  void **props;
  struct Object *__proto__;
  struct Object **prototype;
};

struct ArrayItem
{
  struct Object *curr;
  struct Object *next;
};

struct Closure *Closure;
struct Object *Object;
struct Object *Symbol;
struct Object *Array;
struct Object *String;

void createSymbol(char *name);

/**
 * Variables defined in a closure can be used anywhere in the closure after the definition of it.
 * @param mode == 0: Create a new closure
 * @param mode != 0: Destroy a closure
 */
void useClosure(char mode)
{
  if (mode)
  {
    struct Closure *nextOne = (struct Closure *)malloc(sizeof(struct Closure));
    nextOne->vars = (struct ArrayItem *)malloc(sizeof(struct ArrayItem));
    if (Closure->next == null)
    {
    }
  }
  else
  {
  }
};

void useSymbol(void);

/**
 * Use object in C lang!
 */
#define useObject(varName)

/**
 * Get the value of object
 */
void *useValue(struct Object *obj)
{
  return null;
}

/**
 * Initialize the contents of the entire library.
 */
void useLib(void)
{
  /**
   * Init Closure
   */
  Closure = (struct Closure *)malloc(sizeof(struct Closure));
  Closure->prev = Closure;

  /**
   * Init Object
   */
  Object = (struct Object *)malloc(sizeof(struct Object));
  Object->name = "object";
  Object->type = object;
  // Object->prototype = Object;

  /**
   * Init Symbol
   */
  Symbol = (struct Object *)malloc(sizeof(struct Object));
  Symbol->name = "symbol";
  Symbol->type = symbol;
  // Symbol->prototype = Object;

  /**
   * Init Array
   */
  Array = (struct Object *)malloc(sizeof(struct Object));
  Array->name = "array";
  Array->type = array;
  // Array->prototype = Object;

  /**
   * Init String
   */
  String = (struct Object *)malloc(sizeof(struct Object));
  String->name = "string";
  String->type = string;
  // String->prototype = Object;

  /**
   * TODO remove test print
   */
  printf("%ld\n", sizeof(struct Object));
}

#endif /* __HLIB_SYMBOL */
