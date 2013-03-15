#include <stdio.h>

#include <string.h>
#include <stdint.h>

/**
  Implement an algorithm to determine if a string has all unique characters What if 
  you can not use additional data structures?
*/

static bool
has_only_unique(const char * const str)
{
  uint32_t check = 0;
  for (size_t i = 0; i < strlen(str); ++i) {
    uint32_t letter = str[i] - 'a';
    if ((check & (1 << letter)) > 0)
      return false;

    check |= (1 << letter);
  }

  return true;
}

int main(int argc, char **argv)
{
  printf("%d\n", has_only_unique("abcdef"));
  printf("%d\n", has_only_unique("abcdefa"));

  return 0;
}
