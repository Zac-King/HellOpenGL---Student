#pragma once
#include "crenderutils.h"
#include "Component.h"
#include <vector>

class Transform : public Component
{
public:
	Matrix4 m_local, m_global;
	Transform *m_parent;
	static std::vector <Transform> s_transforms;
	vec3 &up, &right, &forward, &position;
	
	Transform()
	  : m_local(mat4MakeIdentity()), 
		m_global(mat4MakeIdentity()),
		m_parent(nullptr),
		right	(*(vec3*)&m_local.v[0]), 
		up		(*(vec3*)&m_local.v[1]),
		forward	(*(vec3*)&m_local.v[2]),
		position(*(vec3*)&m_local.v[3])
		{
			s_transforms.push_back(*this);
		}


	Matrix4 getGlobal()
	{ 
		// (condition)? (iftrue) : (iffalse)
		return m_parent ? m_local * m_parent->getGlobal() : m_local;
		//if (m_parent)
		//	return m_parent->getGlobal() * m_local;
		//else return m_local; 
	}
};
