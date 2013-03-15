#include<stdio.h>

#include<vector>
#include<iostream>
#include<algorithm>

int main(int argc, char **argv)
{
  int capacity = 10;

  std::vector<std::pair<int, int>> elements = {
    { 20, 7 },
    { 10, 8 },
    {  5, 2 }
  };

  int  solution[elements.size() + 1][capacity + 1];
  bool keep[elements.size() + 1][capacity + 1];

  for (auto i = 0; i <= elements.size(); ++i) {
    keep[i][0] = 0;
    solution[i][0] = 0;
  }

  for (auto i = 0; i <= capacity; ++i) {
    keep[0][i] = 0;
    solution[0][i] = 0;
  }

  for (auto i = 1; i <= elements.size(); ++i) {
    for (auto j = 1; j <= capacity; ++j) {
      keep[i][j] = false;
      if (elements[i - 1].second <= j) {
        int toCheck   = solution[i - 1][j];
        int remaining = j - elements[i - 1].second;
        int w = elements[i - 1].first + solution[i - 1][remaining];
        solution[i][j] = std::max(toCheck, w);
    
        if (toCheck < w)
          keep[i][j] = true;
      }
      else
        solution[i][j] = solution[i - 1][j];
    }
  }

  std::vector<int> result;
  auto j = capacity;
  for (auto i = (int) elements.size(); i > 0 && j > 0; --i) {
    if (keep[i][j]) {
      result.push_back(i - 1);
      j -= elements[i - 1].second;
    }
  }

  for (auto i = 1; i <= elements.size(); ++i) {
    for (auto j = 1; j <= capacity; ++j) {
      std::cout << keep[i][j] << " ";
    }
    std::cout << std::endl;
  }
  for (auto &i : result)
    std::cout << i << std::endl;

  return 0;
}
