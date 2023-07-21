#include "GL/UBO.h"
namespace s21 {

void *UBO::GetBufferData(unsigned int offset, unsigned int count)
{
  void* buf = malloc(count);
  glGetBufferSubData(GetType(), offset, count, buf);
  return buf;
}

}
