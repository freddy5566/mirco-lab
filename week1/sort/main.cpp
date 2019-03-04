#include <iostream>
#include "sort.h"
using namespace std;

int main() {

  int array[10] = {};

  for (int i = 0; i < 10; i++) {
    cin >> array[i];
  }
  
  quickSort(array, 0, 9);
  
  cout << "------output------" << endl;
  for (int a : array) {
    cout << a << endl;
  }

  return 0;
}
