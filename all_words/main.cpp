#include <stdio.h>
#include <ctype.h>

#include <stack>
#include <string>
#include <unordered_map>
#include <functional>
#include <iostream>

class Trie
{
  public:
    struct Node;
    void insert(const std::string &str)
    {
      Node *node = &m_root;
      for (auto &ch : str) {
        char c = (char) tolower(ch);
        auto it = node->m_children.find(c);
        if (it == node->m_children.end())
          it = node->m_children.insert(std::pair<char, Node *>(c, new Node())).first;

        node = it->second;
      }

      node->m_terminate = true;
      node->m_str       = str;
    }

    const Node *checkNode(const Node *node, char ch) {
      if (!node)
        return NULL;
      for (auto &n : node->m_children) {
        if (n.first == ch)
          return n.second;
      }

      return NULL;
    }

    struct Node
    {
      Node()
      {
      }

      bool m_terminate = false;
      std::string m_str;

      std::unordered_map<char, Node *> m_children;
    };

    Node m_root;
};

int main(int argc, char **argv)
{
  Trie trie;
  trie.insert("god");
  trie.insert("goat");
  trie.insert("godbody");
  trie.insert("amour");
  trie.insert("teste");

  enum Paths { TOP = 0x1, BOTTOM = 0x2, LEFT = 0x4, RIGHT = 0x8 };

  size_t height = 3;
  size_t width  = 7;

  char board[3][7] = {
    { 'g', 'o', 'd', 'b', 'o', 'd', 'y' },
    { 't', 'a', 'm', 'o', 't', 'e', 'e' }, 
    { 'u', 'i', 'r', 'u', 's', 's', 't' }
  };

  struct visit {
    int     i;
    int     j;
    uint8_t paths;
    const Trie::Node *trieNode;
  };

  struct myElements{
    Paths   type;
    int     moveI;
    int     moveJ;
    uint8_t paths;
  } elements[] = {
    {TOP   , -1,  0, TOP    | LEFT   | RIGHT },
    {BOTTOM,  1,  0, BOTTOM | LEFT   | RIGHT },
    {LEFT  ,  0, -1, TOP    | BOTTOM | LEFT  },
    {RIGHT ,  0,  1, TOP    | BOTTOM | RIGHT }
  };

  std::stack<struct visit> backlog;
  for (auto i = 0; i < height; ++i) {
    for (auto j = 0; j < width; ++j) {
      const Trie::Node *node = trie.checkNode(&trie.m_root, board[i][j]);

      if (!node)
        continue;

      struct visit v = { i, j, (TOP | BOTTOM | LEFT | RIGHT), node };
      backlog.push(v);
 
      while (!backlog.empty()) {
        bool moved = false;
        for (auto k = 0; k < (sizeof(elements) / sizeof(myElements)); ++k) {
          if (backlog.top().paths & elements[k].type) {
            backlog.top().paths &= ~elements[k].type;

            auto newI = backlog.top().i + elements[k].moveI;
            auto newJ = backlog.top().j + elements[k].moveJ;

            node = trie.checkNode(backlog.top().trieNode, board[newI][newJ]);

            if (!node)
              continue;

            if (newI >= 0 && newI < height && newJ >= 0 && newJ < width) {
              struct visit v = { newI, newJ, elements[k].paths, node };
              moved = true;
              if (node->m_terminate)
                std::cout << "FOUND " << node->m_str << std::endl;
   
              backlog.push(v);
              break;
            }
          }
        }

        if (!moved)
          backlog.pop();
      }
    }
  }

  return 0;
}
