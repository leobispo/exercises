#include <stdio.h>
#include <string>
#include <iostream>
#include <algorithm>

/**
  - A B C B D A B
- 0 0 0 0 0 0 0 0
B 0 0 1 1 1 1 1 1
D 0 0 1 1 1 2 2 2
C 0 0 1 2 2 2 2 2
A 0 1 1 2 2 2 3 3 
B 0 1 2 2 3 3 3 4
A 0 1 2 2 3 3 4 4
*/

int main(int argc, char **argv)
{
  std::string str2 = "ABLAECO";
  std::string str1 = "LEOACOD";

  size_t solution[str1.size() + 1][str2.size() + 1];

  for (auto i = 0; i <= str1.size(); ++i)
    solution[i][0] = 0;

  for (auto j = 0; j <= str2.size(); ++j)
    solution[0][j] = 0;

  for (auto j = 1; j <= str2.size(); ++j) {
    for (auto i = 1; i <= str1.size(); ++i) {
      if (str1[i - 1] == str2[j - 1])
        solution[i][j] = solution[i - 1][j - 1] + 1;
     else
        solution[i][j] = std::max(solution[i - 1][j], solution[i][j - 1]);
    }
  }

  std::string result;
  auto i = str1.size();
  auto j = str2.size();

  auto lcs = solution[i][j]; 
  while (lcs) {
    if (solution[i - 1][j] != lcs && solution[i][j - 1] != lcs) {
      --i;
      --j;
      lcs = solution[i][j];
      std::string ch;
      ch += str1[i];
      result.insert(0, ch);
    }
    else if (solution[i - 1][j] == lcs)
      --i;
    else
      --j;
  }

  std::cout << result << std::endl;
  return 0;
}
