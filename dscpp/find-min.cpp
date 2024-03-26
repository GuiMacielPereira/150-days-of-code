

#include <iostream>
using namespace std;

// Highly ineficient function lol
int find_min_quad (int* int_array, int array_size) {

  int n {int_array[0]};
  bool is_min {true};

  for (int i=0; i<array_size; i++) {
    is_min = true;

    for (int j=0; j<array_size; j++) {
      n = int_array[i];
      if (n > int_array[j]) {
        is_min = false;
        break;
      }
    }
    if (is_min) { break; }
  }
  return n;
}


// Linear search function
int find_min_linear (int* int_array, int array_size) {

  // Popular algorithm
  int min {int_array[0]};

  for (int i=0; i<array_size; i++) {
    if (int_array[i] < min) {
      min = int_array[i];
    }
  }
  return min;
}

int main() {
  int arr[] = {1, 2, 3, 2, 5};
  cout << find_min_quad(arr, 5); 
  cout << find_min_linear(arr, 5); 
}
