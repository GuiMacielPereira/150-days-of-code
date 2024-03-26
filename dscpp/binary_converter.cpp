
#include <stack>
#include <iostream>

void print_binary( int num ) {
  std::cout << num << " -> ";
  std::stack<int> s;
  while (num > 0) {
    s.push(num % 2);
    num = num / 2;
  }
  while (!s.empty()) {
    std::cout << s.top();
    s.pop();
  }
  std::cout << "\n";
}

int main () {
  print_binary(17);
  print_binary(45);
  print_binary(96);
}
