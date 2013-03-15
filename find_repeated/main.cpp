#include <iostream>
#include <string>
#include <unordered_map>

/**
 * Given a String "abcxrrxabcrr" 
 * Find the first repeated string with minimum 3 character? 
 *
 * Answer is "abc" min 3 characters. 
 *
 */
int main(int argc, char **argv)
{
  std::string str = "abcxrrxabcrr";

  std::unordered_map<std::string, bool> map;
  for (auto i = 0; i < str.size() - 2; ++i) {
    std::string sub = str.substr(i, 3);
    auto it = map.find(sub);
    if (it != map.end()) {
      std::cout << sub << std::endl;
      break;
    }
    map.insert(std::pair<std::string, bool>(sub, true));
  }

  return 0;
};
