#include <stdio.h>

template<int size_m>
void rotate_90(int matrix[][size_m], size_t n)
{
  for (int layer = 0; layer < n / 2; ++layer) {
    int first = layer;
    int last  = n - 1 - layer;
    for (int i = first; i < last; ++i) {
      int offset = i - first;

      int tmp = matrix[first][i];

      // [top, left]
      matrix[first][i] = matrix[last - offset][first];

      // [bottom, left]
      matrix[last - offset][first] = matrix[last][last - offset];

      // [bottom, right]
      matrix[last][last - offset] = matrix[i][last];

      // [top, right]
      matrix[i][last] = tmp;
    }
  }
}

int
main(int argc, char **argv)
{
  int matrix[][4] = {
    {  1,  2,  3,  4 }, // 13  9 5 1
    {  5,  6,  7,  8 }, // 14 10 6 2
    {  9, 10, 11, 12 }, // 15 11 7 3
    { 13, 14, 15, 16 }  // 16 12 8 4
  };

  rotate_90(matrix, 4);

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }

  return 0;
};
