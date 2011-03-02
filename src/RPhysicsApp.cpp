#include "cinder/gl/gl.h"

#include "RPhysicsApp.h"
#include "Simulation.h"

using namespace ci;
using namespace ci::app;
using namespace std;



RPhysicsApp* RPhysicsApp::mp_App = NULL;
float time_step = 1.0f/10.0f;

void RPhysicsApp::setup()
{
	mp_PhysicsWorld = new CSimulation(time_step);

	CSimObject* a1 = new CSimObject(SIM_OBJECT_DYNAMIC, 10.0f, ci::Vec3f(200, 200, 0));
	CSimObject* a2 = new CSimObject(SIM_OBJECT_DYNAMIC, 10.0f, ci::Vec3f(400, 200, 0));
	CSimObject* b = new CSimObject(SIM_OBJECT_STATIC, 1.0f, ci::Vec3f(300, 100, 0));
		
	mp_PhysicsWorld->AddSimObject(a1);
	mp_PhysicsWorld->AddSimObject(a2);
	mp_PhysicsWorld->AddSimObject(b);
	
	mp_PhysicsWorld->AddSpring(new CSpring(30, 2.9f, a1, b));
	mp_PhysicsWorld->AddSpring(new CSpring(30, 2.9f, a2, a1));
	
	mp_PhysicsWorld->AddGlobalForce(new CGravity(ci::Vec3f(0, 9.81f, 0)));
	//mp_PhysicsWorld->AddGlobalForce(new CMedium(0.05f));
	
	mp_App = this;
}

void RPhysicsApp::keyDown(KeyEvent event)
{
	switch(event.getCode())
	{
		case KeyEvent::KEY_ESCAPE:
			quit();
			break;
		default:
			break;
	}
}

void RPhysicsApp::update()
{
	mp_PhysicsWorld->Update(time_step);
}

void RPhysicsApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
	
	glColor3f(1,1,1);	
	//gl::drawSolidRect(Rectf(0,0,100,100));
	mp_PhysicsWorld->Draw();
}


CINDER_APP_BASIC( RPhysicsApp, RendererGl )
