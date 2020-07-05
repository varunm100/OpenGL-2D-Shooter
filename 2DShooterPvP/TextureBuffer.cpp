#include "TextureBuffer.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
void TextureBuffer::uploadTextureData(const char* src, bool flipVertical)
{
	glTextureParameteri(m_Texture, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(m_Texture, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTextureParameteri(m_Texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTextureParameteri(m_Texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(flipVertical);
	int width, height, numChannels;
	unsigned char* textureData = stbi_load(src, &width, &height, &numChannels, 4);
	setActiveTexture();
	if (textureData) {
		glTextureStorage2D(m_Texture, 1, GL_RGBA8, width, height);
		glTextureSubImage2D(m_Texture, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
		glGenerateTextureMipmap(m_Texture);
	} else {
		printf(": Failed to Load Texture Data\n");
	}
	stbi_image_free(textureData);
}
