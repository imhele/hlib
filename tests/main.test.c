#include "./types.test.h"

int main()
{
  useLib();
  useClosure(1);

  testTypes();

  useClosure(0);
  return 0;
}
