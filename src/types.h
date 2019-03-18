#ifndef __HLIB_TYPES
#define __HLIB_TYPES
#include <stdio.h>
#include "./methods.h"
#include "./utils.h"

/**
 ** *******************
 **  Types definition
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
 * A value having the data type "symbol" can be referred to as a "symbol value".
 * A symbol value is created as an anonymous, unique value.
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

#define ARRAY_SPLIT_TYPE unsigned char
#define STRING_SPLIT_TYPE unsigned char

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
  struct LinkList *list = HLIB_CALLOC(struct LinkList);
  list->value = value;
  list->prev = current;
  return list;
}

struct Object *createPrimitive(char *name, void *value)
{
  struct Object *primitive = HLIB_CALLOC(struct Object);
  primitive->name = name;
  primitive->props.value = value;
  return primitive;
}

struct Object *createArray(char *name)
{
  struct Object *arr = HLIB_CALLOC(struct Object);
  arr->name = name;
  arr->type = array;
  arr->__proto__ = Array;
  struct LinkList *propsList;
  propsList = createLinkList(null, createPrimitive("length", HLIB_CALLOC(int)));
  propsList = createLinkList(propsList, createPrimitive(0, null));
  arr->props.list = propsList;
  return arr;
}

struct Object *createString(char *name)
{
  struct Object *str = HLIB_CALLOC(struct Object);
  str->name = name;
  str->type = string;
  str->__proto__ = String;
  struct LinkList *propsList;
  propsList = createLinkList(null, createPrimitive("length", HLIB_CALLOC(int)));
  propsList = createLinkList(propsList, createPrimitive(0, null));
  str->props.list = propsList;
  return str;
}

struct Object *createObject(char *name)
{
  struct Object *obj = HLIB_CALLOC(struct Object);
  obj->name = name;
  obj->type = object;
  obj->__proto__ = Object;
  obj->props.arr = createArray("props");
  return obj;
}

struct Object *createSymbol(char *name)
{
  struct Object *syb = HLIB_CALLOC(struct Object);
  syb->name = name;
  syb->type = symbol;
  syb->__proto__ = Symbol;
  syb->props.value = (void *)(long)syb;
  return syb;
}

#endif /* __HLIB_TYPES */
