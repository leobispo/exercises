#include <stdio.h>

#include<string>
#include<iostream>
/**
 You are given two Strings lets say "S" which consist Upper Case albhabets and '?' character only and p. You are required to replace '?' with some alphabet so that resulting string have maximum number of "p" in it. You can replace '?' with any alphabet. 
2. Replace '?' such that it should be lexicographically sorted. 
Example 
S="ABAAMA????MAZON????????" 
p="AMAZON" 
The final string S = "ABAAMAZONAMAZONAAAMAZON" 

S="?????" 
p="ABCD" 
Final Result="AABCD" 
*/

int main(int argc, char ** argv)
{
  std::string S = "ABAAMA????MAZON????????";
  std::string p = "AMAZON";

  int rollbackBegin = -1;
  int rollbackEnd   = 0;
  int j = p.size() - 1;
  for (int i = S.size() - 1; i >= 0; --i) {

    if (S[i] == p[j])
      --j;
    else if (S[i] == '?') {
      if (rollbackBegin == -1)
        rollbackBegin = rollbackEnd = i;

      --rollbackEnd;

      S[i] = p[j];
      --j;
    }
    else {
      if (rollbackBegin >= 0) {
        for (auto k = rollbackBegin; k > rollbackEnd; --k)
          S[k] = p[0];
      }

      rollbackBegin = -1;
      j = p.size() - ((S[i] == p[j]) ? 1 : 2);
    }

    if (j < 0) {
      j = p.size() - 1;
      rollbackBegin = -1;
    }
  }

  for (auto k = rollbackBegin; k > rollbackEnd; --k)
    S[k] = p[0];

  std::cout << S << std::endl;
  return 0;
}
