#include <map>
#include <limits>
#include <functional>

#include <cstring>

#include <stdint.h>
#include <assert.h>

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

void IntervalMapTest();

template<class K, class V>
class interval_map
{
  friend void IntervalMapTest();
  public:

    interval_map(const V &val)
    {
      m_map.insert(m_map.begin(), std::make_pair(std::numeric_limits<K>::min(), val));
    }

    void assign(const K &keyBegin, const K &keyEnd, const V &val)
    {
      ///////////////////////////////////////////
      // Complexity: O((4 * log n) + n) ~= O(n)
      ///////////////////////////////////////////

      static std::function<typename std::map<K, V>::iterator (const typename std::map<K, V>::iterator &, const std::pair<K, V> &, typename std::map<K, V> &)> insertElement =
      [&] (const typename std::map<K, V>::iterator &pos, const std::pair<K, V> &el, typename std::map<K, V> &map) -> typename std::map<K, V>::iterator {
        auto itInserted = map.insert(pos, el);

        auto itPrev = itInserted;
        if (itInserted != map.begin() && (--itPrev)->second == itInserted->second) {
          map.erase(itInserted);
          return ++itPrev;
        }

        return ++itInserted;
      };

      if (!(keyBegin < keyEnd))
        return;

      V prevVal;

      bool ignorePrev = false;
      auto itBegin = m_map.find(keyBegin); // O(log n)
      if (itBegin != m_map.end()) {
        auto toRemove = itBegin;
        prevVal = toRemove->second;
        if ((++itBegin) == m_map.end()) {
          ignorePrev = true;
          itBegin = m_map.begin();
        }

        m_map.erase(toRemove);
      }
      else {
        itBegin = --m_map.upper_bound(keyBegin); // O(log n)
        prevVal = itBegin->second;
      }

      auto itInserted = insertElement(itBegin, std::make_pair(keyBegin, val), m_map); // O(log n)
      while (itInserted != m_map.end() && itInserted->first < keyEnd) { // O(n)
        if (!ignorePrev)
          prevVal = itInserted->second;
        m_map.erase(itInserted++);
      }

      insertElement(itInserted, std::make_pair(keyEnd, prevVal), m_map); // O(log n)
    }

    const V &operator[](const K &key) const
    {
      return (--m_map.upper_bound(key))->second;
    }

  private:
    std::map<K, V> m_map;
};

class TestKey final
{
  public:
    TestKey()
    {
    }

    TestKey(int i) : m_value(i)
    {
    }

    bool operator<(int tmp) const
    {
      return m_value < tmp;
    }

    bool operator<(const TestKey &tmp) const
    {
      return m_value < tmp.m_value;
    }

    operator int() const
    {
      return m_value;
    }

  private:
    bool operator==(const TestKey &tmp) const
    {
      return true;
    }

    bool operator!=(const TestKey &tmp) const
    {
      return true;
    }

    bool operator>(const TestKey &tmp) const
    {
      return true;
    }

    bool operator>=(const TestKey &tmp) const
    {
      return true;
    }

    int m_value = 0;
};

namespace std
{
  template<>
  class numeric_limits<TestKey> final
  {
    public:
      static const bool is_specialized = true;
      static int min() throw() { return std::numeric_limits<int>::min(); }
      static int max() throw() { return std::numeric_limits<int>::max(); }
      static const int  digits = 0;
      static const int  digits10 = 0;
      static const bool is_signed = false;
      static const bool is_integer = false;
      static const bool is_exact = false;
      static const int radix = 0;
      static const int  min_exponent = 0;
      static const int  min_exponent10 = 0;
      static const int  max_exponent = 0;
      static const int  max_exponent10 = 0;
      
      static const bool has_infinity = true;
      static const bool has_quiet_NaN = true;
      static const bool has_signaling_NaN = false;
      static const bool has_denorm_loss = false;
      static const bool is_iec559 = false;
      static const bool is_bounded = false;
      static const bool is_modulo = false;
      
     static const bool traps = false;
     static const bool tinyness_before = false;
     static const float_round_style round_style = round_toward_zero;
  };
}

class TestValue final
{
  public:
    TestValue()
    {
    }

    TestValue(char i) : m_value(i)
    {
    }

    bool operator==(const TestValue &tmp) const
    {
      return m_value == tmp.m_value;
    }

    operator char() const
    {
      return m_value;
    }

    char value() const
    {
      return m_value;
    }

  private:
    bool operator<(const TestValue &tmp) const
    {
      return true;
    }


    bool operator!=(const TestValue &tmp) const
    {
      return true;
    }

    bool operator>(const TestValue &tmp) const
    {
      return true;
    }

    bool operator>=(const TestValue &tmp) const
    {
      return true;
    }

    char m_value = 0;
};

void IntervalMapTest()
{
  for (int j = 50; j < 100; ++j) {
    interval_map<int, int> map2(666);

    srand(time(NULL));
    int arr[j + 1];
    std::memset(arr, 0, sizeof(arr));

    int START = rand() % 10000;
    for (int i = START; i < 1000000; ++i) {
      int b = rand() % (j + 1);
      int e = rand() % (j + 1);
      int v = rand() % (j + 1);
      map2.assign(b, e, v);
      if (b < e) {
        for (auto i = b; i < e; ++i)
          arr[i] = v;
      }
    }

    for (auto i = START; i < j; ++i)
      assert(arr[i] == map2[i]);

    assert(map2[-1] == 666);
    assert(map2[j + 1] == 666);
  }

  interval_map<TestKey, TestValue> map(TestValue('A'));
  map.assign(TestKey(21), TestKey(25), TestValue('C'));
  map.assign(TestKey(15), TestKey(20), TestValue('B'));
  map.assign(TestKey(17), TestKey(21), TestValue('D'));
  map.assign(TestKey(22), TestKey(30), TestValue('L'));
  map.assign(TestKey(25), TestKey(34), TestValue('B'));
  map.assign(TestKey(27), TestKey(29), TestValue('B'));
  map.assign(TestKey(1), TestKey(5), TestValue('E'));
  map.assign(TestKey(35), TestKey(0), TestValue('D'));
  
  assert(map[std::numeric_limits<int32_t>::min()].value() == 'A');
  assert(map[-1].value() == 'A');
  assert(map[0].value() == 'A');
  
  for (int i = 1; i < 5; ++i)
    assert(map[i].value() == 'E');
  
  for (int i = 5; i < 15; ++i)
    assert(map[i].value() == 'A');
  
  assert(map[15].value() == 'B');
  assert(map[16].value() == 'B');
  
  for (int i = 17; i < 21; ++i)
    assert(map[i].value() == 'D');
  
  assert(map[21].value() == 'C');
  
  for (int i = 22; i < 25; ++i)
    assert(map[i].value() == 'L');
  
  for (int i = 25; i < 34; ++i)
    assert(map[i].value() == 'B');
  
  for (int i = 34; i < 40; ++i)
    assert(map[i].value() == 'A');
  
  for (auto it = map.m_map.begin(); it != map.m_map.end(); ++it) {
    auto next = it;
    ++next;
    if (next != map.m_map.end())
      assert(!(it->second == next->second));
  }
  
  map.assign(std::numeric_limits<int32_t>::min(), 20, 'M');
  
  for (int i = std::numeric_limits<int32_t>::min(); i < 20; i += 1000)
    assert(map[i].value() == 'M');
  
  assert(map[20].value() == 'D');
  assert(map[21].value() == 'C');
  
  for (auto it = map.m_map.begin(); it != map.m_map.end(); ++it) {
    auto next = it;
    ++next;
    if (next != map.m_map.end())
      assert(!(it->second == next->second));
  }
  
  interval_map<uint32_t, char> map1('L');
  assert(map1[0] == 'L');
  
  map1.assign(std::numeric_limits<uint32_t>::max() - 10, std::numeric_limits<uint32_t>::max() + 10, 'M');
  assert(map1[0] == 'L');
  assert(map1[std::numeric_limits<uint32_t>::max() - 10] == 'L');
  
  map1.assign(0, 0, 'M');
  assert(map1[0] == 'L');
  
  map1.assign(std::numeric_limits<uint32_t>::max() - 10, std::numeric_limits<uint32_t>::max(), 'M');
  assert(map1[std::numeric_limits<uint32_t>::max() - 10] == 'M');
  assert(map1[std::numeric_limits<uint32_t>::max() - 1] == 'M');
  assert(map1[std::numeric_limits<uint32_t>::max()] == 'L');
  
  map1.assign(21, 25, 'C');
  map1.assign(15, 20, 'B');
  map1.assign(17, 21, 'D');
  map1.assign(22, 30, 'S');
  map1.assign(25, 34, 'B');
  map1.assign(27, 29, 'B');
  map1.assign(1, 5, 'E');
  map1.assign(35, 0, 'D');
  
  for (int i = 1; i < 5; ++i)
    assert(map1[i] == 'E');
  
  for (int i = 5; i < 15; ++i)
    assert(map1[i] == 'L');
  
  assert(map1[15] == 'B');
  assert(map1[16] == 'B');
  
  for (int i = 17; i < 21; ++i)
    assert(map1[i] == 'D');
  
  assert(map1[21]  == 'C');
  
  for (int i = 22; i < 25; ++i)
    assert(map1[i] == 'S');
  
  for (int i = 25; i < 34; ++i)
    assert(map1[i] == 'B');
  
  for (int i = 34; i < 40; ++i)
    assert(map1[i] == 'L');
  
  assert(map1[0] == 'L');
  
  map1.assign(0, std::numeric_limits<uint32_t>::max(), 'D');
  assert(map1.m_map[std::numeric_limits<uint32_t>::max()] == 'L');
  assert(map1.m_map[0] == 'D');
  
  for (uint64_t i = 0; i < std::numeric_limits<uint32_t>::max(); i += 1000)
    assert(map1[i] == 'D');
  
  map1.assign(0, 500, 'K');
  for (uint64_t i = 0; i < 500; ++i)
    assert(map1[i] == 'K');
  
  for (uint64_t i = 500; i < std::numeric_limits<uint32_t>::max(); i += 1000)
    assert(map1[i] == 'D');
  
  map1.assign(10, 80, 'N');
  for (uint64_t i = 10; i < 80; ++i)
    assert(map1[i] == 'N');
  
  for (uint64_t i = 0; i < 10; ++i)
    assert(map1[i] == 'K');
  
  for (uint64_t i = 80; i < 500; ++i)
    assert(map1[i] == 'K');
  
  for (uint64_t i = 500; i < std::numeric_limits<uint32_t>::max(); i += 1000)
    assert(map1[i] == 'D');
  
  map1.assign(0, 1, 'N');
  
  assert(map1[0] == 'N');
  assert(map1[1] == 'K');
  map1.assign(0, 1, 'T');
  assert(map1[0] == 'T');
  map1.assign(1, 3, 'N');
  
  assert(map1[1] == 'N');
  assert(map1[2] == 'N');
  assert(map1[3] == 'K');
  
  for (auto it = map1.m_map.begin(); it != map1.m_map.end(); ++it) {
    auto next = it;
    ++next;
    if (next != map1.m_map.end())
      assert(it->second != next->second);
  }
}

int main(int argc, char **argv)
{
  IntervalMapTest();
  return 0;
}
