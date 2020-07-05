#pragma once
#include "GameObject.h"
#include "Window.h"

class Player :
    public GameObject
{
private:
    const float m_Gravity = 900.0f;
    const float m_lerpInterpolation = 0.1f;
    const float m_lerpInterpolationJump = 0.1f;
    const float m_maxSpeed = 500.0f;
    const float m_jumpHeight = 500.0f;
    const float m_bulletSpeed = 1000.0f;
    
    GameObject* m_Gun;
    
    vector<float> m_ProjectileAngles;
public:
    vector<GameObject*> m_Projectiles;

    Player(const int indexTextureToUse, const char* texSrc, bool flipTexOnLoad, glm::vec3 initialPosition, glm::vec2 dimensions, Shader* shader, GameObject* gun)
        : GameObject(indexTextureToUse, texSrc, flipTexOnLoad, initialPosition, dimensions, shader)
    {
        m_Gun = gun;
    }
    ~Player() {}

    void HandleKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods);
    void HandleMouseInput(GLFWwindow* window, int button, int action, int mods);
    void Update(float time);
    void Render(float time, GLFWwindow* window);
    void CheckCollision(GameObject* other, float boundryBuffer);
    void InstantiateBullet(glm::vec3 initialPos, glm::vec3 bulletDirVector, float theta);
};

