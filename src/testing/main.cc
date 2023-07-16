#include <godison/Matrices.h>

#include <iostream>
using namespace godison::matrices;
using std::cout;
int main() {
  Matrix<2, 2> regular{1, 1, 2, 4, 4, 20, -12, 3, 0};
  SquareMatrix<2> test(regular);
  Matrix2x2 mat22 = test;
  mat22.SetToIdentity();
  cout << mat22 << "\n";
  cout << test.Invert();
}
