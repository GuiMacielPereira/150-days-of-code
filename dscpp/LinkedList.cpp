// My own attenpt at creating a LinkedList, no cheating!
#include <iostream>

template<typename T> 
class Node {
public:
  Node(){}; 
  Node(T v): val(v) {}; 
  Node* ptrToNxt = nullptr;
  T val;
};

template<typename T>
class LinkedList {
private:
  Node<T>* head = nullptr;

public:
  LinkedList(){};
  
  void add(T val) {
    Node<T> temp(val);
    temp.ptrToNxt = head;
    head = &temp;
  }

  void pop_head() {
    head = head->ptrToNxt;
  }

  int size() {
    Node<T>* buff = head;   // Avoid rewriting head
    for (int i=1; i++;) {
      buff = buff->ptrToNxt;
      if (buff == nullptr) {
        return i;
      }
    }
    return -1;
  }

  friend std::ostream& operator<<(std::ostream& os, const LinkedList<T>& ll) {
    Node<T>* buff = ll.head;
    while (buff != nullptr) {
      os << buff->val;
      buff = buff->ptrToNxt;
    }
    return os;
  }

};

int main() {
  LinkedList<int> ll;
  ll.add(4);
  ll.add(5);
  ll.add(6);
  ll.add(7);
  ll.size();
  // std::cout << ll;
}
