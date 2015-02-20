#pragma once
#include "Core.h"
#include "Rigidbody.h"
#include "Transform.h"

struct Entity
{
	Transform *transform;
	Rigidbody *rigidbody;
};

class Factory : public Core
{
	std::vector<Entity> m_entities;

public:
	static Factory getInstance()
	{
		static Factory f;
		return f;
	}
	Entity makeWaypoint()
	{
		Entity e;
		e.transform = &Transform::Transform();
		m_entities.push_back(e);
		return e;
	}
};