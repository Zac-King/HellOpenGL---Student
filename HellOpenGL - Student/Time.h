#pragma once
#include <GLFW\glfw3.h>
#include "Core.h"

class Time : public Core
{
private:
	float m_deltaTime, m_totalTime;
	Time():m_deltaTime(0), m_totalTime(0) {}

protected:
	bool init() { glfwSetTime(0); return true; }
	bool step()
	{
		float currentTime = glfwGetTime();
		m_deltaTime = currentTime - m_totalTime;
		m_totalTime = currentTime;
		return true;
	}
public:
	float getDeltaTime() const { return m_deltaTime; }
	float getTotalTime() const { return m_totalTime; }
	static Time &getInstance() { static Time t; return t; }
};