#include<stdio.h>

#include<vector>
#include<iostream>
#include<algorithm>

int main(int argc, char **argv)
{
  std::string str1 = "leo bispo oliveira";
  std::string str2 = "dani yumi sunaga oliveira";

  int solution[str1.size() + 1][str2.size() + 1];

  for (auto i = 0; i <= str1.size(); ++i)
    for (auto j = 0; j <= str2.size(); ++j)
      solution[i][j] = 0;


  std::string result = "";
  int longest = 0;
  for (auto i = 0; i < str1.size(); ++i) {
    for (auto j = 0; j < str2.size(); ++j) {
      if (str1[i] == str2[j]) {
        solution[i + 1][j + 1] = solution[i][j] + 1;
        
        if (longest < solution[i + 1][j + 1]) {
          result = "";
          longest = solution[i + 1][j + 1];
          auto k = longest;
          while (k) {
            result += str2[j - (--k)];
          }
        }
      }
    }
  }

  std::cout << result << std::endl;

  return 0;
}
