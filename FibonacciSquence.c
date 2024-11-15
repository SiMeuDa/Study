#include <stdio.h>
#define MAX 90

int main(void)
{
  int n, n1 = 0, n2 = 1, n3 = 0;

  scanf("%d", &n);
  if(n > MAX || n < 0)
  {
    printf("Try, Again.\n");  
    return 0;
  }
  if(n !=0)
  {
    for(int i = 1; i < n; i++)
    { 
      if(i != 1)
      { 
        n1 = n2;
        n2 = n3;
      }
      n3 = n1 + n2;
    }
  }
  else
  { 
    n3 = 0;
  }
  printf("%d\n", n3);

  return 0;
}
