#pragma once
#include "Transform.h"
#include "crenderutils.h"
#include "Rigidbody.h"

class GameObject
{
public:
	RenderObject m_ro;     // what model on the vigi card are we using
	Transform m_transform; // x, y, rotation, scale, everything...
	unsigned m_shader;   // reference to shader
	Rigidbody m_rigidbody;

	void draw(Matrix4 m_view, Matrix4 m_projection);
	virtual void update(float a_dt, GLFWwindow* window) {}
};

