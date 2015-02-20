#pragma once
#include <list>

#include "Core.h"
#include "Window.h"
#include "Time.h"
#include "Input.h"
#include "Camera.h"

class Engine : public Core
{
	std::list<Core*> m_cores;
	Engine() {}
public:
	static Engine &getInstance() { static Engine e; return e; }
	void loadCore()
	{
		m_cores.push_back(&Window::getInstance());
		m_cores.push_back(&Time::getInstance());
		m_cores.push_back(&Input::getInstance());
		m_cores.push_back(&Camera::getInstance());
	}
	virtual bool init()
	{
		for each(auto c in m_cores) if (!c->init()) return false;
		return true;
	}
	virtual bool step()
	{
		for each(auto c in m_cores) if (!c->step()) return false;
		return true;
	}
	virtual bool term()
	{
		m_cores.reverse();
		for each(auto c in m_cores) if (!c->term()) return false;
		return true;
	}
};