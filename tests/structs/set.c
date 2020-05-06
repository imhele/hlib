#include "../../main.h"

bool testSetCreate()
{
  int *test = HLIB_CALLOC(int);
  struct Set *set = SetCreate(test);
  bool flag = test == set->value;
  SetFree(&set);
  return flag;
}

bool testSetHas()
{
  struct Set *set = LinkListPush(SetCreate(NULL), (void *)1, ENDARG);

  bool flag = SetHas(set, (void *)1, DEFAULTARG) && !SetHas(set, (void *)3, DEFAULTARG);
  SetFree(&set);
  return flag;
}

bool testSetInsert()
{
  bool flag = true;
  struct Set *set = SetCreate(NULL);
  SetInsert(set, (void *)1, DEFAULTARG);

  flag = flag && SetHas(set, (void *)1, DEFAULTARG);
  flag = flag && !SetHas(set, (void *)3, DEFAULTARG);

  SetInsert(set, (void *)3, DEFAULTARG);
  flag = flag && SetHas(set, (void *)3, DEFAULTARG);
  SetFree(&set);
  return flag;
}

bool testSetRemove()
{
  bool flag = true;
  struct Set *set = SetCreate(NULL);
  SetInsert(set, (void *)1, DEFAULTARG);

  flag = flag && SetHas(set, (void *)1, DEFAULTARG);
  flag = flag && SetRemove(set, (void *)1, DEFAULTARG);
  flag = flag && !SetHas(set, (void *)1, DEFAULTARG);
  SetFree(&set);
  return flag;
}

bool testSetFree()
{
  struct Set *set = LinkListPush(SetCreate(NULL), (void *)1, ENDARG);
  SetFree(&set);
  return set == NULL;
}

int main()
{
  HLIB_ASSERT_TEST(testSetCreate);
  HLIB_ASSERT_TEST(testSetHas);
  HLIB_ASSERT_TEST(testSetInsert);
  HLIB_ASSERT_TEST(testSetRemove);
  HLIB_ASSERT_TEST(testSetFree);
  return 0;
}
