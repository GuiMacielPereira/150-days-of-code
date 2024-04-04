#include <forward_list>
#include <iostream>
#include <queue>
#include <iterator>

template<typename T>
class QueueList{
  public:
    void pop();
    void push(T elem);

  private:
    std::forward_list<T> m_list;

  template<typename Y>
  friend std::ostream& operator<<(std::ostream& os, const QueueList<Y> &fl) {
    os << '[';
    for (auto elem : fl.m_list) os << elem << ' ';
    os << ']' << std::endl;
  return os;
  }
};

template<typename T> void QueueList<T>::pop() {
  m_list.erase_after(m_list.end()--);
}

template<typename T> void QueueList<T>::push( T elem ) {
  m_list.push_front(elem);
}

template<typename T>
std::pair<double, double> cookie_cutter_times(T &q, int size) {

  clock_t  begin_ht= clock();
  for (int i=0; i < size; i++) {
    q.push(i);
  }
  clock_t end_ht = clock();
  double elapsed_secs_push = double(end_ht - begin_ht) / CLOCKS_PER_SEC;

  begin_ht = clock();
  for (int i=0; i < size; i++) {
    q.pop();
  }
  end_ht = clock();
  double elapsed_secs_pop = double(end_ht - begin_ht) / CLOCKS_PER_SEC;
  return std::pair<double, double>(elapsed_secs_push, elapsed_secs_pop);
}

int main () {
  QueueList<int> ql;
  ql.push(4);
  ql.push(3);
  ql.push(7);
  std::cout << ql;
  ql.pop();
  std::cout << ql;
  ql.pop();
  std::cout << ql;
  // std::cout << "Std Queue Push, List Queue Push, Std Queue Pop, List Queue Pop" << std::endl;
  //
  //   for(int a = 10000; a < 1000001; a = a + 20000) {
  //     std::queue<int> stdqueue;
  //     QueueList<int> listqueue; 
  //
  //     auto queue_times = cookie_cutter_times(stdqueue, a);
  //     auto qlist_times = cookie_cutter_times(listqueue, a);
  //
  //     std::cout << queue_times.first << "  " << qlist_times.first << "  "
  //     << queue_times.second << "  " << qlist_times.second << std::endl;
  //   }
  //   return 0;
}

