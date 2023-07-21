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
int main() {
  std::vector<Vector3D> verices;
  verices << (Vector3D){1, 2, 3} << (Vector3D){4, 3, 3};
  const auto data = verices.data();
  auto v = sizeof(data[0]);
  auto b = sizeof(bre);
  for (size_t i = 0; i < verices.size(); ++i) cout << data[i] << "\n";
}
