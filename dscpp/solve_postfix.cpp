// My solution for the postfix problem (before looking at the textbook solution)

#include <iostream>
#include <stack>
#include <string>
#include <cassert>

int calc(int a, int b, char op) {
  switch (op) {
    case '+':
      return a + b;
    case '-':
      return a - b;
    case '*':
      return a * b;
    case '/':
      return a / b;
    default:
      throw std::invalid_argument("Operator not recognized!");
  }
}

void printStack(std::stack<int> stck) {
  std::cout << "\n";
  while (!stck.empty()) {
    std::cout << stck.top() << " ";
    stck.pop();
  }
}

int solvePostfix(std::string input) {
  std::stack<int> stck;
  std::string nums = "1234567890";
  std::string ops = "+-/*";

  for (char ch : input) {
    if (ch == ' ') {
      continue;
    } else if (nums.find(ch) <= nums.length()) {    // Best way to do 'in' operator like Python
      stck.push(ch - '0');             // Correct conversion from character to integer 
    } else if (ops.find(ch) <= ops.length()) {
      int b = stck.top();
      stck.pop();
      int a = stck.top();
      stck.pop();
      
      stck.push(calc(a, b, ch));
    } else {
      throw std::invalid_argument ("\nChar not recognized."); 
    }
    printStack(stck);
  }
  assert(stck.size()==1);
  return stck.top();
}

void printResult(std::string postfixExpr) try {
  int result = solvePostfix(postfixExpr);
  std::cout << "The result of " << postfixExpr << " is " << result << "\n";
} catch (std::exception &e) {
    std::cout << e.what();
}

int main () {
  std::string exprA = "565*+";
  std::string exprB = "7 8 + 3 2 + /";
  std::string exprC = "7 8 % 3 2 + /";
  std::string exprD = "7 8 + 3 A + /";
  printResult(exprA);
  printResult(exprB);
  printResult(exprC);
  printResult(exprD);
}
