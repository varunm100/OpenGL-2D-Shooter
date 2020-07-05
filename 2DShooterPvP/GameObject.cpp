#include "GameObject.h"

GameObject::GameObject(const int indexTextureToUse, const char* texSrc, bool flipTexOnLoad, glm::vec3 initialPosition, glm::vec2 dimensions, Shader* shader)
	: m_Shader{ shader }, m_Pos{ initialPosition }, m_Dimensions{ dimensions }
{
	m_Texture = new TextureBuffer(indexTextureToUse);
	m_Texture->uploadTextureData(texSrc, flipTexOnLoad);

	m_Quad = new Quad(m_Shader, m_Texture, m_Dimensions);

	m_Collision = false;
	m_Vel = glm::vec3(0.0f, 0.0f, 0.0f);
	m_VelGoal = glm::vec3(0.0f, 0.0f, 0.0f);
}

GameObject::~GameObject() {
	delete m_Texture;
	delete  m_Quad;
	delete m_Shader;
}

void GameObject::Update(float time) {
}

void GameObject::Render(float time) {
	Update(time);
	m_Quad->render(glm::scale(glm::translate(glm::mat4(1.0), m_Pos), glm::vec3(m_Dimensions.x, m_Dimensions.y, 0.0f)));
}

void GameObject::Render(float time, glm::mat4 modelMatrix) {
	Update(time);
	m_Quad->render(modelMatrix);
}

void GameObject::CheckCollision(GameObject* other, float boundryBuffer) {
	bool coll = ((m_Pos.x + m_Dimensions.x) >= other->m_Pos.x
		&& m_Pos.x <= (other->m_Pos.x + other->m_Dimensions.x)
		&& (m_Pos.y + m_Dimensions.y + boundryBuffer) >= other->m_Pos.y
		&& m_Pos.y <= (other->m_Pos.y + other->m_Dimensions.y - boundryBuffer));
	m_Collision = coll;
	other->m_Collision = coll;
}
