#include <iostream>
#include <ctime>
#include <vector>
#include <unordered_map>
using namespace std;

int main() {

    for(int a = 10000; a < 1000001; a = a + 20000) {
        // Make vector 
        vector<int> avector;
        for( int i = 0; i < a; i++){
            avector.push_back(i);
        }
        // vector index operator
        clock_t begin = clock();
        for (int i=0; i<10000; i++) {
          int v = avector[i];
          avector[i] = v + 1;
        }
        clock_t end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

        // Make Hash Table
        unordered_map<int, int> y;
        for( int j = 0; j < a; j++ ){
            y[j] = j;
        }
        clock_t  begin_ht = clock();
        for (int i=0; i<10000; i++) {
          int v = y.find(i)->first;
          std::pair<int, int> pair (a+1, 5);
          y.insert(pair);
        }
        clock_t end_ht = clock();
        double elapsed_secs_ht = double(end_ht - begin_ht) / CLOCKS_PER_SEC;

        // Printing final output
        cout << a << "\t" << elapsed_secs << "\t" << elapsed_secs_ht << endl;
    }

    return 0;
}
