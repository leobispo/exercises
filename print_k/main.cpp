#include <stdio.h>
#include <stdbool.h>

bool
print_k(int *arr1, size_t size1, int *arr2, size_t size2, size_t k, int *result)
{
  if (!arr1 || !arr2 || !result || size1 + size2 < k)
    return false;

  int i = 0;
  int j = size2 - 1;
  while (k--) {
    if (i < size1 && (j < 0 || arr1[i] > arr2[j]))
      *result = arr1[i++];
    else
      *result = arr2[j--];
  }

  return true;
}

int
main(int argc, char **argv)
{
  int array2[] = { 1, 2, 3, 4, 5 };
  int array1[] = { 7, 6 };

  int result;

  print_k(array1, sizeof(array1) / sizeof(int), array2, sizeof(array2) / sizeof(int), 6, &result);

  printf("%d\n", result);

  return 0;
};
