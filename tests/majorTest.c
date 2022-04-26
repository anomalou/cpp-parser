#include <stdio.h>
int main()
{
  int k; 
  printf("k= ");  
  scanf("%d", &k); 
  if (k >= 5) 
    printf("%d >= 5", k);
  else
    printf("%d < 5", k);
  return 0;
}
