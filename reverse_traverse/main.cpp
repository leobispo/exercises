#include <stdio.h>

#include <stack>
#include <iostream>

/**
 The above code works fine 
e.g 
Enter the no. of elements in linked list(n) and the reverse shift(k) and travel shift(m) such that [2<=k,m<=n] 26 3 5 

Enter the elements : 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 

Output 
3 2 1 4 5 6 7 8 11 10 9 12 13 14 15 16 19 18 17 20 21 22 23 24 26 25

*/

struct my_list {
  int i;
  struct my_list *next;
};

static void
insert_on_list(struct my_list **head, struct my_list **tail, int i)
{
  struct my_list *node;
  if (!*head)
    *head = node = (struct my_list *) malloc(sizeof(struct my_list));
  else
    (*tail)->next = node = (struct my_list *) malloc(sizeof(struct my_list));

  *tail = node;
  node->next = NULL;
  node->i = i;
}

int
main(int argc, char **argv)
{
  struct my_list *head = NULL, *tail = NULL, *node;

  for (auto i = 1; i <= 26; ++i)
    insert_on_list(&head, &tail, i);

  size_t m = 3;
  size_t n = 5;
  node = head;

  auto i = m, j = n;

  std::stack<struct my_list *> stack;
  while (node) {
    if (!i && !j) {
      i = m;
      j = n;
    }

    if (i) {
      stack.push(node);
      if (!--i) {
        while (!stack.empty()) {
          std::cout << stack.top()->i << " ";
          stack.pop();
        }
      }
    }
    else {
      std::cout << node->i << " ";
      --j;
    }
    
    node = node->next;
  }

  while (!stack.empty()) {
    std::cout << stack.top()->i << " ";
    stack.pop();
  }

  std::cout << std::endl;

  return 0;
}
