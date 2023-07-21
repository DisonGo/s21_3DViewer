#include <godison/Matrices.h>
#include <godison/Point.h>

#include <QDebug>
#include <QMatrix4x4>
#include <iostream>

using namespace godison::matrices;
using namespace godison::vectors;
using std::cout;
struct bre{float a,b,c;};
std::ostream& operator<<(std::ostream& os, const QVector3D& v) {
  os << v.x() << " " << v.y() << " " << v.z() << " ";
  return os;
}
std::vector<Vector3D>& operator<<(std::vector<Vector3D>& arr,
                                  const Vector3D& vec) {
  arr.push_back(vec);
  return arr;
}
void print(unsigned a) {
  cout << a << " ";
}
int main() {
   unsigned offset = 10;
   print(offset -= 2);

}
