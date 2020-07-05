#pragma once
#include <glad/glad.h>

#include <glad/glad.h>
#include "Buffer.h"
#include <iostream>
class VAO
{
private:
	unsigned int m_VAO;
public:
	inline VAO() {
		glCreateVertexArrays(1, &m_VAO);
	}
	inline ~VAO() { glDeleteVertexArrays(1, &m_VAO); }
	inline void Bind() const { glBindVertexArray(m_VAO); }
	void addAttrib(unsigned int index, int count, unsigned int type, bool normalized, unsigned int offset);
	void BindAttribs(Buffer& vbo, Buffer& indices, GLsizei elementSize);
};

