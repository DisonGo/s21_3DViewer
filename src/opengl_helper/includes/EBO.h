#ifndef EBO_H_
#define EBO_H_
#include "opengl_helper.h"
class EBO {
	public:
    GLuint ID = -1;
    EBO();
    EBO(GLuint* indices, GLsizeiptr size);
    void BindIndices(GLuint* indices, GLsizeiptr size);
		void Bind();
		void Unbind();
		void Delete();
    ~EBO();
};

#endif // !EBO_H_

