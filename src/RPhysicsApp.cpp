#include "cinder/gl/gl.h"

#include "RPhysicsApp.h"
#include "Simulation.h"

using namespace ci;
using namespace ci::app;
using namespace std;



RPhysicsApp* RPhysicsApp::mp_App = NULL;

void RPhysicsApp::setup()
{
	mp_PhysicsWorld = new CSimulation(1.0f/30.0f);

	CSimObject* a1 = new CSimObject(SIM_OBJECT_DYNAMIC, 1.0f, ci::Vec3f(200, 200, 0));
	CSimObject* a2 = new CSimObject(SIM_OBJECT_DYNAMIC, 0.1f, ci::Vec3f(400, 200, 0));
	CSimObject* b = new CSimObject(SIM_OBJECT_STATIC, 1.0f, ci::Vec3f(300, 200, 0));
		
	mp_PhysicsWorld->AddSimObject(a1);
	//mp_PhysicsWorld->AddSimObject(a2);
	mp_PhysicsWorld->AddSimObject(b);
	
	//mp_PhysicsWorld->AddSpring(new CSpring(0.0f, 0.0f, a1, b));
	
	mp_PhysicsWorld->AddGlobalForce(new CGravity(ci::Vec3f(0, 9.81f, 0)));
	mp_PhysicsWorld->AddGlobalForce(new CMedium(0.5f));
	
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
	mp_PhysicsWorld->Update(1.0f/30.0f);
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
