#include <stdio.h>

#include <stdint.h>
#include <string.h>

#include <vector>
#include <iostream>

#include<stack>

class Maze
{
  enum Direction { NORTH = 0x1, SOUTH = 0x2, EAST = 0x4, WEST = 0x8 };

  public:
    Maze(size_t width, size_t height) : m_width(width), m_height(height)
    {
      m_maze = new uint8_t*[height];
      for (auto i = 0; i < height; ++i) {
        m_maze[i] = new uint8_t[width];
        memset(m_maze[i], (NORTH | SOUTH | EAST | WEST), width);
      }
    }

    void create()
    {
      std::stack<std::pair<int, int>> backtrack;
      
      struct Paths {
        Direction direction;
        Direction opposite;
        int moveI;
        int moveJ;
      };

      std::vector<Paths> paths = {
        { NORTH, SOUTH, -1,  0 },
        { SOUTH, NORTH,  1,  0 },
        { EAST , WEST ,  0,  1 },
        { WEST , EAST ,  0, -1 }
      };

      srand(time(NULL));

      size_t visited = (m_width * m_height) - 1;
      std::pair<int, int> node(rand() % m_height, rand() % m_width);

      backtrack.push(node);

      while (visited) {
        bool found = false;

        std::random_shuffle(paths.begin(), paths.end());
        for (auto i = 0; i < paths.size(); ++i) {
          auto newI = node.first  + paths[i].moveI;
          auto newJ = node.second + paths[i].moveJ;

          if (newI >= 0 && newI < m_height && newJ >= 0 && newJ < m_width) {
            if (m_maze[newI][newJ] == (NORTH | SOUTH | EAST | WEST)) {
              m_maze[node.first][node.second] &= ~paths[i].direction;

              node = std::pair<int, int>(newI, newJ);

              m_maze[node.first][node.second] &= ~paths[i].opposite;

              --visited;
              backtrack.push(node);
              found = true;
              break;
            }
          }
        }

        if (!found) {
          node = backtrack.top();
          backtrack.pop();
        }
      }
    }

    void print()
    {
      std::cout << "+";
      for (auto i = 0; i < m_width; ++i) {
        std::cout << "+";
        std::cout << "--";
        std::cout << "+";
      }

      std::cout << "+";
      std::cout << std::endl;

      for (auto i = 0; i < m_width; ++i) {
        std::cout << "+";
        for (auto j = 0; j < m_height; ++j) {
          std::cout << "+";

          if (m_maze[i][j] & NORTH)
            std::cout << "--";
          else
            std::cout << "  ";

          std::cout << "+";
        }

        std::cout << "+";
        std::cout << std::endl;
        std::cout << "|";
        for (int j = 0; j < m_height; ++j) {
          if (m_maze[i][j] & WEST)
            std::cout << "|";
          else
            std::cout << " ";

            std::cout << "  ";

          if (m_maze[i][j] & EAST)
            std::cout << "|";
          else
            std::cout << " ";
        }

        std::cout << "|";
        std::cout << std::endl;
        std::cout << "+";
        for (int j = 0; j < m_height; ++j) {
          std::cout << "+";

          if (m_maze[i][j] & SOUTH)
            std::cout << "--";
          else
            std::cout << "  ";

          std::cout << "+";
        }

        std::cout << "+";
        std::cout << std::endl;
      }

      std::cout << "+";
      for (auto i = 0; i < m_width; ++i) {
        std::cout << "+";
        std::cout << "--";
        std::cout << "+";
      }

      std::cout << "+";
      std::cout << std::endl;
    }     

  private:
    uint8_t **m_maze;

    size_t m_width;
    size_t m_height;


};

int main(int argc, char **argv)
{
  Maze maze(20, 20);

  maze.create();
  maze.print();

  return 0;
}
