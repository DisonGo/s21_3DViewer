#pragma once
#include <vector>

#include "Normal.h"
#include "TextureCoord.h"
#include "TriangleFace.h"
#include "Vertex.h"
using std::vector;
typedef struct {
  vector<Vertex> vertices;
  vector<TriangleFace> faces; 
  vector<Normal> normals;
  vector<TextureCoord> textureCoords;
} OBJ;
