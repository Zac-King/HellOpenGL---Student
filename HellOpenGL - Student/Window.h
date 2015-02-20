#pragma once
#include "Core.h"
#include <GL\glew.h>
#include <GL\wglew.h>
#include <GLFW\glfw3.h>

extern const unsigned int e_SCREEN_WIDTH;
extern const unsigned int e_SCREEN_HEIGHT;
extern const char e_SCREEN_NAME[];

class Window : public Core
{
private:
	GLFWwindow* m_window;

	Window() : m_window(nullptr) {}

protected:	
	bool init()
	{
		if (!glfwInit()) return false;
		
		m_window = glfwCreateWindow(e_SCREEN_WIDTH, e_SCREEN_HEIGHT, e_SCREEN_NAME, NULL, NULL);
		if (!m_window) { glfwTerminate(); return false; }
		glfwMakeContextCurrent(m_window);
		if (glewInit() != GLEW_OK) { glfwTerminate(); return false; }

		return true;
	}
	bool step()
	{
		glfwSwapBuffers(m_window);
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		return !glfwWindowShouldClose(m_window);
	}
	bool term()
	{
		glfwTerminate();
		return true;
	}

public:
	static Window &getInstance() { static Window w; return w; }
	GLFWwindow *getHandle() { return m_window; }
};