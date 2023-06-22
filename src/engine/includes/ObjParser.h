#pragma once
#include "Types/OBJ.h"
class ObjParser
{
public:
  static OBJ Parse(std::string filePath);
  static OBJ ParseEdges(std::string filePath);
private:
};



