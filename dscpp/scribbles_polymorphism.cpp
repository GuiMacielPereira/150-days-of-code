#include <iostream>
#include <typeinfo>

class Letters {
public:
  char let {' '};
  Letters (char let) : let(let) {}
  Letters getLetter() {
    return *this;
  }
};

class A: public Letters {
public:
  A(): Letters('A'){};
};

int main() {
  A a{};
  std::cout << typeid(a.getLetter()).name();
  Letters L{' '};
  std::cout << typeid(L.getLetter()).name();
}
