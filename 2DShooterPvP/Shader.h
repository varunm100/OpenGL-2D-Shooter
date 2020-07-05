#pragma once
#include <glad/glad.h>
#include "ShaderFileParser.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
private:
	unsigned int m_Program;
public:
	Shader();
	~Shader();
	inline unsigned int getProgram() const { return m_Program; }
	inline void Use() const { glUseProgram(m_Program); }
	void compileShader(const char* vertexShaderSource, const char* fragmentShaderSource);
	void compileShader(string filePath);
	
	inline void setUniformMatrix4(const char* uniform, const glm::mat4& matrix) {
		glUniformMatrix4fv(glGetUniformLocation(m_Program, uniform), 1, GL_FALSE, glm::value_ptr(matrix));
	}
	inline void setUniformInt1(const char* uniform, const int integer) {
		glUniform1i(glGetUniformLocation(m_Program, uniform), integer);
	}
};

