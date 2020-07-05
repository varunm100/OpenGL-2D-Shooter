#include "Player.h"

void Player::HandleKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		m_VelGoal.y = -m_jumpHeight;
	if (key == GLFW_KEY_A && action == GLFW_RELEASE)
		m_VelGoal.x = 0;
	if (key == GLFW_KEY_D && action == GLFW_RELEASE)
		m_VelGoal.x = 0;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		m_VelGoal.x = m_maxSpeed;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_D) == GLFW_REPEAT)
			m_VelGoal.x = -m_maxSpeed;
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		m_VelGoal.x = -m_maxSpeed;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_A) == GLFW_REPEAT)
			m_VelGoal.x = m_maxSpeed;
	}
	if (key == GLFW_KEY_W && action == GLFW_RELEASE)
		m_VelGoal.y = 0;
}

void Player::HandleMouseInput(GLFWwindow* window, int button, int action, int mods) {
	double xpos;
	double ypos;
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && action != GLFW_REPEAT) {
		glfwGetCursorPos(window, &xpos, &ypos);
		float theta = glm::atan(ypos - m_Pos.y, xpos - m_Pos.x);
		glm::vec3 initialBulletPos(m_Pos.x + (0.5f * m_Dimensions.x) + (glm::cos(theta) * m_Gun->m_Dimensions.x), m_Pos.y + (0.5f * m_Dimensions.y) + (glm::sin(theta) * m_Gun->m_Dimensions.x), 0.0f);
		InstantiateBullet(initialBulletPos, glm::vec3(xpos - m_Pos.x, ypos - m_Pos.y, 0.0f), theta);
	} else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS && action != GLFW_REPEAT) {
		glfwGetCursorPos(window, &xpos, &ypos);
		float theta = glm::atan(ypos - m_Pos.y, xpos - m_Pos.x);
		glm::vec3 initialBulletPos(m_Pos.x + (0.5f * m_Dimensions.x) + (glm::cos(theta) * m_Gun->m_Dimensions.x), m_Pos.y + (0.5f * m_Dimensions.y) + (glm::sin(theta) * m_Gun->m_Dimensions.x), 0.0f);
		InstantiateBullet(initialBulletPos, glm::vec3(xpos - m_Pos.x, ypos - m_Pos.y, 0.0f), theta);
	}
}

void Player::Update(float dt) {
	for (GameObject* projectile : m_Projectiles) {
		projectile->m_Pos = projectile->m_Pos + (projectile->m_Vel * dt * m_bulletSpeed);
	}

	float gravity = 0.0f;
	if (!m_Collision) {
		gravity = m_Gravity;
	}
	else {
		m_Vel.y = glm::mix(m_VelGoal.y, m_Vel.y, dt * m_lerpInterpolationJump);
	}
	m_Vel.x = glm::mix(m_VelGoal.x, m_Vel.x, dt * m_lerpInterpolation);
	m_Pos = m_Pos + m_Vel * dt;
	m_Vel = m_Vel + (glm::vec3(0.0f, gravity, 0.0f) * dt);
	m_Gun->m_Pos = glm::vec3(m_Pos.x+(m_Dimensions.x*0.5f), m_Pos.y+(m_Dimensions.y*0.5f), 0.0f);
}

void Player::Render(float dt, GLFWwindow* window) {
	Update(dt);
	
	double xpos;
	double ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	float theta = glm::atan(ypos - m_Pos.y, xpos - m_Pos.x);
	glm::mat4 gunModelMatrix = glm::mat4(1.0);
	gunModelMatrix = glm::translate(gunModelMatrix, glm::vec3(m_Pos.x + (0.5f * m_Dimensions.x), m_Pos.y + (0.5f * m_Dimensions.y), 0.0f));
	gunModelMatrix = glm::rotate(gunModelMatrix, theta, glm::vec3(0.0f, 0.0f, 1.0f));
	gunModelMatrix = glm::translate(gunModelMatrix, glm::vec3(0.0f, -0.5f * m_Gun->m_Dimensions.y, 0.0f));
	gunModelMatrix = glm::scale(gunModelMatrix, glm::vec3(m_Gun->m_Dimensions.x, m_Gun->m_Dimensions.y, 0.0f));

	glm::mat4 bulletModelMatrix;
	cout << m_Projectiles.size() << " " << m_ProjectileAngles.size() << endl;
	for (int i = 0; i < m_Projectiles.size(); ++i) {
		GameObject* projectile = m_Projectiles[i];
		if (!projectile->isOutOfBounds() && !projectile->m_Collision) {
			bulletModelMatrix = glm::mat4(1.0);
			bulletModelMatrix = glm::translate(bulletModelMatrix, projectile->m_Pos);
			bulletModelMatrix = glm::rotate(bulletModelMatrix, m_ProjectileAngles[i], glm::vec3(0.0f, 0.0f, 1.0f));
			bulletModelMatrix = glm::translate(bulletModelMatrix, glm::vec3(0.0f, -0.5f * projectile->m_Dimensions.y, 0.0f));
			bulletModelMatrix = glm::scale(bulletModelMatrix, glm::vec3(projectile->m_Dimensions.x, projectile->m_Dimensions.y, 0.0f));
			projectile->Render(dt, bulletModelMatrix);
		}
		else {
			m_Projectiles.erase(m_Projectiles.begin() + i);
			m_ProjectileAngles.erase(m_ProjectileAngles.begin() + i);
		}
	}
	m_Gun->Render(dt, gunModelMatrix);
	m_Quad->render(glm::scale(glm::translate(glm::mat4(1.0), m_Pos), glm::vec3(m_Dimensions.x, m_Dimensions.y, 0.0f)));
}

void Player::CheckCollision(GameObject* other, float boundryBuffer) {
	bool coll = ((m_Pos.x + m_Dimensions.x) >= other->m_Pos.x
		&& m_Pos.x <= (other->m_Pos.x + other->m_Dimensions.x)
		&& (m_Pos.y + m_Dimensions.y + boundryBuffer) >= other->m_Pos.y
		&& m_Pos.y <= (other->m_Pos.y + other->m_Dimensions.y - boundryBuffer));
	m_Collision = coll;
	other->m_Collision = coll;
}

void Player::InstantiateBullet(glm::vec3 initialPos, glm::vec3 bulletDirVector, float theta) {
	GameObject* bullet = new GameObject(0, "C:/Users/varun/Pictures/Saved Pictures/RubberTexture.jpg", false, initialPos, glm::vec2(60.0f, 25.0f), m_Shader);
	m_ProjectileAngles.push_back(theta);

	float magnitude = glm::sqrt(glm::pow(bulletDirVector.x, 2) + glm::pow(bulletDirVector.y, 2));
	bulletDirVector = bulletDirVector/magnitude;
	bullet->m_Vel = bulletDirVector;
	m_Projectiles.push_back(bullet);
}