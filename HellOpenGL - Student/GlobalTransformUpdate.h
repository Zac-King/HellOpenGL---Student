#pragma once
#include "Factory.h"
#include "System.h"
#include "Transform.h"

class GlobalTransformUpdate : public System
{
public:
	void process()
	{
		for each(auto e in Factory::getInstance().m_entities)
			if (e.transform)
				updateGlobal(*e.transform);
	}

};