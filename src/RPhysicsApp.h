/*
 *  RPhysicsApp.h
 *  RPhysics
 *
 *  Created by Neil Wallace on 01/03/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once
#include "cinder/app/AppBasic.h"

class CSimulation;

class RPhysicsApp : public ci::app::AppBasic {
public:
	void setup();
	void keyDown(ci::app::KeyEvent event);	
	void update();
	void draw();
	
	CSimulation* mp_PhysicsWorld;
	
	static RPhysicsApp& Get() { return *mp_App; }
private:
	static RPhysicsApp* mp_App;
};