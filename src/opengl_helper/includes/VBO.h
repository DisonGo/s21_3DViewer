#ifndef VBO_H_
#define VBO_H_
#include "opengl_helper.h"
class VBO {
	public:
    GLuint ID = -1;
    VBO();
		VBO(GLfloat* vertices, GLsizeiptr size);
    void BindVertices(GLfloat* vertices, GLsizeiptr size);
		void Bind();
		void Unbind();
		void Delete();
    ~VBO();
};
#endif // !VBO_H_
