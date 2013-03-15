#include <stdio.h>
#include <vector>

/*
Given an array elements, Find the maximum number which can be formed by the array elements 
Eg input – a[ ] = {9,6,8,1] 
Output - 9861
*/
int main(int argc, char **argv)
{
  std::vector<int> a = { 9, 6, 8, 1 };

  std::sort(a.begin(), a.end(), [](int a, int b) -> bool {
    return a > b;
  });

  for (int i = 0; i < a.size(); ++i)
    printf("%d", a[i]);
  printf("\n");

  return 0;
}
