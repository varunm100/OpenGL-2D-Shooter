#include "VAO.h"

void VAO::addAttrib(unsigned int index, int count, unsigned int type, bool normalized, unsigned int offset) {
	glEnableVertexArrayAttrib(m_VAO, index);
	glVertexArrayAttribFormat(m_VAO, index, count, type, normalized, offset);
	glVertexArrayAttribBinding(m_VAO, index, 0);
}

void VAO::BindAttribs(Buffer& vbo, Buffer& indices, GLsizei vertexElementSize) {
	glVertexArrayVertexBuffer(m_VAO, 0, vbo.getBuffer(), 0, vertexElementSize);
	glVertexArrayElementBuffer(m_VAO, indices.getBuffer());
}