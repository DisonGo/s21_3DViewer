#ifndef OBJ_H
#define OBJ_H
#include <vector>

#include "Face.h"
#include "Normal.h"
#include "TextureCoord.h"
#include "TriangleFace.h"
#include "Vertex.h"
using std::vector;
typedef struct {
  vector<Vertex> vertices;
  vector<TriangleFace> faces;
  vector<Face> edges;
  vector<Normal> normals;
  vector<TextureCoord> textureCoords;
} OBJ;

<<<<<<< HEAD
#endif  // OBJ_H
=======
#endif // OBJ_H
>>>>>>> origin/develop
