#include <stdio.h>
int main()
{
  int k;           // объявляем целую переменную k
  printf("k= ");   // выводим сообщение
  scanf("%d", &k); // вводим переменную k
  if (k >= 5)      // если k>5
    printf("%d >= 5", k); // выводим "ЗНАЧЕНИЕ >= 5"
  else             // иначе
    printf("%d < 5", k);  // выводим "ЗНАЧЕНИЕ < 5"
  getchar(); getchar();
  return 0;
}
