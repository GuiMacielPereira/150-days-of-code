#include <iostream>
#include <ostream>
#include <string>
#include <random>

// I also want to use the least ammount of memory possible

std::string avlbl_chars = "abcdefghijklmnopqrstuvwxyz ";
std::uniform_int_distribution<int> distribution(0, avlbl_chars.size()-1);
std::default_random_engine generator;


void modify_str(std::string &result){
  for (int j=0; j<result.size(); j++) {
    if (result[j] == '$') {
      result[j] = avlbl_chars[distribution(generator)];
    }
  }
}


double check_similarity(std::string &result, const std::string &benchmark){
  int right_counts {0};
  for (int i=0; i<result.size(); i++) {
    if (result[i]==benchmark[i]){
      right_counts++;
    }
    else {
      result[i] = '$';
    }
  }
  return double(right_counts) / result.size();
}

void compare_generated (std::string &curr_str, const std::string &target, std::string &closest_str, double &best_acc) {

  double curr_acc = check_similarity(curr_str, target);

  if (curr_acc > best_acc) {
    best_acc = curr_acc;
    closest_str = curr_str;
    std::cout << "Acc: " << best_acc << ", string: " << curr_str << std::endl;
  }
}

// Modified initial random algorithm to accept '$' as a placeholder for unsuccessful character
// Aparently this modified version is called 'Hillclimb' algorithms

int main () {

  std::string target = "methinks it is like a weasel";
  std::string curr_str = std::string(target.size(), '$');

  double best_acc {0};
  std::string closest_str {' '};

  for (int i=0; curr_str != target; i++) {
    modify_str(curr_str);
    compare_generated(curr_str, target, closest_str, best_acc);
  }
std::cout << "The closest string was: "<< closest_str << std::endl;
return 0;
}


