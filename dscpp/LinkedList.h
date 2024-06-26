#include <stdexcept>
#include <iostream>
#include <typeinfo>
#include <stack>

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
  int m_size = 0;

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
    return m_size;
  }

  void remove(T val) {
    Node<T>* curr=head;
    Node<T>* prev=nullptr;

    while (curr != nullptr) {

      if (curr->val == val) {

        if (prev==nullptr) {
          head = head->ptrToNxt;
          delete curr;
          m_size--;
          return;

        } else {
          prev->ptrToNxt = curr->ptrToNxt;
          delete curr;
          m_size--;
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
    os << '[';
    while (buff != nullptr) {
      os << buff->val << " ";
      buff = buff->ptrToNxt;
    }
    os << ']' << std::endl;
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
    this->m_size++;
  }

  void append (int val) {
    insert (val, 0);
    this->m_size++;
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
          this->m_size++;
          return;
        } else {
          prev->ptrToNxt = newNode;
          newNode->ptrToNxt = curr;
          this->m_size++;
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
    this->m_size++;
    return;
  }

  void insert (T val, int idx) {
    Node<T>* curr=this->head;
    Node<T>* prev=nullptr;

    for (int i=0;; i++) {
      if (i==idx) {

        // Section of asserts for ordered sequence
        if (prev!=nullptr && curr!=nullptr) {
          if (val <= prev->val && val >= curr->val) {
            throw std::invalid_argument("Value to insert is not in between values of previous and current");
          } else if (prev==nullptr) {
            if (val >= curr->val) {
              throw std::invalid_argument("Value to insert at the begining is not lower than head");
            }
          } else if (curr==nullptr) {
            if (val <= prev->val) {
              throw std::invalid_argument("Value to insert at the tail is not bigger");
            }
          }
        }
        auto newNode = new Node<T>(val);
        if (i==0) {
          newNode->ptrToNxt = this->head;
          this->head = newNode;
          this->m_size++;
          return;
        } else {
          prev->ptrToNxt = newNode;
          newNode->ptrToNxt = curr;
          this->m_size++;
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

  // I tried to implement this in a virtual function 
  // But my LSP was not working properly so fuck it
  // Still don't know how I would do a virtual function
  // that returns the children type
  OrderedLinkedList<T> slice (int start, int stop) {
    if (start > stop) {
      throw std::invalid_argument("Start of slice cannot be bigger than end.");
    }
    // This might be the most stupid implementation of this method buy see if I care lol
    std::stack<Node<T>*> buff;
    OrderedLinkedList<T> ll_copy;

    // Put nodes in buffer list (acts as a stack)
    Node<T>* curr = this->head;
    for (int i=0; i<stop; i++) {
      if (i>=start) {
        buff.push(curr);
      }
      curr = curr->ptrToNxt;
    }
    while (!buff.empty()) {
      ll_copy.add(buff.top()->val);
      buff.pop();
    }
    return ll_copy;
  }
};
