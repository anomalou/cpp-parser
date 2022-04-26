#include <stdio.h>
int main()
{
  int k = 5 + 1;
  printf("k= ", k);  
  scanf("%d", &k); 
  if (k >= 5) 
    printf("%d >= 5", k);
  else
    printf("%d < 5", k);
  printf("1", k);
  return 0;
}
