#ifndef CAMERA_H
#define CAMERA_H
#include <QOpenGLFunctions>
#include <QObject>
#include "shader.h"
#include <QVector3D>
#include <QKeyEvent>
struct CameraData {
  QPoint centerPoint;
  QPoint relevantPoint;
  float rotX;
  float rotY;
  float angle;
  float speed;
  QVector3D orientation;
  QVector3D position;
};

class Camera : public QObject , protected QOpenGLFunctions
{
  Q_OBJECT
public:
  explicit Camera(QObject *parent = nullptr);

  enum CameraMode {
    Free = 0,
    Focus = 1
  };
  enum ViewMode {
    Perspective = 0,
    Orthographic = 1
  };

  struct CameraConfig {
    ViewMode viewMode = Perspective;
    CameraMode Mode = Free;
    QVector3D FocusPoint = QVector3D(0,0,0);
    QVector3D Position = QVector3D(0,0,0);
    QVector3D Orientation = QVector3D(0,0,1);
    QVector2D zRange = QVector2D(0.001, 100);
    float FOV = 60;
  };

  Camera(int width, int height, QObject *parent = nullptr);
  void Matrix(Shader& shader, const char* uniform);

public slots:
  void keyPressSlot(QKeyEvent *e);
  void keyReleaseSlot(QKeyEvent *e);
  void mousePressSlot(QMouseEvent *e);
  void mouseReleaseSlot(QMouseEvent *e);
  void mouseMoveSlot(QMouseEvent *e);
  void wheelSlot(QWheelEvent *e);
public: // Setters / Getters
  void SetConfig(CameraConfig config);

  void setMode(CameraMode newMode);
  void setViewMode(ViewMode newViewMode);
  void setFocusPoint(const QVector3D &newFocusPoint);
  void setPosition(const QVector3D &newPosition);
  void setOrientation(const QVector3D &newOrientation);
  void setZRange(const QVector2D &newZRange);
  void setFOV(float newFOV);
  void setVw(int newVw);
  void setVh(int newVh);
  void setMoveSpeed(float newMoveSpeed);
  void setRotationSpeed(float newRotationSpeed);

private: // Methods
  void processFreeMode(QPoint ePos);
  void processFocusMode(QPoint focusPoint);
private: // vars
  CameraConfig config;
  CameraMode mode = config.Mode;
  ViewMode viewMode = config.viewMode;
  QVector3D FocusPoint = config.FocusPoint;
  QVector3D Position = config.Position;
  QVector3D Orientation = config.Orientation;
  QVector3D Up = QVector3D(0.0f, 1.0f, 0.0f);

  QVector2D zRange = config.zRange;
  float FOV = config.FOV;

  bool LMBPressed = false;
  int vw = 1;
  int vh = 1;
  QPoint mCenterPos = QPoint(0,0);
  float moveSpeed = 0.1f;
  float rotationSpeed = 0.1f;

signals:
  void dataUpdated(CameraData data);
};

#endif // CAMERA_H
