#include <deque>
#include <iostream>
#include <string>
#include <cctype>

bool isPalindrome(std::string sentence) {

  std::deque<char> q;

  for (const char& c : sentence) if (!std::isspace(c)) q.push_back(c); 

  while (!q.empty() & q.size()!=1) {
    if (q.front() == q.back()) {
      q.pop_back();
      q.pop_front();
    } else {
      return false;
    }
  }
return true;
}

int main () {
  std::cout << isPalindrome("I PREFER PI") << std::endl;
  std::cout << isPalindrome("I\nPREFER PI") << std::endl;
  std::cout << isPalindrome("I  PREFER PI") << std::endl;
  std::cout << isPalindrome("I DO NOT PREFER PI") << std::endl;
}
