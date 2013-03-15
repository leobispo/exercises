#include <vector>
#include <iostream>

/*
 Given a list of n gas station of form P(D,X) where D is the distance from this station to next station and X
 is the amount of petrol available at this station, identify the starting station from where you can complete
 journey to each station in order from 1.....N. You can only go in one direction i.e from P(i) to P(i+1) 
*/

int main(int argc, char **argv)
{
/*
  std::vector<std::pair<int, int>> P = {
    { 4, 3 }, 
    { 7, 5 },
    { 1, 6 },
    { 4, 3 },
    { 8, 8 },
    { 4, 3 },
  };
*/

/*
  std::vector<std::pair<int, int>> P = {
    { 20, 2 }, 
    {  3, 2 },
    {  3, 6 },
    {  3, 2 },
    {  3, 1 },
    {  4, 4 },
  };
*/

  std::vector<std::pair<int, int>> P = {
    { 1,  0 }, 
    { 1,  1 },
    { 1,  0 },
    { 9, 13 },
  };

  size_t count = P.size();
  std::pair<int, int> candidate(-1, -1);
  for (auto i = 0; i < (P.size() * 2) - 1; ++i) {
    if (i < P.size()) {
      if (P[i].first <= P[i].second && candidate.second < 0) {
        candidate = std::pair<int, int>(i, 0);
        count = P.size();
      }
    }

    if (candidate.second >= 0) {
      candidate.second += (P[i % P.size()].second - P[i % P.size()].first);
      --count;
    }

    if (!count) {
      std::cout << candidate.first <<std::endl;
      break;
    }
  }

  return 0;
}
