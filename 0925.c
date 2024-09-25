#include <stdio.h>

#include <limits.h>

LeeO1(void)
{
  printf("char min : %d, Max : %d", CHAR_MIN, CHAR_MAX);
  printf("short min : %d, Max : %d", SHRT_MIN, SHRT_MAX);
  printf("int min : %d, Max : %d", INT_MIN, INT_MAX);
  printf("long mon : %d, Max : %d", LONG_MIN, LONG_MAX);

  return 0;
}

int main(void)
{
  LeeO1();

  return 0;
}
