#include "binarytree.h"

#include <fstream>
#include <vector>

int main(int argc, char **argv)
{
  std::function<int(const int &, const int &)> compare = [](const int &a, const int &b) -> int {
    return a - b;
  };

  BinaryTree<int> tree;
  tree.insert(10, compare);
  tree.insert(15, compare);
  tree.insert(13, compare);
  tree.insert(17, compare);
  tree.insert(16, compare);
  tree.insert(19, compare);
  tree.insert(9, compare);
  tree.insert(7, compare);
  tree.insert(3, compare);
  tree.insert(4, compare);
  tree.insert(24, compare);
  tree.insert(23, compare);
  tree.insert(26, compare);

  tree.levelOrder([](const int &value, const int &unbalanced) -> bool {
    printf("%d, %d\n", value, unbalanced);
    return true;
  });

  return 0;
}

