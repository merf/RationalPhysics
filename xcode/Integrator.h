/*
 *  Integrator.h
 *  RPhysics
 *
 *  Created by Neil Wallace on 26/02/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once;
#include "SimObject.h"

class CIntegratorBase
{
public:
	CIntegratorBase(float time_step)
	:
	m_FixedTimeStep(time_step)
	{
	}
	
	virtual void	Integrate(Vec3fArg acceleration, CSimObjectBase& sim_object) = 0;
	
protected:
	float	m_FixedTimeStep;
};

class CForwardEulerIntegrator : public CIntegratorBase
{
public:
	CForwardEulerIntegrator(float time_step) : CIntegratorBase(time_step) {}
	
	virtual void	Integrate(Vec3fArg acceleration, CSimObjectBase& sim_object)
	{
		//calculate new position using the velocity at current time
		sim_object.SetCurrPos(sim_object.GetCurrPos() + sim_object.GetVelocity() * m_FixedTimeStep);
		//calculate new velocity using the acceleration at current time
		sim_object.SetVelocity(sim_object.GetVelocity() + acceleration * m_FixedTimeStep);
	}
	
private:
};