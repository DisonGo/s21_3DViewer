#include <godison/Matrices.h>

#include <QDebug>
#include <QMatrix4x4>
#include <iostream>
using namespace godison::matrices;
using namespace godison::vectors;
using std::cout;
int main() {
  Vector3D at{0, 1, 0};
  Vector3D eye{1, 1, 1};
  Vector3D up{0, 1, 0};
  Matrix4x4 view;
  view.LookAt(eye, at, up);
  cout << view;
  QMatrix4x4 viewQT;
  viewQT.lookAt({1, 1, 1}, {0, 1, 0}, {0, 1, 0});
  qDebug() << viewQT;
}
