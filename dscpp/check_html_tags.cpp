#include <iostream>
#include <stack>
#include <string>
#include <fstream>


bool check_tags(std::ifstream& istrm) {
  if (!istrm) {
    std::cout << "Unable to open input file!" << std::endl;
    return false;
  }
  // Before starting to read file, set the stack
  std::stack<std::string> stck;

  // Start reading file
  for (std::string word; istrm >> word;) {

    // Skip if word is not tag 
    if (word[0]!='<' | word[word.size()-1]!='>') {
      continue;
    }

    if (word[1]=='/') {
      if (stck.top().compare(1, stck.top().size()-1, word, 2, word.size()-2) == 0) {
        stck.pop();
      } else {
        return false;
      }
    } else {
      stck.push(word);
    }
  }

  if (!stck.empty()) {
    return false;
  }

  return true;
}

int main() {
  std::ifstream istrm {"~/150-days-of-code/dscpp/simple.txt"};
  std::cout << check_tags(istrm) << std::endl;
}
