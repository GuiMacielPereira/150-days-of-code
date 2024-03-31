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

  bool isempty() const {
    return head ==  nullptr;
  }
  
  void add(T val) {
    auto temp = new Node<T>(val);
    temp->ptrToNxt = head;
    head = temp;
  }

  T gethead() const {
    return head->val;
  }

  void pophead() {
    Node<T>* buff;
    buff = head;
    head = head->ptrToNxt;
    delete buff;
  }

  int size() const {
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

  void insert (T val, int idx) {
    Node<T>* curr=head;
    Node<T>* prev=nullptr;

    for (int i=0;; i++) {
      if (i==idx) {
        auto newNode = new Node<T>(val);

        if (i==0) {
          newNode->ptrToNxt = head;
          head = newNode;
          return;
        } else {
          prev->ptrToNxt = newNode;
          newNode->ptrToNxt = curr;
          return;
        }
      }
      if (curr==nullptr) {   // Conditonal here instead of loop to account for edge case of end of list
        break;
      }
      prev = curr;
      curr = curr->ptrToNxt;
    }
    throw std::out_of_range("Index provided is out of range.");
  }

  void append (int val) {
    insert (val, 0);
  }

  T index (int idx) const {
    Node<T>* curr=head;
    for (int i=0; curr!=nullptr; i++) {
      if (i==idx) {
        return curr->val;
      }
      curr = curr->ptrToNxt;
    }
    throw std::out_of_range("Index is out of range of linked list");
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
  ll.insert(1, 0);
  std::cout << ll;
  ll.insert(2, 1);
  std::cout << ll;
  ll.insert(3, 3);
  std::cout << ll;
  ll.append(9);
  std::cout << ll;
  std::cout << ll.index(0) << std::endl;
  std::cout << ll.index(2) << std::endl;
  std::cout << ll.index(3) << std::endl;
} catch (const std::exception& e) {
  std::cout << e.what() << std::endl;
}
