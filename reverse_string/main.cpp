#include <stdio.h>
#include <string.h>

#include <stdint.h>

/*
Write code to reverse a C-Style String (C-String means that “abcd” is represented as 
five characters, including the null character )
*/

void
reverse_string(char *str)
{
  if (!str)
    return;

  char *begin = str;
  char *end   = begin + (strlen(str) - 1);

  char tmp;
  while (begin < end) {
    tmp      = *begin; 
    *begin++ = *end;
    *end--   = tmp;
  }
}



int
main(int argc, char **argv)
{
  char str[] = "leonardo";


  reverse_string(str);
  printf("%s\n", str);
  return 0;
}
