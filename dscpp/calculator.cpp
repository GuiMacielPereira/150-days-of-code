
#include <iostream>
#include <stack>
#include <unordered_map>
#include <string>
#include <vector>
#include <cassert>

class Calculator {
  
  public:
    Calculator(std::string infixexpr) : m_infix(infixexpr) {};
    ~Calculator() = default;
    std::string get_infix();
    std::string get_postfix();
    int calculate();

  private:
    std::string NUMS = "0123456789";
    std::string OPS = "+-*/";
    static std::unordered_map<char, int> prec_table;
    std::string m_postfix;
    std::string m_infix;
    void _infix_to_postfix();
    int _solve_postfix();
};

std::unordered_map<char, int> Calculator::prec_table {{'*', 3}, {'/', 3}, {'+', 2}, {'-', 2}, {'(', 1}};

int Calculator::calculate() {
  _infix_to_postfix();
  return _solve_postfix();
}

void Calculator::_infix_to_postfix() {
    std::stack<char> opStack;
    std::vector<char> postfixVector;

    for (char token : m_infix) {
      if (token == ' ') {
          continue;
      }
      else if (NUMS.find(token)<=NUMS.length()) { //finds if the token is inside of NUMS
        postfixVector.emplace_back(token); // appends to the end of the container.
      } else if (OPS.find(token)<=OPS.length()) {
          while (!opStack.empty() && (prec_table[opStack.top()]>=prec_table[token])) {
            postfixVector.emplace_back(opStack.top());
            opStack.pop();
            }
          opStack.push(token);
      } else if (token == '(') {
          opStack.push(token);
      } else if (token == ')') {
          char topToken = opStack.top();
          opStack.pop();
          while (topToken != '(') {
              postfixVector.emplace_back(topToken);
              topToken=opStack.top();
              opStack.pop();
          }
      } else { 
        throw std::invalid_argument ("Character not recognized");
      }
    }
    while (!opStack.empty()) {
        postfixVector.emplace_back(opStack.top());
        opStack.pop();
    }
    std::string s(postfixVector.begin(),postfixVector.end());
    m_postfix = s;
}

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

void printStack(std::stack<int> stck) {  // Copy constructor
  std::cout << "\n";
  while (!stck.empty()) {
    std::cout << stck.top() << " ";
    stck.pop();
  }
}

int Calculator::_solve_postfix() {
  std::stack<int> stck;

  for (char ch : m_postfix) {
    if (ch == ' ') {
      continue;
    } else if (NUMS.find(ch) <= NUMS.length()) {    // Best way to do 'in' operator like Python
      stck.push(ch - '0');             // Correct conversion from character to integer 
    } else if (OPS.find(ch) <= OPS.length()) {
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

int main() try {
    std::cout << Calculator("(5 + 9) * 2").calculate();
    return 0;
} catch (std::exception &e) {
  std::cout << e.what() << std::endl;
}
