/*
 *  ForceGenerator.cpp
 *  RPhysics
 *
 *  Created by Neil Wallace on 26/02/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "ForceGenerator.h"

//*********************************************************************************
void CSpring::ApplyForce()
{
	ci::Vec3f direction = m_SimObjectA->GetCurrPos() - m_SimObjectB->GetCurrPos();
	float curr_length = direction.length();
	if(curr_length > 0)
	{
		direction.normalize();
		ci::Vec3f force = -m_Stiffness * ((curr_length - m_RestLength) * direction);
		
		//add damping force
		//force += -m_Damping * (m_SimObjectA->GetVelocity() - m_SimObjectB->GetVelocity()).dot(direction) * direction;
		force *= m_Damping;
		
		m_SimObjectA->ApplyForce(force);
		m_SimObjectB->ApplyForce(-force);
	}
}