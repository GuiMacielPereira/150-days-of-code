#include <stdexcept>
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
protected:
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

  virtual void add (T val) = 0;
  virtual void insert (T val, int idx) = 0;

  bool isempty() const {
    return head ==  nullptr;
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

template<typename T>
class UnorderedLinkedList : public LinkedList<T> {
public:
  UnorderedLinkedList() : LinkedList<T>{} {};

  void add(T val) override {
    auto temp = new Node<T>(val);
    temp->ptrToNxt = this->head;
    this->head = temp;
  }

  void append (int val) {
    insert (val, 0);
  }

  void insert (T val, int idx) {
    Node<T>* curr=this->head;
    Node<T>* prev=nullptr;

    for (int i=0;; i++) {
      if (i==idx) {
        auto newNode = new Node<T>(val);

        if (i==0) {
          newNode->ptrToNxt = this->head;
          this->head = newNode;
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
};

template<typename T>
class OrderedLinkedList : public LinkedList<T> {
public:
  OrderedLinkedList() : LinkedList<T>{} {};

  void add(T val) override {

    if ((this->head!=nullptr) && (val < this->head->val)) {
      throw std::invalid_argument("Can't add lower value than head of current list");
    }
    auto temp = new Node<T>(val);
    temp->ptrToNxt = this->head;
    this->head = temp;
    return;
  }

  void insert (T val, int idx) {
    Node<T>* curr=this->head;
    Node<T>* prev=nullptr;

    for (int i=0;; i++) {
      if (i==idx) {
        if ((prev!=nullptr) && (val <= prev->val && val >= curr->val)) {
          throw std::invalid_argument("Value to insert is not in between values of previous and current");
        }
        auto newNode = new Node<T>(val);
        if (i==0) {
          newNode->ptrToNxt = this->head;
          this->head = newNode;
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
};
