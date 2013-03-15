#include <stdio.h>

#include <stack>
#include <iostream>

#define SWAP(a, b) do {\
  if (a != b) {\
    a = a ^ b; \
    b = a ^ b; \
    a = a ^ b; \
  }\
} while (0)

void quicksort(int *array, size_t size)
{
  srand(time(NULL));
  if (!size)
    return;

  std::stack<std::pair<int, int>> stack;
  stack.push(std::pair<int, int>(0, size - 1));

  while (!stack.empty()) {
    std::pair<int, int> range = stack.top();
    stack.pop();

    if (range.second <= range.first)
      continue;

    size_t pivot = (range.first + (rand() % (range.second - range.first + 1)));

    auto left  = range.first;
    auto right = range.second;

    while (left <= right) {
      while (array[left] < array[pivot]) ++left;
      while (array[right] > array[pivot]) --right;
      if (left <= right) {
        SWAP(array[left], array[right]);
        ++left;
        --right;
      }
    }

    stack.push(std::pair<int, int>(range.first, left - 1));
    stack.push(std::pair<int, int>(left, range.second));
  }
}

int main(int argc, char **argv)
{
  int array[] = { 1, 12, 5, 26, 7, 14, 3, 7, 2, 9, 12, 17, 56 };

  for (auto i = 0; i < sizeof(array) / sizeof(int); ++i)
    std::cout << array[i] << " ";
  std::cout << std::endl;

  quicksort(array, sizeof(array) / sizeof(int));

  for (auto i = 0; i < sizeof(array) / sizeof(int); ++i)
    std::cout << array[i] << " ";
  std::cout << std::endl;

  return 0;
};
