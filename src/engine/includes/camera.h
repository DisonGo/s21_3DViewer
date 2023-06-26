#ifndef CAMERA_H
#define CAMERA_H
#include <QOpenGLFunctions>
#include <QVector3D>

#include "E/EObject.h"
#include "shader.h"

class Camera : public EObject, protected QOpenGLFunctions {
 public:
  friend class CameraConfig;
  friend class CameraSpacer;
  explicit Camera();
  Camera(int width, int height);
  EObjectType type = EObjectType::kCamera;
  enum CameraMode { Free = 0, Focus = 1 };
  enum ViewMode { Perspective = 0, Orthographic = 1 };
  class ParallelBox {
   public:
    ParallelBox(float vertical, float horizontal)
        : top(vertical),
          right(horizontal),
          bottom(vertical),
          left(horizontal){};
    ParallelBox(float top = 1, float right = 1, float bottom = -1,
                float left = -1)
        : top(top), right(right), bottom(bottom), left(left){};
    float top = 1;
    float right = 1;
    float bottom = -1;
    float left = -1;
  };
  class CameraConfig {
   public:
    //    CameraConfig() = delete;
    CameraConfig(Camera &camera)
        : viewMode(camera.viewMode),
          Mode(camera.mode),
          FocusPoint(camera.FocusPoint),
          Position(camera.Position),
          Orientation(camera.Orientation),
          zRange(camera.zRange),
          FOV(camera.FOV),
          box(camera.box){};
    ViewMode &viewMode;
    CameraMode &Mode;
    QVector3D &FocusPoint;
    QVector3D &Position;
    QVector3D &Orientation;
    QVector2D &zRange;
    float &FOV;
    ParallelBox &box;
  };

  void Matrix(Shader &shader, const char *uniform);
  CameraConfig &GetConfig() { return config_; };

 public:  // Setters / Getters
  void SetMode(CameraMode newMode);
  void SetViewMode(ViewMode newViewMode);
  void SetFocusPoint(const QVector3D &newFocusPoint);
  void SetPosition(const QVector3D &newPosition);
  void SetOrientation(const QVector3D &newOrientation);
  void SetZRange(const QVector2D &newZRange);
  void SetFOV(float newFOV);
  void SetVw(int newVw);
  void SetVh(int newVh);
  void SetMoveSpeed(float newMoveSpeed);
  void SetRotationSpeed(float newRotationSpeed);

 private:  // Methods
  void processFreeMode(QPoint ePos);
  void processFocusMode(QPoint focusPoint);

 private:  // vars
  CameraConfig config_;
  CameraMode mode = Free;
  ViewMode viewMode = Perspective;
  QVector3D FocusPoint = QVector3D(0, 0, 0);
  QVector3D Position = QVector3D(0, 0, 0);
  QVector3D Orientation = QVector3D(0, 0, 1);
  QVector2D zRange = QVector2D(0.001, 100);

  QVector3D Up = QVector3D(0.0f, 1.0f, 0.0f);
  float FOV = 60;

  bool LMBPressed = false;
  int vw = 1;
  int vh = 1;
  QPoint mCenterPos = QPoint(0, 0);
  float moveSpeed = 0.1f;
  float rotationSpeed = 0.1f;
  ParallelBox box{};
};

#endif  // CAMERA_H
