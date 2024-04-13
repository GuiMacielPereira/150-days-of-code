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
public:
  Node<T>* head = nullptr;
  Node<T>* tail = nullptr;
  int size = 0;
  DoublyLinkedList<T> () {};
  bool empty();
  void add(T val);
  void pop ();
  bool search (T val);
  void remove_at(int idx);
  void insert_at(T val, int idx);

  friend std::ostream& operator<<(std::ostream& os, const DoublyLinkedList<T>& ll) {
    Node<T>* buff = ll.head;
    os << '[';
    while (buff != nullptr) {
      os << buff->value << " ";
      buff = buff->next;
    }
    os << ']';
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
  // List is empty, create head
  tail = temp;
  head = temp;
  size++;
  return;
}

template<typename T> 
void DoublyLinkedList<T>::pop() {
  if (empty()) {
    return;
  }
  head = head->next;
  size--;
}

template<typename T> 
bool DoublyLinkedList<T>::search(T val) {
  Node<T>* frontwards = this->head;
  Node<T>* backwards = this->tail;

  if (this->empty()) {
    return false;
  }
  if (frontwards->value==val || backwards->value==val) {
    return true;
  }

  while (frontwards!=backwards && frontwards->next!=backwards) {

    frontwards = frontwards->next;
    backwards = backwards->prev;

    if ((frontwards->value==val) || (backwards->value==val)) {
      return true;
    }
  }
  return false;
}

template<typename T> 
void DoublyLinkedList<T>::remove_at(int idx) {
  // Actually this implementation should be simpler than for single linked lists

  if (idx > size-1) {
    std::cout << "Idex out of range of list size " << size << "\n";
  }
  Node<T>* curr = head;
  for (int i=0; i<idx; i++) {
    curr = curr->next;
  }
  if (curr==head) {
    if (head->next!=nullptr) {
      head->next->prev = nullptr;
    }
    head = head->next;
  } else if (curr==tail) {
    if (tail->prev!=nullptr) {
      tail->prev->next = nullptr;
    }
    tail = tail->prev;
  } else {
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
  }
  delete curr;
  return;
}

int main () {
  DoublyLinkedList<int> dll;
  dll.add(0);
  std::cout << dll << std::endl;
  std::cout << "Value at head: " <<  dll.head->value << std::endl;
  std::cout << "Value at tail: " << dll.tail->value << std::endl;
  dll.add(1);
  dll.add(2);
  dll.add(3);
  std::cout << dll << std::endl;
  std::cout << "Value of 2 in list: " << dll.search(2) << std::endl;
  std::cout << "Value of 4 in list: " << dll.search(4) << std::endl;
  std::cout << "Value at head: " <<  dll.head->value << std::endl;
  std::cout << "Value at tail: " << dll.tail->value << std::endl;
  dll.pop();
  dll.pop();
  dll.pop();
  std::cout << dll << std::endl;
  std::cout << "Value of 0 in list: " << dll.search(0) << std::endl;
  std::cout << "Value of 1 in list: " << dll.search(1) << std::endl;
  std::cout << "Value at head: " <<  dll.head->value << std::endl;
  std::cout << "Value at tail: " << dll.tail->value << std::endl;
  dll.pop();
  std::cout << dll << std::endl;
  std::cout << "Value of 1 in list: " << dll.search(1) << std::endl;
  dll.add(4);
  dll.add(5);
  dll.add(6);
  dll.add(7);
  std::cout << dll << std::endl;
  dll.remove_at(3);
  std::cout << dll << std::endl;
  dll.remove_at(1);
  std::cout << dll << std::endl;
  dll.remove_at(0);
  std::cout << dll << std::endl;
  dll.remove_at(0);
  std::cout << dll << std::endl;
}
