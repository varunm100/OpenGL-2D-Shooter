#pragma once
#include "VAO.h"
#include "Shader.h"
#include <array>
#include "TextureBuffer.h"

struct s_Vert {
	glm::vec3 pos;
	glm::vec2 tex;
};

class Quad
{
private:
	VAO m_VAO;
	Buffer m_VBO, m_IBO;
	TextureBuffer* m_Texture;
	Shader* m_Shader;
	float m_Width, m_Height;

public:
	std::array<s_Vert, 4> verts;
	std::array<unsigned int, 6> indices;

	Quad(Shader* shader, TextureBuffer* texBuffer, const glm::vec2& dimensions);
	~Quad() {
		m_VBO.~Buffer();
		m_IBO.~Buffer();
		m_VAO.~VAO();
	}
	inline const float getWidth() const { return m_Width; }
	inline const float getHeight() const { return m_Height; }
	void render(const glm::mat4& modelMatrix);
	void render(const char* modelUniformName, const glm::mat4& modelMatrix);
};

