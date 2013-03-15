#include <string>
#include <iostream>
#include <functional>
/**
Print all combination of given length k possible with characters available in a given string "S" with repetition in new lines. 
Example 
S="abc" 
k=2 
output: 
aa 
ab 
ac 
ba 
bb 
bc 
ca 
cb 
cc
*/

int main(int argc, char **argv)
{
  std::string S = "abcd";
  size_t k = 3;
  char result[k + 1];
  result[k] = 0;

  std::function<void(size_t, size_t, char *)> f;
  f = [&S, &f](size_t idx, size_t k, char *result) -> void {
    for (auto &ch : S) {
      result[idx] = ch;
      if (!k)
        std::cout << result << std::endl;
      else
        f(idx + 1, k - 1, result);
    }
  };

  f(0, k - 1, result);
  return 0;
}
