#include "TankStuff.h"
#include <cmath>

Tank::Tank(RenderObject a_ro, unsigned a_shader, Matrix4 a_tran)
{
	m_ro = a_ro;
	m_shader = a_shader;
	m_transform.m_local = a_tran;

	m_speed = 240;			// speed is pixels per second^2
	m_torque = 3.207;	    // Torque is radians per second^2

	m_rigidbody.mass = 1;
	m_rigidbody.drag = 2;
	m_rigidbody.gravity = 0;

	t = nullptr;
}

void Tank::update(float a_dt, GLFWwindow* window, Turret *child)
{
	m_rigidbody.update(m_transform, a_dt);
	// in tank land...
	if (glfwGetKey(window, GLFW_KEY_W))
		m_rigidbody.addForce(m_transform.up * m_speed);
	if (glfwGetKey(window, GLFW_KEY_S))
		m_rigidbody.addForce(m_transform.up * (-1 * m_speed));
	if (glfwGetKey(window, GLFW_KEY_A))
		m_rigidbody.addTorque(m_torque);
	if (glfwGetKey(window, GLFW_KEY_D))
		m_rigidbody.addTorque(-m_torque);
	if (glfwGetKey(window, GLFW_KEY_SPACE))
		t = new Bullet(m_ro, m_shader, child); 

	if (t)
		t->update(a_dt);
}

Turret::Turret(RenderObject a_ro, unsigned a_shader, Tank &parent)
{
	m_ro = a_ro;
	m_shader = a_shader;
	m_transform.m_parent = &parent.m_transform;
}

void Turret::update(float a_dt, GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_Q))
	{
		float angle = m_torque * a_dt;
		m_transform.m_local = makeRotation(angle) * m_transform.m_local;
	}

	if (glfwGetKey(window, GLFW_KEY_E))
	{
		float angle = -m_torque * a_dt;
		m_transform.m_local = makeRotation(angle) * m_transform.m_local;
	}
}

Bullet::Bullet(RenderObject a_ro, unsigned a_shader, Turret *parent)
{
	m_ro = a_ro;
	m_shader = a_shader;
	m_transform.m_parent = &parent->m_transform;

	m_speed  =  270;			// speed is pixels per second^2
	m_active = true;

	m_rigidbody.mass = .01;
	m_rigidbody.drag = 0;
	m_rigidbody.gravity = 0;
}

void Bullet::update(float a_dt)
{
	if (!m_active)
		return;

	m_rigidbody.addForce(m_transform.up * m_speed);	// add force to rigid body
	m_rigidbody.update(m_transform, a_dt);			// need to update the rigid body
}

