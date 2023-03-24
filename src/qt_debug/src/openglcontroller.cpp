#include "openglcontroller.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <QMouseEvent>

void OpenGLController::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        LMB_pressed = true;
        mPos = e->pos();

    }
}

void OpenGLController::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        LMB_pressed = false;
        mPos = e->pos();
    }
}
void OpenGLController::initShaders()
{
    program = Shader(":/vshader.glsl", ":/fshader.glsl");

}
void OpenGLController::initializeGL()
{
    initializeOpenGLFunctions();
    QSize window_size = this->size();
    float width = window_size.width();
    float height = window_size.height();
    float aspectRatio = width / height;
    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(FOV, aspectRatio, zNear, zFar);

    glClearColor(0,0,0,1);
    initShaders();
    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE);
    glEnable(GL_PROGRAM_POINT_SIZE);
    geometries = new GeometryEngine;
}

void OpenGLController::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    qreal aspectratio = qreal(w)/qreal(h ? h : 1);
    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(FOV, aspectratio, zNear, zFar);

}

void OpenGLController::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glClearColor(0, 0, 0, 1);
    program.Activate();
    QMatrix4x4 model, result;
    model.translate(0, 0, -6.0);
    result = model * projectionMatrix;
    GLint mat_location = glGetUniformLocation(program.ID, "mvp_matrix");
    qDebug() << "Matrix:" << mat_location;
    glUniformMatrix4fv(mat_location, 1, GL_FALSE, result.data());
    geometries->drawCubeGeometry(&program);
}
