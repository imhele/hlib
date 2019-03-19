#include "../main.h"
#include "./types.test.h"
#include "./methods.test.h"

int main()
{
  useLib();
  useClosure(1);

  testTypes();
  testMethods();

  useClosure(0);
  return 0;
}
