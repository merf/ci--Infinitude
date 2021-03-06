#include "InfinitudeApp.h"
#include "cinder/gl/gl.h"

#include "InfiniThing.h"
#include "SoundEngine.h"

using namespace ci;
using namespace ci::app;
using namespace std;

InfinitudeAppApp* InfinitudeAppApp::mp_App = NULL;

void InfinitudeAppApp::setup()
{
	mp_App = this;
	
	mp_InfiniThing = new InfiniThing();

	CSoundEngine::Create(this);
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
	case KeyEvent::KEY_ESCAPE:
		quit();
		break;
	case KeyEvent::KEY_f:
		setFullScreen(!isFullScreen());
			
		break;
	}
}

void InfinitudeAppApp::update()
{
	if(CSoundEngine::IsValid())
	{
		CSoundEngine::Get().Update();
		mp_InfiniThing->CheckTriggers();

		static float delta_time = 1.0f / 60.0f;
		mp_InfiniThing->Update(delta_time);
	}
}

void InfinitudeAppApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 

	float w = getWindowWidth()*0.5f;
	float h = getWindowHeight()*0.5f;

	gl::pushMatrices();

	gl::translate(Vec3f(w, h, 0));

	//gl::rotate((float)getElapsedSeconds()*180.0f);

	/*

	glColor3f(1, 0, 0);
	gl::drawSolidRect(ci::Rectf(0, 0, w, h));
	glColor3f(0, 1, 0);
	gl::drawSolidRect(ci::Rectf(-w, -h, 0, 0));
	glColor3f(0, 0, 1);
	gl::drawSolidRect(ci::Rectf(-w, 0, 0, h));
	glColor3f(1, 1, 1);
	gl::drawSolidRect(ci::Rectf(0, -h, w, 0));

	*/

	mp_InfiniThing->Draw();


	//gl::translate(Vec3f(w, h, 0));
	gl::popMatrices();

	//mp_SoundEngine->Draw();
}

void InfinitudeAppApp::quit()
{
	CSoundEngine::Destroy();

	AppBasic::quit();
}

CINDER_APP_BASIC( InfinitudeAppApp, RendererGl )
