#include "Quad.h"

Quad::Quad(Shader* shader, TextureBuffer* texBuffer, const glm::vec2& dimensions)
{
	m_Texture = texBuffer;
	m_Width = dimensions.x, m_Height = dimensions.y;

	m_Shader = shader;

	verts = { {
		{ glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) },
		{ glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f) },
		{ glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f) },
		{ glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f) }
	} };
	
	indices = {
		0, 1, 2,
		0, 2, 3,
	};

	m_VBO.uploadBufferData(sizeof(verts), verts.data(), GL_DYNAMIC_STORAGE_BIT);
	m_IBO.uploadBufferData(sizeof(indices), indices.data(), GL_DYNAMIC_STORAGE_BIT);

	m_VAO.addAttrib(0, 3, GL_FLOAT, GL_FALSE, offsetof(s_Vert, pos));
	m_VAO.addAttrib(1, 2, GL_FLOAT, GL_FALSE, offsetof(s_Vert, tex));

	m_VAO.BindAttribs(m_VBO, m_IBO, sizeof(s_Vert));
}

void Quad::render(const char* modelUniformName, const glm::mat4& modelMatrix) {
	m_Texture->setActiveTexture();  // wrapper for glBindTextureUnit()

	m_Shader->Use(); // use shader

	m_Shader->setUniformMatrix4(modelUniformName, modelMatrix);
	m_Shader->setUniformInt1("quadTexture", (*m_Texture).getTextureIndex());
	m_VAO.Bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}

void Quad::render(const glm::mat4& modelMatrix) {
	m_Texture->setActiveTexture();  // wrapper for glBindTextureUnit()

	m_Shader->Use(); // use shader

	m_Shader->setUniformMatrix4("model", modelMatrix);
	m_Shader->setUniformInt1("quadTexture", (*m_Texture).getTextureIndex());
	m_VAO.Bind();
	m_VAO.BindAttribs(m_VBO, m_IBO, sizeof(s_Vert));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}
