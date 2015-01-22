#pragma once
#include "crenderutils.h"
class Transform
{
public:
	Matrix4 m_local;
	Transform *m_parent;
	vec3 &up, &right, &forward, &position;
	
	Transform(Transform *a_parent = nullptr, Matrix4 a_local = mat4MakeIdentity())
		: m_parent(a_parent), m_local(a_local),
		right	(*(vec3*)&m_local.v[0]), 
		up		(*(vec3*)&m_local.v[1]),
		forward	(*(vec3*)&m_local.v[2]),
		position(*(vec3*)&m_local.v[3])
		{ }


	Matrix4 getGlobal()
	{ 
		// (condition)? (iftrue) : (iffalse)
		return m_parent ? m_local * m_parent->getGlobal() : m_local;
		//if (m_parent)
		//	return m_parent->getGlobal() * m_local;
		//else return m_local; 
	}
};
