#include "shader.h"
#include "QDebug"

QString Shader::getFileContent(const char* fileName) {
    QFile shader_file(fileName);
    if(!shader_file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Cannot open shader file " << fileName;
        return "";
    }
    QString shader_content = QString::fromUtf8(shader_file.readAll());
    return shader_content;
}

Shader::Shader()
{
    ID = -1;
}

Shader::Shader(const char* vertexFile, const char* fragmentFile) {
    vertexFileName = vertexFile;
    fragmentFileName = fragmentFile;
    std::string vertexCode = getFileContent(vertexFile).toStdString();
    std::string fragmentCode = getFileContent(fragmentFile).toStdString();

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
    Check_compilation(vertexShader, Vertex);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
    Check_compilation(fragmentShader, Fragment);

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
    if (!LinkSuccessful(ID)) {
        qDebug() << "Shader linking failed";
        PrintProgramError(ID);
    }
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
bool Shader::LinkSuccessful(int obj) {
  int status;
  glGetProgramiv(obj, GL_LINK_STATUS, &status);
  return status == GL_TRUE;
}
bool Shader::CompileSuccessful(int obj) {
  int status;
  glGetShaderiv(obj, GL_COMPILE_STATUS, &status);
  return status == GL_TRUE;
}
void Shader::PrintShaderError(int obj, const char* fileName) {
    GLint maxLength = 0;
    glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &maxLength);
    std::vector<GLchar> errorLog(maxLength);
    glGetShaderInfoLog(obj, maxLength, &maxLength, &errorLog[0]);
    qDebug() << fileName << ":";
    qDebug() << errorLog.data();
}
void Shader::PrintProgramError(int obj) {
    GLint maxLength = 0;
    glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &maxLength);
    std::vector<GLchar> errorLog(maxLength);
    glGetProgramInfoLog(obj, maxLength, &maxLength, &errorLog[0]);
    qDebug() << "Program id:" << obj;
    qDebug() << errorLog.data();
}
void Shader::Check_compilation(int id, ShaderType type) {
    const char* fileName = type == Vertex ? vertexFileName : fragmentFileName;
    if (!CompileSuccessful(id))
        PrintShaderError(id, fileName);

}
void Shader::Activate() {
	glUseProgram(ID);
}
void Shader::Delete() {
	glDeleteProgram(ID);
}
