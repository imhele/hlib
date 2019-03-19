#ifndef __HLIB_USE
#define __HLIB_USE
#include "./colors.h"
#include "./types.h"

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
    struct Closure *newOne = HLIB_CALLOC(struct Closure);
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

void *__useProp(struct Object *obj, char *prop)
{
  if (!prop)
    console(ConsoleTypeError, "TypeError: Name of a property cannot be null", null);
  else if (!obj)
    console(ConsoleTypeError, "TypeError: Cannot read property '", prop, "' of null", null);
  else if (obj->type == object)
  {
  }
  else if (obj->type == array)
  {
  }
  else if (obj->type == string)
  {
  }
  /* primitive */
  else if (obj->type == null)
  {
  }
  return null;
}

/**
 * Use object in C lang!
 */
#define useObject(varName) (ArrayPush(Closure->vars, createObject(#varName)))

/**
 * TODO use*
 * Get the value of object
 */
#define useValue(varName)

#define useContext(varName)

/**
 * @param onCatch: A function that will be calling after catching an exception.
 * @param onCatch == NOOP: Do nothing after catching.
 * @param onCatch == null: End the try statement.
 */
#define useTry(onCatch)

#define useThrow(varName)

/**
 * Initialize the contents of the entire library.
 */
void useLib(void)
{
  /**
   * Init Closure
   */
  Closure = HLIB_CALLOC(struct Closure);
  Closure->vars = createArray((char *)0);

  /**
   * Init Object
   */
  Object = HLIB_CALLOC(struct Object);
  Object->name = "Object";
  Object->type = object;

  /**
   * Init Symbol
   */
  Symbol = HLIB_CALLOC(struct Object);
  Symbol->name = "Symbol";
  Symbol->type = object;
  Symbol->prototype = createLinkList(null, Object);

  /**
   * Init Array
   */
  Array = HLIB_CALLOC(struct Object);
  Array->name = "Array";
  Array->type = object;
  Array->prototype = createLinkList(null, Object);

  /**
   * Init String
   */
  String = HLIB_CALLOC(struct Object);
  String->name = "String";
  String->type = object;
  String->prototype = createLinkList(null, Object);
}

#endif /* __HLIB_USE */
