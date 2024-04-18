
#include <iostream> 
#include <string>

// Trying to make a converter to binary from recursion (from memory)

std::string to_base (int n, int base) {

  std::string convertToChar = "0123456789ABCDEF";

  if (n <= base) {
    return std::string (1, convertToChar[n]);
  } else {
    return to_base(n / base, base) + convertToChar[n % base];
  }
}

int main() {
  std::cout << to_base(1453, 16);
  // The recursive behaviour is very similar to using a stack 
  // Because DUH, the recursion is implemented through a stack frame
}
