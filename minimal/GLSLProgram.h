#pragma once
#include <string>
#include "GL/glew.h"

class GLSLProgram
{
public:
	GLSLProgram();

	void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
	// vertexShaderFilePath never get changed! const
	void linkShaders();
	void addAttribute(const std::string attributeName);

	GLint getUniformLocation(const std::string& uniformName);

	void use();
	void unuse();

private:
	int _numAttributes;
	void compileShader(const std::string& shaderFilePath, GLuint id);
	GLuint _programID;
	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;
};

