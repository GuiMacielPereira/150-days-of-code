
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>


// Idea is to put queues in a vector
void sort_queue(std::queue<std::string> &q) {

  std::vector<std::queue<std::string>> digit_queues (10, std::queue<std::string>());

  for (int digit=1; digit<4; digit++) {
    std::cout << "digit: "<< digit << std::endl;

    while (!q.empty()) {

      std::string curr_val = q.front();
      q.pop();

      std::cout << curr_val << std::endl;

      int str_idx = curr_val.size() - digit;

      if (str_idx < 0 ) {
        digit_queues[0].push(curr_val);    // Consider cases where number of digits is less than the one being considered
      } else {
        digit_queues[int(curr_val[str_idx] - '0')].push(curr_val);
      }
    }
    for (auto &digit_q : digit_queues) {
      while (!digit_q.empty()) {
        q.push(digit_q.front());
        digit_q.pop();
      }
    }
  }
}

// Returns the integer at the decimal place of a number
int get_dec(int n, int dec) {
    // Handles case where decimal place is more than the number or is negative
    return n / int(std::pow(10, std::max(dec-1, 0))) % 10; 
}

void sort_queue( std::queue<int> &q) {

  std::vector<std::queue<int>> digit_queues (10, std::queue<int>());

  for (int digit=1; digit<4; digit++) {
    std::cout << "digit: "<< digit << std::endl;

    while (!q.empty()) {

      int curr_val = q.front();
      q.pop();

      std::cout << curr_val << std::endl;

      digit_queues[get_dec(curr_val, digit)].push(curr_val);
    }
    for (auto &digit_q : digit_queues) {
      while (!digit_q.empty()) {
        q.push(digit_q.front());
        digit_q.pop();
      }
    }
  }
}

int main () {
  // std::queue<std::string> q;
  // q.push("42");
  // q.push("234");
  // q.push("4");
  // q.push("245");
  // q.push("24");
  //
  // // String implementation of queue
  // sort_queue(q);
  // std::cout << "Final sorted queue:" << std::endl;
  // while (!q.empty()) {
  //   std::cout << q.front() << std::endl;
  //   q.pop();
  // }

  std::queue<int> q_int;
  q_int.push(42);
  q_int.push(234);
  q_int.push(4);
  q_int.push(245);
  q_int.push(24);
  q_int.push(23);
  q_int.push(26);

  // Int implementation of queue
  sort_queue(q_int);
  std::cout << "Final sorted queue:" << std::endl;
  while (!q_int.empty()) {
    std::cout << q_int.front() << std::endl;
    q_int.pop();
  }
} 
