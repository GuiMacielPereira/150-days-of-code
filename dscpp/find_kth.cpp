#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


// Want algorithm to be nlog(n)


// Linear search function
vector<int> unique(const vector<int> &v) {

  vector<int> result {v[0]};

  for (int i=1; i < v.size(); i++){
    if (v[i] != v[i-1]){
      result.push_back(v[i]);
    }
  }
  return result;
}

// sort is nlog(n) and unique part is namespace 
// So in total its nlog(n)
int main() {
  vector<int> v {5, 5, 4, 5, 4, 6, 4, 3, 2, 1, 2 , 1, 5, 7, 7};
  sort(v.begin(), v.end());
  v = unique(v);
  cout << "\n";
  for (int i : v) cout << i; 
}
