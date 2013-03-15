#include <stdio.h>

int fibo(int n)
{
  if (n < 2)
    return n;

  int x = fibo(n - 1);
  int y = fibo(n - 2);
  return (x + y);
}

int main(int argc, char **argv)
{
  printf("%d\n", fibo(11));
  return 0;
}
