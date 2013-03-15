#include <stdio.h>

#include<vector>
#include<iostream>
/*
Write a function, that given a list of integers and an integer s, prints any 2 numbers in the list that sum to s. 

 1, 2, 3, 4, 5 sum = 6 could print: 
 1 + 5 = 6 
 2 + 4 = 6 
 4 + 2 = 6 
 5 + 1 = 6
 */

int main(int argc, char **argv)
{
  std::vector<int> array = { 1, 2, 3, 4, 5 };

  int sum = 6;
  for (auto i = 0; i < array.size(); ++i) {
    for (auto j = i; j < array.size(); ++j) {
      if (i == j) continue;
      if ((array[i] + array[j]) == sum) {
        std::cout << array[i] << " + " << array[j] << " = " << 6 << std::endl;
        std::cout << array[j] << " + " << array[i] << " = " << 6 << std::endl;
      }
    }
  }
  return 0;
}
