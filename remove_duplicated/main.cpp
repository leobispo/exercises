#include <stdio.h>
#include <string.h>

/*
Design an algorithm and write code to remove the duplicate characters in a string 
without using any additional buffer NOTE: One or two additional variables are fine 
An extra copy of the array is not 
*/

static void
remove_duplicated(char *str)
{
  int tail = 1;
  for (int i = 1; i < strlen(str); ++i) {
    int j;
    for (j = 0; j < tail; ++j) {
      if (str[i] == str[j])
        break;
    }

    if (j == tail)
      str[tail++] = str[i];
  }

  str[tail] = 0;
}

int
main(int argc, char **argv)
{
  char str[] = "aabac";

  remove_duplicated(str);
  printf("%s\n", str);

  return 0;
}
