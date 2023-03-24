#ifndef SHADER_CLASS_H_
#define SHADER_CLASS_H_
#define GL_SILENCE_DEPRECATION
#include <QtOpenGL>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
class Shader
{
	public:
        enum ShaderType {
            Vertex = 0,
            Fragment
        };
		GLuint ID;
        Shader();
		Shader(const char* vertexFile, const char* fragmentFile);


		void Activate();
        void Delete();
private:
        QString getFileContent(const char *fileName);
        const char* vertexFileName;
        const char* fragmentFileName;
        void PrintShaderError(int obj, const char *fileName);
        void Check_compilation(int id, ShaderType type);
        bool CompileSuccessful(int obj);
        bool LinkSuccessful(int obj);
        void PrintProgramError(int obj);
};

#endif
