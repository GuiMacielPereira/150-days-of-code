template<typename T>
class LinkedList {
protected:
  T* head;
public:
  virtual int gethead() = 0;
};

template<typename T>
class UnorderedLinkedList: public LinkedList<T> {
public:
  T gethead () override {
    return *this->head;   // CAN'T USE HEAD BY ITSELLF: NON-DEPENDENT NAME
    // Need to access method through this-> to force it to look for depenent names
  }
};

int main() {}
