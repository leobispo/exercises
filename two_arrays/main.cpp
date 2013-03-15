#include <stdio.h>
#include <stdlib.h>

#include <string.h>

static int
compare_reverse(const void *a, const void *b)
{
  return *(int *) b - *(int *) a;
}

int
main(int argc, char **argv)
{
  int array[] = { 2, 5, 3, 7, 9, 6, 3, 3 };

  struct Answer {
    int sum;
    size_t currPos;
    int array[4];
  } answer[2];

  memset(answer, 0, sizeof(answer));
  size_t len = sizeof(array) / sizeof(int);

  qsort(array, len, sizeof(int), compare_reverse);

  for (size_t i = 0; i < len; ++i) {
    size_t idx = (answer[0].currPos == 4 || (answer[0].currPos < 4 && answer[1].sum + array[i] < answer[0].sum + array[i]));
    answer[idx].array[answer[idx].currPos++] = array[i];
    answer[idx].sum += array[i];
  }

  for (size_t idx = 0; idx < 2; ++idx) {
    for (size_t i = 0; i < 4; ++i)
      printf("%d ", answer[idx].array[i]);
    printf(" - %d\n", answer[idx].sum);
  }

  return 0;
}
