#pragma once
#include "GameObject.h"

class Bullet;
class Turret;

class Tank : public GameObject
{
public:
	float m_speed;
	float m_torque; // rotational speed
	Bullet *t;

	Tank(RenderObject a_ro, unsigned a_shader, Matrix4 a_tran);

	void update(float a_dt, GLFWwindow* window, Turret *turret);
};

class Turret : public GameObject
{
public:
	float m_torque; // rotational speed

	Turret(RenderObject a_ro, unsigned a_shader, Tank &parent);

	void update(float a_dt, GLFWwindow* window);
};

class Bullet : public GameObject
{
public:
	float m_speed;
	bool  m_active;

	Bullet(RenderObject a_ro, unsigned a_shader, Turret *parent);

	void update(float a_dt);
};