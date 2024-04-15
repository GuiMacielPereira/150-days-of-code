#include <iostream>
#include <string>

std::string reverse (std::string s) {

  if (s.length() <= 1) {
    return std::string(1, s[0]);
  } else {
    // Same result but slightly easier to conceptualize
    // return s[s.length()-1] + reverse(s.substr(0, s.length()-1));
    return reverse(s.substr(1)) + s[0];
  }
}

int main () {
  std::cout << reverse("abc");
}

