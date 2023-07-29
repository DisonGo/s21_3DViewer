#include <godison/Matrices.h>
#include <godison/Point.h>

#include <QDebug>
#include <QMatrix4x4>
#include <iostream>

using namespace godison::matrices;
using namespace godison::vectors;
using std::cout;
std::ostream& operator<<(std::ostream& os, const QVector3D& v) {
  os << v.x() << " " << v.y() << " " << v.z() << " ";
  return os;
}
void TranslateXViewTest();
void VectorsTesting();
void VectorsTesting() {
  QVector3D a({1, 2, 3});
  Vector3D b{1, 2, 3};

  QVector3D a1({-1, -2, -3});
  Vector3D b1{-1, -2, -3};
  cout << "Length:\n";
  cout << a.length() << "\n";
  cout << b.Length() << "\n";
  cout << "Normalized:\n";
  cout << a.normalized() << "\n";
  cout << b.Normalized() << "\n";
  cout << "Cross:\n";
  cout << a.crossProduct(a1, a) << "\n";
  cout << b1.CrossProduct(b) << "\n";
  cout << "Dot:\n";
  cout << a.dotProduct(a, a1) << "\n";
  cout << b.Dot(b1) << "\n";
}
int main() {
  //  VectorsTesting();
  TranslateXViewTest();
  // RotateTest();
  // ModelMatTest();
  // MultiTest();
  //  ViewTest();
}
// {{1, 3, 5}, {7, 2, 1}, {1, -2, 3}}
// {{3, 20, -2}, {0, 5, 10}, {-30, 90, 222}}

void TranslateXViewTest() {
  Vector3D at{0, 1, 0};
  Vector3D eye{1, 1, 1};
  Vector3D up{0, 1, 0};
  Matrix4x4 view;
  view.LookAt(eye, at, up);
  QMatrix4x4 viewQT;
  viewQT.lookAt({1, 1, 1}, {0, 1, 0}, {0, 1, 0});

  Matrix4x4 translateMat;
  QMatrix4x4 translateMatQT;
  // Vector3D translate {1, 2, 4};

  translateMat.SetToIdentity();
  translateMat.Translate({1, 2, 4});
  translateMatQT.translate({1, 2, 4});
  //  qDebug() << translateMatQT;

  Matrix4x4 persp;
  QMatrix4x4 perspQT;

  persp.Perspective(45, 1920.f / 1080.f, 0.001, 2000);
  perspQT.perspective(45, 1920.f / 1080.f, 0.001, 2000);

  auto data = (viewQT * perspQT * translateMatQT).data();
  for (int i = 0; i < 16; ++i) cout << std::setprecision(6) << data[i] << " ";
  cout << "\n";
  auto my_data = (translateMat * persp * view).Data();
  for (int i = 0; i < 16; ++i)
    cout << std::setprecision(6) << my_data[i] << " ";

  cout << "\n";
  cout << "\n";

  data = (perspQT).data();
  for (int i = 0; i < 16; ++i) cout << std::setprecision(6) << data[i] << " ";
  cout << "\n";
  my_data = (persp).Data();
  for (int i = 0; i < 16; ++i)
    cout << std::setprecision(6) << my_data[i] << " ";
}
// void RotateTest() {
//   Matrix4x4 rotateMat;
//   QMatrix4x4 rotateMatQT;
//   rotateMat.SetToIdentity();

//  rotateMat.Rotate(15, {1, 0, 0});
//  rotateMatQT.rotate(15, {1, 0, 0});
//  auto data = (rotateMatQT).data();
//  for (int i = 0; i < 16; ++i) cout << std::setprecision(6) << data[i] << " ";
//  cout << "\n";
//  auto my_data = (rotateMat).Data();
//  for (int i = 0; i < 16; ++i)
//    cout << std::setprecision(6) << my_data[i] << " ";
//}
// void ModelMatTest() {
//  Vector3D scale_ = Vector3D(1, 1, 1);
//  Vector3D rotation_ = Vector3D(16, 0, 0);
//  Vector3D translate_ = Vector3D(0, 23, 1);

//  QVector3D scale_QT = QVector3D(1, 1, 1);
//  QVector3D translate_QT = QVector3D(0, 0, 0);

//  QMatrix4x4 modelScale_QT;
//  QMatrix4x4 modelRot_QT;
//  QMatrix4x4 modelTranslate_QT;

//  Matrix4x4 modelScale_;
//  Matrix4x4 modelRot_;
//  Matrix4x4 modelTranslate_;

//  modelScale_.SetToIdentity();
//  modelRot_.SetToIdentity();
//  modelTranslate_.SetToIdentity();

//  modelRot_QT.rotate(rotation_.X(), 1, 0, 0);
//  modelRot_QT.rotate(rotation_.Y(), 0, 1, 0);
//  modelRot_QT.rotate(rotation_.Z(), 0, 0, 1);

//  modelRot_.Rotate(rotation_.X(), {1, 0, 0});
//  modelRot_.Rotate(rotation_.Y(), {0, 1, 0});
//  modelRot_.Rotate(rotation_.Z(), {0, 0, 1});

//  modelTranslate_QT.translate(translate_QT);
//  modelTranslate_.Translate(translate_);

//  modelScale_QT.scale(scale_QT);
//  modelScale_.Scale(scale_);
//  qDebug() << (modelTranslate_QT * modelRot_QT * modelScale_QT);
//  auto data = (modelTranslate_QT * modelRot_QT * modelScale_QT).constData();
//  for (int i = 0; i < 16; ++i) cout << std::setprecision(6) << data[i] << " ";
//  cout << "\n";
//  auto my_data = (modelTranslate_ * modelRot_ * modelScale_).Data();
//  for (int i = 0; i < 16; ++i)
//    cout << std::setprecision(6) << my_data[i] << " ";
//}
// void MultiTest() {
//  Matrix3x3 a{1, 3, 5, 7, 2, 1, 1, -2, 3};
//  Matrix3x3 b{3, 20, -2, 0, 5, 10, -30, 90, 222};
//  cout << a * b << "\n";
//  // QMatrix2x2 a1(1, 3, 5, 7);
//  // QMatrix2x2 b1(3, 20, -2, 0);
//  // qDebug() << a1 * b1;
//}
// void ViewTest() {
//  Matrix4x4 persp;
//  persp.SetToIdentity();
//  QMatrix4x4 perspQT;
//  persp.Perspective(45, 1024.f / 720.f, 0.0001, 1000);
//  perspQT.perspective(45, 1024.f / 720.f, 0.0001, 1000);
//  qDebug() << perspQT;
//  cout << persp;

//}
