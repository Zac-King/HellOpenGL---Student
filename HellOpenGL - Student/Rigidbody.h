#pragma once
#include "crenderutils.h"
#include "Transform.h"
#include <iostream>
class Rigidbody
{
public:
	float mass, drag;
	float gravity;

	vec3 velocity;
	float angularMomentum;

	vec3 force;
	float torque;


	void addTorque(float a_torque)  { torque = torque + a_torque; }
	void addForce(vec3 a_force)     { force = force + a_force;  }


	void update(Transform &transform, float dt)
	{
		transform.m_local = makeRotation(angularMomentum * dt)
									* transform.m_local
										* makeTranslation(velocity * dt);
	
		vec3 damp = (velocity * -1) * drag;
		vec3 acceleration = (force + damp) * (1 / mass);
		velocity = velocity + acceleration * dt;
		force.x = force.y = force.z = 0;

		float a_damp = (angularMomentum * -1) * drag;
		float a_acc = (torque + a_damp) * (1 / mass);
		angularMomentum = angularMomentum + a_acc * dt;
		torque = 0;
	}

};