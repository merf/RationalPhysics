/*
 *  Simulation.cpp
 *  RPhysics
 *
 *  Created by Neil Wallace on 26/02/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Simulation.h"
#include "cinder/gl/gl.h"
#include "RPhysicsApp.h"


using namespace ci;
using namespace std;

void CSimulation::Update(float delta_time)
{
	for(TForceGeneratorList::iterator it = m_Springs.begin(); it != m_Springs.end(); ++it)
	{
		(*it)->ApplyForce();
	}
	
	for(TSimObjectList::iterator sim_obj_it = m_SimObjects.begin(); sim_obj_it != m_SimObjects.end(); ++sim_obj_it)
	{
		for(TForceGeneratorList::iterator it = m_GlobalForces.begin(); it != m_GlobalForces.end(); ++it)
		{
			(*it)->ApplyGlobalForce(**sim_obj_it);
		}
	}
	
	for(TSimObjectList::iterator sim_obj_it = m_SimObjects.begin(); sim_obj_it != m_SimObjects.end(); ++sim_obj_it)
	{
		if((*sim_obj_it)->GetType() == SIM_OBJECT_DYNAMIC)
		{
			ci::Vec3f acceleration = (*sim_obj_it)->GetResultantForce() / (*sim_obj_it)->GetMass();
			
			m_Integrator->Integrate(acceleration, **sim_obj_it);
			
			Vec3f force = (*sim_obj_it)->GetResultantForce();

			RPhysicsApp::Get().console() << "Force = " << force.x << ", " << force.y;
			RPhysicsApp::Get().console() << " - Accel = " << acceleration.x << ", " << acceleration.y;
			RPhysicsApp::Get().console() << " - Vecl = " << (*sim_obj_it)->GetVelocity().x << ", " << (*sim_obj_it)->GetVelocity().y << "\n";
		}
	}
	
	for(TSimObjectList::iterator sim_obj_it = m_SimObjects.begin(); sim_obj_it != m_SimObjects.end(); ++sim_obj_it)
	{
		(*sim_obj_it)->ResetForces();
	}
}

void CSimulation::Draw()
{
	for(TSimObjectList::iterator sim_obj_it = m_SimObjects.begin(); sim_obj_it != m_SimObjects.end(); ++sim_obj_it)
	{
		CSimObjectBase& sim_ob = **sim_obj_it;
		ci::Vec3f pos = sim_ob.GetCurrPos();
		
		float size = 10.0f;
		sim_ob.GetType() == SIM_OBJECT_DYNAMIC ? glColor3f(0,1,0) : glColor3f(1,0,0);
		
		gl::drawSolidRect(Rectf(pos.x - size, pos.y - size, pos.x + size, pos.y + size));
	}
}