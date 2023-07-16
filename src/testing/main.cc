#include <godison/Matrices.h>

#include <iostream>
using namespace godison::matrices;
using std::cout;
int main() {
  Matrix<3, 3> regular{1, 1, 2, 4, 4, 20, -12, 3, 0};
  SquareMatrix<3> test(regular);
  SquareMatrix<3> test2 = std::move(test);
  cout << test2.Invert() << "\n";
  cout << test.Invert();
}
