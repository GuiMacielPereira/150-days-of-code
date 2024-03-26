
#include <iostream>
#include <cmath>

int orderOfMagnitude(double num) {
    return (num == 0) ? 0 : static_cast<int>(floor(log10(fabs(num))));
}

int main () {
  int order = orderOfMagnitude(0.003453);
  std::cout << "order of mag: " << order << ", power: " <<  pow(10, 2 * order);
}
