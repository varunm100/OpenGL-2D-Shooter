#pragma once
#include <glad/glad.h>

class Buffer {
private:
	unsigned int m_Buffer;
public:
	Buffer() { glCreateBuffers(1, &m_Buffer); }
	~Buffer() { glDeleteBuffers(1, &m_Buffer); }
	inline void uploadBufferData(GLsizeiptr size, const void* data, unsigned int usage) { glNamedBufferStorage(m_Buffer, size, data, usage); }
	inline unsigned int getBuffer() const { return m_Buffer; }
};