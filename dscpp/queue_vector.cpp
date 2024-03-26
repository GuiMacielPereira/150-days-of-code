#include <optional>
#include <vector>
#include <iostream>
#include <queue>
#include <functional>
#include <utility>

template<typename T>
class QueueVector {
  public:
    void pop();
    void push(T elem);
    bool empty();
    int size();
    T front();
    T back();

  private:
    std::vector<T> m_vector {};

  template<typename Y>
  friend std::ostream& operator<<(std::ostream& os, const QueueVector<Y> &q) {
  for (auto elem : q.m_vector) os << elem;
  return os;
  }
};

template<typename T> void QueueVector<T>::pop() {
  m_vector.erase(m_vector.end()-1);     // Remember that end() is boundary outside vector
}

template<typename T> void QueueVector<T>::push( T elem ) {
  m_vector.insert(m_vector.begin(), elem);
}

template<typename T> int QueueVector<T>::size() {
  return m_vector.size();
}

// Implement decorator to get running time 
// Implementation comes from stackoverflow
template <class> struct TimeIt;

template <class R, class... Args>
struct TimeIt<R(Args ...)>
{
   TimeIt(std::function<R(Args ...)> f, int size) : f_(f), size_(size){}

    double operator()(Args ... args)
   {
      clock_t begin = clock();
      for (int i=0; i<size_; i++) f_(args...);
      clock_t end = clock();
      double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
      std::cout << "Running time: " << elapsed_secs;
      return elapsed_secs;
   }
   std::function<R(Args ...)> f_;
  int size_;
};

template<class R, class... Args>
TimeIt<R(Args...)> makeDecorator(R (*f)(Args ...), int size)
{
   return TimeIt<R(Args...)>(std::function<R(Args...)>(f), size);
}

// I gave up, so just wrote a simple straight forward function
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

int main() {

  // Tried to play around with invoke method
  // QueueVector<int> vectqueue;
  // qvector_method(vectqueue, &QueueVector<int>::push);
  // qvector_method(vectqueue, &QueueVector<int>::push);
  // qvector_method(vectqueue, &QueueVector<int>::push);
  // std::cout << vectqueue;

  std::cout << "Std Queue Push, Vect Queue Push, Std Queue Pop, Vect Queue Pop" << std::endl;

    for(int a = 10000; a < 1000001; a = a + 20000) {
      std::queue<int> stdqueue;
      QueueVector<int> vectqueue; 

      auto queue_times = cookie_cutter_times(stdqueue, a);
      auto qvector_times = cookie_cutter_times(vectqueue, a);

      std::cout << queue_times.first << "  " << qvector_times.first << "  "
      << queue_times.second << "  " << qvector_times.second << std::endl;
    }
    return 0;
}

/* Results 
Unsurprisingly the push method is O(1) for queue and O(n) for vector
Surprisingly the pop method is O(1) for queue but bigger for vector
*/
