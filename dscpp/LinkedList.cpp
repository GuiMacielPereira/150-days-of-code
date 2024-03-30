// My own attenpt at creating a LinkedList, no cheating!
#include <iostream>
#include <stdexcept>

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
  ~LinkedList() {
    Node<T>* buff;
    while (head!=nullptr) {
      buff = head;
      head = head->ptrToNxt;
      delete buff;
    }
  }
  
  void add(T val) {
    auto temp = new Node<T>(val);
    temp->ptrToNxt = head;
    head = temp;
  }

  T gethead() {
    return head->val;
  }

  void pop_head() {
    Node<T>* buff;
    buff = head;
    head = head->ptrToNxt;
    delete buff;
  }

  int size() {
    Node<T>* buff = head;   // Avoid rewriting head
    int count = 0;
    while (buff!=nullptr) {
      buff = buff->ptrToNxt;
      count++;
    }
    return count;
  }

  void remove(T val) {
    Node<T>* curr=head;
    Node<T>* prev=nullptr;

    while (curr != nullptr) {

      if (curr->val == val) {

        if (prev==nullptr) {
          head = head->ptrToNxt;
          delete curr;
          return;

        } else {
          prev->ptrToNxt = curr->ptrToNxt;
          delete curr;
          return;
        } 
      }
    prev = curr;
    curr = curr->ptrToNxt;
    }
    throw std::overflow_error("Value not found in Linked List.");
    return;
  }

  friend std::ostream& operator<<(std::ostream& os, const LinkedList<T>& ll) {
    Node<T>* buff = ll.head;
    while (buff != nullptr) {
      os << buff->val << " ";
      buff = buff->ptrToNxt;
    }
    os << std::endl;
    return os;
  }
};

int main() try {
  LinkedList<int> ll;
  ll.add(4);
  ll.add(5);
  ll.add(6);
  ll.add(7);
  std::cout << ll.size() << std::endl;
  std::cout << ll.gethead() << std::endl;
  std::cout << ll;
  ll.remove(6);
  std::cout << ll;
  ll.remove(7);
  std::cout << ll;
  ll.remove(4);
  std::cout << ll;
} catch (const std::exception& e) {
  std::cout << e.what() << std::endl;
}
