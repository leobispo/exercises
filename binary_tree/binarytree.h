#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <stdio.h>

#include <iostream>
#include <functional>

#include <vector>

#include <stack>

#include "queue.h"
#include "stack.h"

template<class T>
class BinaryTree;

template<typename T>
std::ostream &operator<<(std::ostream &in, const BinaryTree<T> &obj);

template<typename T>
std::istream &operator>>(std::istream &in, BinaryTree<T> &obj);

template<class T>
class BinaryTree
{
  friend std::ostream &operator<< <>(std::ostream &in, const BinaryTree<T> &obj);
  friend std::istream &operator>> <>(std::istream &in, BinaryTree<T> &obj);
  private:
    const static int SERIAL_ID = 12345;

    enum Children { LEFT = 0x1, RIGHT = 0x2 };

    struct Node;
  public:
    virtual ~BinaryTree()
    {
      std::function<void(Node *)> f;
      f = [&](Node *node) {
        if (!node)
          return;

        f(node->m_left);
        f(node->m_right);

        delete node;
      };

      f(m_root);
    }

    void insert(T t, std::function<int(const T &, const T &)> compare)
    {
      if (!m_root)
        m_root = new Node(t);
      else {
        Node *currentElement = m_root;
        while (currentElement) {
          int leftOrRight = compare(t, currentElement->m_data);
          Node *parent    = currentElement;
          if (leftOrRight > 0) {
            currentElement = parent->m_right;
            if (!currentElement) {
              parent->m_right = new Node(parent, t);
              rebalance(parent->m_right);
            }
          }
          else {
            currentElement = parent->m_left;
            if (!currentElement) {
              parent->m_left = new Node(parent, t);
              rebalance(parent->m_left);
            }
          }
        }
      }
    }

    void inOrder(std::function<bool(const T &)> callback)
    {
      Node *node = m_root;
      Stack<Node *> stack;
      while (!stack.isEmpty() || node) {
        if (node) {
          stack.push(node);
          node = node->m_left;
        }
        else {
          stack.pop(node);

          if (!callback(node->m_data))
            return;

          node = node->m_right;
        }
      }
    }

    void reverseInOrder(std::function<bool(const T &)> callback)
    {
      Node *node = m_root;
      Stack<Node *> stack;
      while (!stack.isEmpty() || node) {
        if (node) {
          stack.push(node);
          node = node->m_right;
        }
        else {
          stack.pop(node);
          if (!callback(node->m_data))
            return;

          node = node->m_left; 
        }
      }
    }

    void postOrder(std::function<bool(const T &)> callback)
    {
      if (!m_root)
        return;

      Stack<Node *> stack;
      Node *node, *prevNode = NULL;

      stack.push(m_root);
      while (stack.peek(node)) {
        if (!prevNode || prevNode->m_left == node || prevNode->m_right == node) {
          if (node->m_left)
            stack.push(node->m_left);
          else if (node->m_right)
            stack.push(node->m_right);
        }
        else if (node->m_left == prevNode) {
          if (node->m_right)
            stack.push(node->m_right);
        }
        else {
          if (!callback(node->m_data))
            return;

          stack.pop(node);
        }

        prevNode = node;
      }
    }

    void preOrder(std::function<bool(const T &)> callback)
    {
      Node *node = m_root;

      Stack<Node *> stack;
      while (!stack.isEmpty() || node) {
        if (node) {
          if (!callback(node->m_data))
            return;

          stack.push(node);
          node = node->m_left;
        }
        else {
          stack.pop(node);
          node = node->m_right;
        }
      }
   }

    void levelOrder(std::function<bool(const T &, const T &)> callback)
    {
      Queue<Node *> q;    
      q.enqueue(m_root);

      Node *node;
      while (q.dequeue(node)) {
        if (!callback(node->m_data, node->m_unbalanced))
          break;

        if (node->m_left)
          q.enqueue(node->m_left);
        if (node->m_right)
          q.enqueue(node->m_right);
      }
    }

    bool lca(const T &a, const T &b, T &result, std::function<int(const T &, const T &)> compare) {
      Node *popNode;
      Stack<Node *> stack;

      std::vector<const T *> elements = { &a, &b };

      std::function<bool(Node *)> findNode;
      findNode = [&](Node *node) -> bool {
        if (!node)
          return false;

        if (elements.size() == 2)
          stack.push(node);

        for (auto it = elements.begin(); it != elements.end(); ++it) {
          if (compare(node->m_data, *(*it)) == 0) {
            elements.erase(it);
     
            stack.pop(popNode);
            if (popNode != node)
              stack.push(popNode);

            return true;
          }
        }

        if (findNode(node->m_left) && elements.empty())
          return true;

        if (findNode(node->m_right) && elements.empty())
          return true;

        stack.pop(popNode);
        if (popNode != node)
          stack.push(popNode);

        return false;
      };

      Node *node;
      if (findNode(m_root) && stack.pop(node)) {
        result = node->m_data;

        return true;
      }

      return false; 
    }

  private:
    struct Node
    {
      public:
        Node()
        {
        }

        Node(T t) : m_data(t)
        {
        }

        Node(Node *parent, T t) : m_data(t), m_parent(parent)
        {
        }

        T    m_data;
        Node *m_parent = NULL;
        Node *m_left   = NULL;
        Node *m_right  = NULL;

        int8_t m_unbalanced = 0;
    };

    Node *m_root = NULL;
};

template<typename T>
std::ostream &operator<<(std::ostream &out, const BinaryTree<T> &obj)
{
  if (!obj.m_root)
    return out;

  out << obj.SERIAL_ID;
  out << '#';

  typename BinaryTree<T>::Node *node = obj.m_root;
  Stack<typename BinaryTree<T>::Node *> stack;
  while (!stack.isEmpty() || node) {
    if (node) {
      stack.push(node);

      out << node->m_data;
      uint8_t children = 0;
      if (node->m_left)
        children |= obj.LEFT;
      if (node->m_right)
        children |= obj.RIGHT;

      out << children;
      node = node->m_left;
    }
    else {
      stack.pop(node);
      node = node->m_right;
    }
  }
  
  return out;
}

template<typename T>
std::istream &operator>>(std::istream &in, BinaryTree<T> &obj)
{
  int serial;
  char ch;
  in >> serial;
  in >> ch;
  if (serial != obj.SERIAL_ID || ch != '#')
    return in;

  Stack<typename BinaryTree<T>::Node *> stack;

  obj.m_root = new typename BinaryTree<T>::Node;

  typename BinaryTree<T>::Node *node = obj.m_root;

  while (!stack.isEmpty() || node) {
    if (node) {
      stack.push(node);
      T t;
      uint8_t children;

      in >> t;
      in >> children;

      node->m_data = t;

      if (!children)
        stack.pop(node);

      if (children & obj.RIGHT)
        node->m_right = new typename BinaryTree<T>::Node(node, -1);

      if (children & obj.LEFT) {
        node->m_left = new typename BinaryTree<T>::Node(node, -1);
        node = node->m_left;
      }
      else
        node = NULL;
    }
    else {
      stack.pop(node);
      node = node->m_right;
    }
  }

  return in;
}

#endif
