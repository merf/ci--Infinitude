#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

#include "InfiniThing.h"
#include "SoundEngine.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class InfinitudeAppApp : public AppBasic {
  public:
	void setup();
	void keyDown(KeyEvent event);	
	void update();
	void draw();

	InfiniThing* mp_InfiniThing;
	CSoundEngine* mp_SoundEngine;
};

void InfinitudeAppApp::setup()
{
	mp_InfiniThing = new InfiniThing();
	mp_SoundEngine = new CSoundEngine(this);
}

void InfinitudeAppApp::keyDown(KeyEvent event)
{
	switch(event.getCode())
	{
	case KeyEvent::KEY_0:
		mp_InfiniThing->Trigger(0);
		break;
	case KeyEvent::KEY_1:
		mp_InfiniThing->Trigger(1);
		break;
	case KeyEvent::KEY_2:
		mp_InfiniThing->Trigger(2);
		break;
	case KeyEvent::KEY_3:
		mp_InfiniThing->Trigger(3);
		break;
	case KeyEvent::KEY_4:
		mp_InfiniThing->Trigger(4);
		break;
	case KeyEvent::KEY_5:
		mp_InfiniThing->Trigger(5);
		break;
	case KeyEvent::KEY_6:
		mp_InfiniThing->Trigger(6);
		break;
	case KeyEvent::KEY_7:
		mp_InfiniThing->Trigger(7);
		break;
	case KeyEvent::KEY_8:
		mp_InfiniThing->Trigger(8);
		break;
	case KeyEvent::KEY_9:
		mp_InfiniThing->Trigger(9);
		break;
	}
}

void InfinitudeAppApp::update()
{
	mp_SoundEngine->Update();

	for(int i=0; i<10; ++i)
	{
		float f = i/10.0f;

		if(mp_SoundEngine->GetMovement(f) > 0.5f)
		{
			mp_InfiniThing->Trigger(i);
		}
	}

	static float delta_time = 1.0f / 60.0f;
	mp_InfiniThing->Update(delta_time);
}

void InfinitudeAppApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 

	float w = getWindowWidth()*0.5f;
	float h = getWindowHeight()*0.5f;

	gl::pushMatrices();

	gl::translate(Vec3f(w, h, 0));
	/*
	gl::rotate((float)getElapsedSeconds()*180.0f);

	glColor3f(1, 0, 0);
	gl::drawSolidRect(ci::Rectf(0, 0, w, h));
	glColor3f(0, 1, 0);
	gl::drawSolidRect(ci::Rectf(-w, -h, 0, 0));
	glColor3f(0, 0, 1);
	gl::drawSolidRect(ci::Rectf(-w, 0, 0, h));
	glColor3f(1, 1, 1);
	gl::drawSolidRect(ci::Rectf(0, -h, w, 0));

	glColor3f(0,0,0);
	gl::drawSolidCircle(ci::Vec2f(0,0), w*0.25f);
	*/

	mp_InfiniThing->Draw();

	//gl::translate(Vec3f(w, h, 0));
	gl::popMatrices();

	//mp_SoundEngine->Draw();
}

CINDER_APP_BASIC( InfinitudeAppApp, RendererGl )
