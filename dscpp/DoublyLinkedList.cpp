#include <iostream>


template<typename T>
class Node {
public:
  Node(T v): value(v) {}; 
  Node* next = nullptr;
  Node* prev= nullptr;
  T value;
};

template<typename T>
class DoublyLinkedList {
private:
  Node<T>* head = nullptr;
  Node<T>* tail = nullptr;
  int size = 0;

public:
  DoublyLinkedList<T> () {};
  bool empty();
  void add(T val);
  void remove_at(int idx);
  void insert_at(T val, int idx);

  friend std::ostream& operator<<(std::ostream& os, const DoublyLinkedList<T>& ll) {
    Node<T>* buff = ll.head;
    os << '[';
    while (buff != nullptr) {
      os << buff->value << " ";
      buff = buff->next;
    }
    os << ']' << std::endl;
    return os;
  }
};

template<typename T>
bool DoublyLinkedList<T>::empty() {
  return head == nullptr; 
}

template<typename T>
void DoublyLinkedList<T>::add(T val) {
  // Adds always to the head
  Node<T>* temp = new Node<T>(val);

  if (!this->empty()){
    temp->next = head;
    head->prev = temp;
    head = temp;
    return;
  }
  tail = temp;
  head = temp;
  return;
}

int main () {
  DoublyLinkedList<int> dll;
  dll.add(0);
  dll.add(1);
  dll.add(2);
  dll.add(3);
  std::cout << dll << std::endl;
}
