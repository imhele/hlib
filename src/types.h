#ifndef __HLIB_TYPES
#define __HLIB_TYPES
#include <stdio.h>
#include "utils.h"

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

#define ARRAY_SPLIT_TYPE char
#define STRING_SPLIT_TYPE char

/**
 ** *******************
 ** Data structure definition
 ** *******************
 */

struct LinkList
{
  void *value;
  struct LinkList *prev;
};

/**
 * A closure is the combination of a function and
 * the lexical environment within which that function was declared.
 */
struct Closure
{
  /**
   * @type: array
   */
  struct Object *vars;
  struct Closure *parent;
  struct LinkList *children;
};

/**
 *? @ATTENTION: Only primitive value use `BaseProp.value`. [type == null]
 *? @ATTENTION: Only array and string type use `BaseProp.list`. [type == array]
 */
union BaseProp {
  void *value;
  struct Object *arr;
  struct LinkList *list;
};

struct Object
{
  char *name;
  void *type;
  /**
   * Property that both instances and classes have.
   * @type: array
   */
  union BaseProp props;
  /**
   * Instance-specific property.
   * @type: object
   * @value: Class corresponding to the instance.
   */
  struct Object *__proto__;
  /**
   * The method from the parent class does not inherit directly,
   * but traces its origin through the prototype chain.
   */
  struct LinkList *methods;
  struct LinkList *prototype;
};

struct Closure *Closure;
struct Object *Object;
struct Object *Symbol;
struct Object *Array;
struct Object *String;

/**
 ** *******************
 ** Functions for creating instances
 ** *******************
 */

struct LinkList *createLinkList(struct LinkList *current, void *value)
{
  struct LinkList *list = HLIB_MALLOC(struct LinkList);
  list->value = value;
  list->prev = current;
  return list;
}

struct Object *createPrimitive(char *name, void *value)
{
  struct Object *primitive = HLIB_MALLOC(struct Object);
  primitive->name = name;
  primitive->props.value = value;
  return primitive;
}

struct Object *createArray(char *name)
{
  struct Object *arr = HLIB_MALLOC(struct Object);
  arr->name = name;
  arr->type = array;
  arr->__proto__ = Array;
  struct LinkList *propsList = null;
  createLinkList(propsList, createPrimitive("length", HLIB_MALLOC(int)));
  createLinkList(propsList, createPrimitive(0, null));
  arr->props.list = propsList;
  return arr;
}

struct Object *createString(char *name)
{
  struct Object *str = HLIB_MALLOC(struct Object);
  str->name = name;
  str->type = string;
  str->__proto__ = String;
  struct LinkList *propsList = null;
  createLinkList(propsList, createPrimitive("length", HLIB_MALLOC(int)));
  createLinkList(propsList, createPrimitive(0, null));
  str->props.list = propsList;
  return str;
}

/**
 * Variables defined in a closure can be used anywhere in the closure after the definition of it.
 * @param mode == 0: Create a new closure
 * @param mode != 0: Destroy a closure
 * @return: Level of the current closure.
 */
long useClosure(char mode)
{
  if (mode)
  {
    struct Closure *newOne = HLIB_MALLOC(struct Closure);
    newOne->parent = Closure;
    newOne->vars = createArray((char *)(Closure->vars + 1));
    Closure->children = createLinkList(Closure->children, newOne);
    Closure = newOne;
  }
  else if (Closure->parent != null)
  {
    Closure = Closure->parent;
    do
    {
      /**
       * TODO: Garbage cleaning for closure variables.
       */
      // struct Closure *tmp = Closure->children->value;
      // tmp->vars->props.arr;
      free(Closure->children->value);
      Closure->children = Closure->children->prev;
    } while (Closure->children != null);
  }
  return (long)Closure->vars->name;
}

void useSymbol(void);

/**
 * Use object in C lang!
 */
#define useObject(varName)

/**
 * Get the value of object
 */
#define useValue(varName)

/**
 * Initialize the contents of the entire library.
 */
void useLib(void)
{
  /**
   * Init Closure
   */
  Closure = HLIB_MALLOC(struct Closure);
  Closure->vars = createArray((char *)0);

  /**
   * Init Object
   */
  Object = HLIB_MALLOC(struct Object);
  Object->name = "Object";
  Object->type = object;
  Object->prototype = null;

  /**
   * Init Symbol
   */
  Symbol = HLIB_MALLOC(struct Object);
  Symbol->name = "Symbol";
  Symbol->type = symbol;
  Symbol->prototype = HLIB_MALLOC(struct LinkList);
  Symbol->prototype->value = Object;

  /**
   * Init Array
   */
  Array = HLIB_MALLOC(struct Object);
  Array->name = "Array";
  Array->type = array;
  // Array->prototype = Object;

  /**
   * Init String
   */
  String = HLIB_MALLOC(struct Object);
  String->name = "String";
  String->type = string;
  // String->prototype = Object;

  /**
   * TODO remove test print
   */
  printf("%d\n", '\0' == 0 ? 1 : 0);
}

#endif /* __HLIB_TYPES */
