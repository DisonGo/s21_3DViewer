#include <godison/Matrices.h>
#include <iostream>
using namespace godison::matrices;
using std::cout;
int main() {
  SquareMatrix<3> test{1,2,3,4,5,6,7,8,9};
  // test.SwapRows(0, 1);
  cout << test.Determinant();
}