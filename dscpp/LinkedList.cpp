#include "LinkedList.h"
// The reason we use header files is because main() can only be defined once
#include <iostream>

int main() try {
  // UnorderedLinkedList<int> ll;
  OrderedLinkedList<int> ll;
  ll.add(4);
  ll.add(5);
  ll.add(6);
  ll.add(6);
  ll.add(7);
  std::cout << ll;
  std::cout << "size: " << ll.size() << std::endl;
  std::cout << "head: " << ll.gethead() << std::endl;
  ll.remove(6);
  std::cout << ll;
  ll.remove(7);
  std::cout << ll;
  ll.remove(4);
  std::cout << ll;
  std::cout << "size: " << ll.size() << std::endl;
  ll.add(8);
  ll.add(9);
  ll.add(10);
  ll.add(12);
  // ll.insert(1, 0);
  // std::cout << ll;
  // ll.insert(2, 1);
  // std::cout << ll;
  // ll.insert(3, 3);
  std::cout << ll;
  std::cout << "size: " << ll.size() << std::endl;
  // ll.append(9);
  std::cout << ll;
  std::cout << ll.index(0) << std::endl;
  std::cout << ll.index(2) << std::endl;
  std::cout << ll.index(3) << std::endl;
  std::cout << ll;
  OrderedLinkedList<int> slc_ll = ll.slice(2, 5);
  std::cout << "slice: " << slc_ll;
} catch (const std::exception& e) {
  std::cout << e.what() << std::endl;
}
