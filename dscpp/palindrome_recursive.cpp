#include <iostream>
#include <string>
#include <algorithm>

bool is_palindrome (std::string s) {
  // Check for characters to ignore
  std::string charToIgnore = " .;!?,";
  while (charToIgnore.find(s[0])!=std::string::npos) {
    s = s.substr(1);
  }
  while (charToIgnore.find(s[s.length()-1])!=std::string::npos) {
    s = s.substr(0, s.length()-1);
  }

  if (s.length()<=1) {
    return true;
  } else {
    return (s[0]==s[s.length()-1]) && is_palindrome(s.substr(1, s.length()-2));
  }
}

int main() {
  std::cout << is_palindrome("not a palindrome");
  std::cout << is_palindrome("aibohphobia");
  std::cout << is_palindrome("live, not on evil!");
  // PS. I am so good at this that sometimes I scare myself OwO
}
