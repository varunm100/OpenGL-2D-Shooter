#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

class Window
{
private:
	GLFWwindow* m_Window;
public:
	Window(const int width, const int height, const char* title, bool vsync);
	~Window();
	inline GLFWwindow* getWindowPtr() { return m_Window; }
};

