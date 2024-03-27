#include <iostream>
#include <stack>
#include <string>
#include <fstream>
#include <filesystem>


// Very proud of this little function UwU, worked first time
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


// Cool way of formatting strings
std::string testhtml {R"(
<html>
   <head>
      <title>
         Example
      </title>
   </head>

   <body>
      <h1>Hello, world</h1>
   </body>
</html>
)"};


int main() {
  // Create html file
  std::ofstream ostrm {"basic.html"};
  ostrm << testhtml;
  ostrm.close();

  // Read html from file
  std::ifstream istrm {"basic.html"};
  std::string message = check_tags(istrm) ? "File parsed correctly!" : "Tags in file don't match";
  std::cout << message << std::endl;
  istrm.close();
}
