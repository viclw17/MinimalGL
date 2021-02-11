#include "GLSLProgram.h"
#include "Errors.h"
#include <fstream>

GLSLProgram::GLSLProgram():_numAttributes(0),_programID(0),_vertexShaderID(0),_fragmentShaderID(0) // init list
{

}

void GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
{
	_programID = glCreateProgram();

	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (_vertexShaderID == 0) {
		fatalError("vert shader fail");
	}

	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (_fragmentShaderID == 0) {
		fatalError("frag shader fail");
	}

	compileShader(vertexShaderFilePath, _vertexShaderID);
	compileShader(fragmentShaderFilePath, _fragmentShaderID);


}

void GLSLProgram::compileShader(const std::string& shaderFilePath, GLuint id)
{
	std::ifstream shaderFile(shaderFilePath);
	if (shaderFile.fail()) {
		perror(shaderFilePath.c_str());
		fatalError("failed on " + shaderFilePath);
	}
	std::string fileContents = "";
	std::string line;
	while (std::getline(shaderFile, line)) {
		fileContents += line + "\n";
	}
	shaderFile.close(); // fine, stack variable
	const char* contentsPtr = fileContents.c_str();
	glShaderSource(id, 1, &contentsPtr, nullptr);
	glCompileShader(id);
	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		//...
	}
}

void GLSLProgram::linkShaders()
{
	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);
	glLinkProgram(_programID);

	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE) {
		//...
	}

	glDetachShader(_programID, _vertexShaderID);
	glDetachShader(_programID, _fragmentShaderID);
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
}

void GLSLProgram::addAttribute(const std::string attributeName)
{
	glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str()); // ++
}

GLint GLSLProgram::getUniformLocation(const std::string& uniformName)
{
	GLint location = glGetUniformLocation(_programID, uniformName.c_str());
	if (location == GL_INVALID_INDEX)
	{
		fatalError("uniform not found");
	}
	return location;
}

void GLSLProgram::use()
{
	glUseProgram(_programID);
	for (int i = 0; i < _numAttributes; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

void GLSLProgram::unuse()
{
	glUseProgram(0);
	for (int i = 0; i < _numAttributes; i++)
	{
		glDisableVertexAttribArray(i);
	}
}
