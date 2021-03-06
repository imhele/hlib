#ifndef __HLIB_STRUCTS_CLOSURE
#define __HLIB_STRUCTS_CLOSURE

#include "../structs/map.h"

struct LinkList *__CLOSURE_VARIABLE_MAPS = NULL;

#define CLOSURE \
  ({             \
    __CLOSURE_VARIABLE_MAPS = LinkListUnshift(__CLOSURE_VARIABLE_MAPS, MapCreate(NULL), ENDARG);

#define ENDCLOSURE                                                               \
  MapFree((struct Map **)&(__CLOSURE_VARIABLE_MAPS->value));                     \
  struct LinkList *__CLOSURE_VARIABLE_NEXT_MAPS = __CLOSURE_VARIABLE_MAPS->next; \
  free(__CLOSURE_VARIABLE_MAPS);                                                 \
  __CLOSURE_VARIABLE_MAPS = __CLOSURE_VARIABLE_NEXT_MAPS;                        \
  })

#define useClosure(variable) \
  (MapSet(__CLOSURE_VARIABLE_MAPS->value, #variable, &variable, MapIsStringKeyEqual))

#define useSpecClosure(name, variable) \
  (MapSet(__CLOSURE_VARIABLE_MAPS->value, name, variable, MapIsStringKeyEqual))

#define useClosureValue(variable)                                                             \
  ({                                                                                          \
    struct MapItem *__CLOSURE_VARIABLE_MAP_ITEM = NULL;                                       \
    struct LinkList *__CLOSURE_VARIABLE_UPPER_LEVEL_MAP = __CLOSURE_VARIABLE_MAPS;            \
    for (; __CLOSURE_VARIABLE_MAP_ITEM == NULL && __CLOSURE_VARIABLE_UPPER_LEVEL_MAP != NULL; \
         __CLOSURE_VARIABLE_UPPER_LEVEL_MAP = __CLOSURE_VARIABLE_UPPER_LEVEL_MAP->next)       \
      __CLOSURE_VARIABLE_MAP_ITEM = MapGet(                                                   \
          __CLOSURE_VARIABLE_UPPER_LEVEL_MAP->value, #variable, MapIsStringKeyEqual);         \
    if (__CLOSURE_VARIABLE_MAP_ITEM != NULL)                                                  \
      variable = *((typeof(&variable))__CLOSURE_VARIABLE_MAP_ITEM->value);                    \
  })

#define useSpecClosureValue(name, variable)                                                   \
  ({                                                                                          \
    struct MapItem *__CLOSURE_VARIABLE_MAP_ITEM = NULL;                                       \
    struct LinkList *__CLOSURE_VARIABLE_UPPER_LEVEL_MAP = __CLOSURE_VARIABLE_MAPS;            \
    for (; __CLOSURE_VARIABLE_MAP_ITEM == NULL && __CLOSURE_VARIABLE_UPPER_LEVEL_MAP != NULL; \
         __CLOSURE_VARIABLE_UPPER_LEVEL_MAP = __CLOSURE_VARIABLE_UPPER_LEVEL_MAP->next)       \
      __CLOSURE_VARIABLE_MAP_ITEM = MapGet(                                                   \
          __CLOSURE_VARIABLE_UPPER_LEVEL_MAP->value, name, MapIsStringKeyEqual);              \
    if (__CLOSURE_VARIABLE_MAP_ITEM != NULL)                                                  \
      variable = (typeof(variable))__CLOSURE_VARIABLE_MAP_ITEM->value;                        \
  })

#endif /* __HLIB_STRUCTS_CLOSURE */
