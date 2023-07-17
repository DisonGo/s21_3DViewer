#include <godison/Matrices.h>
#include <godison/Point.h>

#include <QDebug>
#include <QMatrix4x4>
#include <iostream>

using namespace godison::matrices;
using namespace godison::vectors;
using std::cout;
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

  // FIXME Not coresponding answers on view x translate
  auto data = (viewQT * translateMatQT).data();
  for (int i = 0; i < 16; ++i) cout << std::setprecision(6) << data[i] << " ";
  cout << "\n";
  auto my_data = (view * translateMat).Data();
  for (int i = 0; i < 16; ++i)
    cout << std::setprecision(6) << my_data[i] << " ";
}
void RotateTest() {
  Matrix4x4 rotateMat;
  QMatrix4x4 rotateMatQT;
  rotateMat.SetToIdentity();

  rotateMat.Rotate(15, {1, 0, 0});
  rotateMatQT.rotate(15, {1, 0, 0});
  auto data = (rotateMatQT).data();
  for (int i = 0; i < 16; ++i) cout << std::setprecision(6) << data[i] << " ";
  cout << "\n";
  auto my_data = (rotateMat).Data();
  for (int i = 0; i < 16; ++i)
    cout << std::setprecision(6) << my_data[i] << " ";
}
void ModelMatTest() {
  Vector3D scale_ = Vector3D(1, 1, 1);
  Vector3D rotation_ = Vector3D(16, 0, 0);
  Vector3D translate_ = Vector3D(0, 23, 1);

  QVector3D scale_QT = QVector3D(1, 1, 1);
  QVector3D translate_QT = QVector3D(0, 0, 0);

  QMatrix4x4 modelScale_QT;
  QMatrix4x4 modelRot_QT;
  QMatrix4x4 modelTranslate_QT;

  Matrix4x4 modelScale_;
  Matrix4x4 modelRot_;
  Matrix4x4 modelTranslate_;

  modelScale_.SetToIdentity();
  modelRot_.SetToIdentity();
  modelTranslate_.SetToIdentity();

  modelRot_QT.rotate(rotation_.X(), 1, 0, 0);
  modelRot_QT.rotate(rotation_.Y(), 0, 1, 0);
  modelRot_QT.rotate(rotation_.Z(), 0, 0, 1);

  modelRot_.Rotate(rotation_.X(), {1, 0, 0});
  modelRot_.Rotate(rotation_.Y(), {0, 1, 0});
  modelRot_.Rotate(rotation_.Z(), {0, 0, 1});

  modelTranslate_QT.translate(translate_QT);
  modelTranslate_.Translate(translate_);

  modelScale_QT.scale(scale_QT);
  modelScale_.Scale(scale_);
  qDebug() << (modelTranslate_QT * modelRot_QT * modelScale_QT);
  auto data = (modelTranslate_QT * modelRot_QT * modelScale_QT).constData();
  for (int i = 0; i < 16; ++i) cout << std::setprecision(6) << data[i] << " ";
  cout << "\n";
  auto my_data = (modelTranslate_ * modelRot_ * modelScale_).Data();
  for (int i = 0; i < 16; ++i)
    cout << std::setprecision(6) << my_data[i] << " ";
}
void MultiTest() {
  Matrix3x3 a{1, 3, 5, 7, 2, 1, 1, -2, 3};
  Matrix3x3 b{3, 20, -2, 0, 5, 10, -30, 90, 222};
  cout << a * b << "\n";
  // QMatrix2x2 a1(1, 3, 5, 7);
  // QMatrix2x2 b1(3, 20, -2, 0);
  // qDebug() << a1 * b1;
}
int main() {
  godison::Point point;
  Matrix4x4 a;
  a.SetToIdentity();
  a.Perspective(45, 1024.f / 720.f, 0.0001, 1000);
  cout << a;
  // TranslateXViewTest();
  // RotateTest();
  // ModelMatTest();
  // MultiTest();
}
// {{1, 3, 5}, {7, 2, 1}, {1, -2, 3}}
// {{3, 20, -2}, {0, 5, 10}, {-30, 90, 222}}