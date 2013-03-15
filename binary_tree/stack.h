#include <stdio.h>

template<class T>
class Stack {
  public:
    virtual ~Stack()
    {
      Node *node = m_head;
      while (node) {
        Node *tmp = node;
        node = node->m_next;
        delete node;
      }
    }

    void push(T t)
    {
      if (!m_head)
        m_head = new Node(t);
      else {
        Node *tmp = new Node(t);
        tmp->m_next = m_head;
        m_head = tmp;
      }
    }

    bool peek(T &result)
    {
      if (!m_head)
        return false;

      result = m_head->m_data;

      return true;
    }
 
    bool pop(T &result)
    {
      if (!m_head)
        return false;

      Node *tmp = m_head;
      m_head    = m_head->m_next;
      result    = tmp->m_data; 
      delete tmp;

      return true;
    }

    bool isEmpty()
    {
      return !m_head;
    }

  private:

    class Node
    {
      public:
        Node(T t) : m_data(t)
        {
        }

        T m_data;
        Node *m_next = NULL;
    };

    Node *m_head = NULL;
};
