#ifndef OPENGLCONTROLLER_H
#define OPENGLCONTROLLER_H

#include <QObject>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <QTimer>
#include <QMatrix4x4>
#include <QSurfaceFormat>
#include "geometryengine.h"
#include "shader.h"
class OpenGLController : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    using QOpenGLWidget::QOpenGLWidget;
//    OpenGLController(const , QWidget* parent);
//    ~OpenGLController();
protected:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
//    void timerEvent(QTimerEvent *e) override;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

//    void initShaders();
//    void initTextures();
private:
    QPoint mPos = QPoint(0,0);

    bool LMB_pressed = false;
    bool RMB_pressed = false;

    QString filename;

    float xRot = 0, yRot = 0, zRot = 0;
    float xShift = 0, yShift = 0, zShift = 0;

    qreal zNear = 3.0, zFar = 7.0, FOV = 45.0f;

    float color_back_r = 255, color_back_g = 0, color_back_b = 0;
    float color_facet_r = 0, color_facet_g = 0, color_facet_b = 0;
    int width_line = 1;
    QMatrix4x4 projectionMatrix; // Store the projection matrix
//    glm::mat4 viewMatrix; // Store the view matrix
//    glm::mat4 modelMatrix; // Store the model matrix
    Shader program;
    GeometryEngine *geometries = nullptr;
    void initShaders();
};

#endif // OPENGLCONTROLLER_H
