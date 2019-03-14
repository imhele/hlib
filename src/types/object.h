#ifndef __HLIB_OBJECT
#define __HLIB_OBJECT

/**
 * Basic object type
 */
typedef struct Object
{
  Object *prototype;
} Object;

typedef struct ObjectInstance
{
  Object *__proto__;
  ObjectInstance (*valueOf)(void);
} ObjectInstance;

int main()
{
  ObjectInstance *p;
  p->valueOf = valueOf;
}

ObjectInstance *valueOf(void)
{
  ObjectInstance *p;
  return p;
}

#endif
