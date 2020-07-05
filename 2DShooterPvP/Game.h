#pragma once
#include "Window.h"
#include "Shader.h"
#include "GameObject.h"
#include "Player.h"

class Game :
	public Window
{
private:
	vector<GameObject*> m_Objects;
	Player* m_Player;
public:

	Game(const int width, const int height, const char* title, bool vsync);
	inline ~Game() { for (auto object : m_Objects) { delete object; } delete m_Player; }

	void InitGameData();
	void RunMainGameLoop();
};

