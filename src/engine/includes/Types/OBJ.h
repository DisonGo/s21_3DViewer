#pragma once
#include <vector>
#include "Vertex.h"
#include "Face.h"
#include "Normal.h"
#include "TextureCoord.h"
using std::vector;
typedef struct {
  vector<Vertex> vertices;
  vector<Face> faces;
  vector<Normal> normals;
  vector<TextureCoord> textureCoords;
} OBJ;
