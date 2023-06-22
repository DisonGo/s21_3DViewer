#pragma once
#include <vector>

#include "Normal.h"
#include "TextureCoord.h"
#include "TriangleFace.h"
#include "Face.h"
#include "Vertex.h"
using std::vector;
typedef struct {
  vector<Vertex> vertices;
  vector<TriangleFace> faces;
  vector<Face> edges;
  vector<Normal> normals;
  vector<TextureCoord> textureCoords;
} OBJ;
