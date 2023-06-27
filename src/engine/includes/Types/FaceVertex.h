#ifndef FACEVERTEX_H
#define FACEVERTEX_H
#include <QOpenGLFunctions>
typedef struct {
  GLuint vIndex, tIndex, nIndex;
} FaceVertex;
#endif // FACEVERTEX_H