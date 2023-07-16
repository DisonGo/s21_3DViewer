#include <godison/Matrices.h>

#include <iostream>
using namespace godison::matrices;
using std::cout;
int main() {
  SquareMatrix<4> test{1, 2, 3, 4, 5, 6, 7, 9, 9, 0, 1, 2, 3, 4, 5, 6};
  cout << test.Determinant();
}