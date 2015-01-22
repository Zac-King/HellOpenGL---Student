#pragma once
#include "GameObject.h"

class Tank : public GameObject
{
public:
	float m_speed;
	float m_torque; // rotational speed

	Tank(RenderObject a_ro, unsigned a_shader, Matrix4 a_tran);

	void update(float a_dt, GLFWwindow* window);
};

class Turret : public GameObject
{
public:
	float m_torque; // rotational speed

	Turret(RenderObject a_ro, unsigned a_shader, Tank &parent);

	void update(float a_dt, GLFWwindow* window);
};