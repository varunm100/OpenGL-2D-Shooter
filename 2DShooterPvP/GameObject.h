#pragma once
#include "Quad.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GameObject
{
private:
	Quad* m_Quad;
	TextureBuffer* m_Texture;
	Shader* m_Shader;

	glm::vec3 m_Pos;
	glm::vec2 m_Dimensions;
	glm::vec3 m_Vel;
	glm::vec2 m_VelGoal;

	friend class Player;
public:
	bool m_Collision;


	GameObject(const int indexTextureToUse, const char* texSrc, bool flipTexOnLoad, glm::vec3 initialPosition, glm::vec2 dimensions, Shader* shader);
	~GameObject();

	void Update(float time);
	void Render(float time);
	void Render(float time, glm::mat4 modelMatrix);

	inline bool isOutOfBounds() const { return (m_Pos.x < 0 || m_Pos.x > 1920 || m_Pos.y < 0 || m_Pos.y > 1080); }
	void CheckCollision(GameObject* other, float boundryBuffer);
};

