#pragma once
#include <glad\glad.h>

class TextureBuffer
{
private:
	unsigned int m_Texture;
	const int m_Index;
public:
	TextureBuffer(const int texIndex) : m_Index{texIndex} { glCreateTextures(GL_TEXTURE_2D, 1, &m_Texture); }
	~TextureBuffer() { glDeleteTextures(1, &m_Texture); };
	
	void uploadTextureData(const char* src, bool flipVertical);
	inline const int getTextureIndex() { return m_Index; }
	inline unsigned int getTextureBuffer() { return m_Texture; }
	inline void setActiveTexture() { glBindTextureUnit(m_Index, m_Texture); }
};

