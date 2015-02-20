#pragma once
#include "GLFW\glfw3.h"
#include "Core.h"
#include "Window.h"

class Input : public Core
{
private:
	bool m_keys[GLFW_KEY_LAST];
	GLFWwindow *e_window;
	
	double m_mouse_x, m_mouse_y;
	bool m_mouse_keys[GLFW_MOUSE_BUTTON_LAST];
	Input() { }
protected:
	bool init()
	{
		e_window = Window::getInstance().getHandle();
		return  true;
	}
	bool step()
	{
		for (int i = ' '; i < '~'; ++i)
			m_keys[i] = glfwGetKey(e_window, i);

		for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST; ++i)
			m_mouse_keys[i] = glfwGetMouseButton(e_window, i);
	
		glfwGetCursorPos(e_window, &m_mouse_x, &m_mouse_y);
		return true;
	}
public:
	bool getMousePressed(unsigned i)
		{ return !m_mouse_keys[i] && glfwGetMouseButton(e_window, i); }
	bool getMouseReleased(unsigned i)
		{ return m_mouse_keys[i] && !glfwGetMouseButton(e_window, i); }
	bool getMouseDown(unsigned i) { return glfwGetMouseButton(e_window, i); }

	bool getKeyPressed(unsigned i)
		{ return !m_keys[i] && glfwGetKey(e_window, i); }
	bool getKeyReleased(unsigned i)
		{ return m_keys[i] && !glfwGetKey(e_window, i); }
	bool getKeyDown(unsigned i) { return glfwGetKey(e_window, i); }

	double getMouseX() { return m_mouse_x; }
	double getMouseY() { return m_mouse_y; }

	void setMousePosition(float x, float y)
	{
		glfwSetCursorPos(e_window, m_mouse_x = x, m_mouse_y = y);
	}

	static Input &getInstance() { static Input i; return i; }
};