#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class BinaryCode
{
public:
vector<string> decode(string message)
{
  vector<string> answer;
  string Q = message;

  if (Q.empty())
    return vector<string>( { "NONE", "NONE" } );
  vector<int> P;

  for (int p0 = 0; p0 <= 1; ++p0) {
    P = vector<int>(Q.size());
    P[0] = p0;
    P[1] = (Q[0] - '0') - P[0];
    bool none = false;
    if (P[1] < 0 || P[1] > 1)
      none = true;

    int i;
    for (i = 2; i < Q.size(); ++i) {
      P[i] = (Q[i - 1] - '0') - P[i - 2] - P[i - 1];
      if (P[i] < 0 || P[i] > 1) {
        none = true;
        break;
      }
    }

    if (P[P.size() - 2] == 1 && Q[P.size() - 1] == '0')
      none = true;

    if (!none) {
      string str;
      for (int i = 0; i < P.size(); ++i)
        str += std::to_string(P[i]);
      answer.push_back(str);
    }
    else
      answer.push_back("NONE");
  }

  return answer;
}
};

int main(int argc, char **argv)
{
  vector<string> samples = {
    "123210122",
    "11",
    "22111",
    "123210120",
    "3",
    "12221112222221112221111111112221111",
    ""
  };
  
  for (&s : samples) {
    vector<string> ret = decode(s);
    for (auto &r : ret)
      std::cout << r <<std::endl;
  }
  return 0;

}

