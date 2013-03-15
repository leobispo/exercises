#include <stdio.h>

#include<cmath>
#include<vector>
#include<iostream>

void
insertHeap(std::vector<int> *maxHeap, int value)
{
  maxHeap->push_back(value);

  auto element = maxHeap->size();

  while (element > 0) {
    auto parent = std::floor((element - 1) / 2);
    if ((*maxHeap)[parent] < (*maxHeap)[element]) {
      auto right = 2 * parent + 1;
      auto left  = 2 * parent + 2;
      if ((*maxHeap)[left] > (*maxHeap)[right]) {
        auto tmp = (*maxHeap)[left];
        (*maxHeap)[left] = (*maxHeap)[parent];
        (*maxHeap)[parent] = tmp;
      }
      else {
        auto tmp = (*maxHeap)[right];
        (*maxHeap)[right] = (*maxHeap)[parent];
        (*maxHeap)[parent] = tmp;
      }
    }
    else
      parent = 0;

    element = parent;
  }
}



int main(int argc, char **argv)
{
  std::vector<int> maxHeap;

  insertHeap(&maxHeap,  9);
  insertHeap(&maxHeap,  5);
  insertHeap(&maxHeap,  7);
  insertHeap(&maxHeap,  2);
  insertHeap(&maxHeap, 30);

  for (auto &i : maxHeap)
    std::cout << i << std::endl;

  return 0;
}
