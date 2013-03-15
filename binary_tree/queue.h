#include <stdio.h>

template<class T>
class Queue {
  public:
    virtual ~Queue()
    {
      Node *node = m_head;
      while (node) {
        Node *tmp = node;
        node = node->m_next;
        delete node;
      }
    }

    void enqueue(T t)
    {
      if (!m_head)
        m_head = m_tail = new Node(t);
      else {
        m_tail->m_next = new Node(t);
        m_tail = m_tail->m_next;
      }
    }

    bool dequeue(T &result)
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
    Node *m_tail = NULL;
};
