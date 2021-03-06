#include "InfiniThing.h"
#include "SoundEngine.h"
#include "InfinitudeApp.h"

#include "cinder/gl/gl.h"

using namespace cinder;

//*************************************************************************
//*************************************************************************
InfiniThing::InfiniThing()
{
	//float num = 24.0f;

	//for(int i=0; i<num; ++i)
	//{
	//	float f = i / num;
	//	MiniInfiniThingRect* r = new MiniInfiniThingRect();
	//	//r->Init(i, 0.2f, Color(CM_HSV, f, 1.0f, 1.0f), Vec3f((f-0.5f)*300.0f, 0.0f, 0.0f), f, 0.5f);
	//	r->Init(i, 0.5f, Color(CM_HSV, f, 1.0f, 1.0f), Vec3f(0.0f, 0.0f, 0.0f), f, 0.5f);
	//	r->SetAngle(f * 360.0f);
	//	AddThing(r);
	//	//m_Things.push_back(boost::shared_ptr<MiniInfiniThingBase> (new MiniInfiniThingBase(i, 0.1f, Color(CM_HSV, f, 1.0f, 1.0f), Vec3f(0, (f-0.5f) * 300.0f, 0))));
	//}
	MiniInfiniThingSolar* s = new MiniInfiniThingSolar();
	s->Init(0, Vec3f(0,0,0));
	AddThing(s);

	MiniInfiniThingScope* scope = new MiniInfiniThingScope();
	scope->Init(1, 0.5f, Color(CM_RGB, 1,1,1), Vec3f(0,0,0), 0.5f, 0.5f);
	AddThing(scope);
}

//*************************************************************************
void InfiniThing::AddThing(MiniInfiniThingAbstractBase* p_thing)
{
	m_Things.push_back(TThingPtr(p_thing));
}

//*************************************************************************
void InfiniThing::Draw()
{
	for(TThingList::iterator it = m_Things.begin(); it != m_Things.end(); ++it)
	{
		(*it)->Draw();
	}
}

//*************************************************************************
void InfiniThing::Update(float time)
{
	for(TThingList::iterator it = m_Things.begin(); it != m_Things.end(); ++it)
	{
		(*it)->Update(time);
	}
}

//*************************************************************************
void InfiniThing::CheckTriggers()
{
	for(TThingList::iterator it = m_Things.begin(); it != m_Things.end(); ++it)
	{
		(*it)->CheckForTrigger();
	}
}

//*************************************************************************
void InfiniThing::Trigger(int id)
{
	for(TThingList::iterator it = m_Things.begin(); it != m_Things.end(); ++it)
	{
		if((*it)->GetID() == id)
		{
			(*it)->Trigger();
		}
	}
}

//*************************************************************************
//*************************************************************************
void MiniInfiniThingAbstractBase::Draw()
{
	gl::pushMatrices();
	gl::translate(m_Pos);
	DrawImpl();
	gl::popMatrices();
}

//*************************************************************************
void MiniInfiniThingSimpleBase::Update(float time)
{
	float f = m_CurrTime / m_TotalTime;
	m_Strength = 1.0f-f;
	//f *= 2.0f;
	//if(f > 2.0f)
	//{
	//	m_Strength = 0;
	//}
	//else if(f > 1.0f)
	//{
	//	m_Strength = 2.0f - f;
	//}
	//else
	//{
	//	m_Strength = f;
	//}

	m_CurrTime += time;
	m_TriggerCooloff -= time;
}

//*************************************************************************
void MiniInfiniThingFreqBase::CheckForTrigger()
{
	if(CSoundEngine::Get().GetMovement(m_Freq) > m_Threshold)
	{
		Trigger();
	}
}

//*************************************************************************
void MiniInfiniThingSimpleBase::Trigger()
{
	if(m_TriggerCooloff <= 0.0f)
	{
		m_TriggerCooloff = m_TotalTime * 0.5f;
		m_CurrTime = 0; 
	}
}

//*************************************************************************
void MiniInfiniThingSimpleBase::DrawImpl()
{
	Vec2f offset(100, 0);
	glColor3f(m_Colour);
	gl::drawSolidCircle(offset * m_Strength, 1 * 10);
	gl::drawSolidCircle(offset * -m_Strength, 1 * 10);
}

//*************************************************************************
void MiniInfiniThingScope::DrawImpl()
{
	if(m_Strength > 0.5f)
	{
		float width = InfinitudeAppApp::mp_App->getWindowWidth() * 0.25f;
		float height = InfinitudeAppApp::mp_App->getWindowHeight() * 0.125f * m_Strength;
		glColor3f(m_Colour);

		int num = 0;
		float* data = CSoundEngine::Get().GetRawAudio(num);

		PolyLine<Vec2f> ScopeLine;
		
		int inc = (m_Strength) * 256;
		inc = math<int>::clamp(inc, 1, 256);

		for(int i=0; i<num; i += inc)
		{
			float f = i/(float)num;
			f -= 0.5f;
			ScopeLine.push_back(Vec2f(f * width, (data[i])*height));
		}
		gl::draw(ScopeLine);
	}
}

//*************************************************************************
void MiniInfiniThingSolar::DrawImpl()
{
	gl::rotate(m_Angle);

	int num = 24;

	float angle_inc = 360.0f / (float)num;

	float size = InfinitudeAppApp::mp_App->getWindowWidth() * 0.25f;

	for(int i=0; i<num; ++i)
	{
		float f = i/(float)num;

		gl::rotate(angle_inc);
		glColor3f(Color(CM_HSV, f, 1, 1));
		float val = CSoundEngine::Get().GetShortAverage(f) + 0.3f;
		val = math<float>::max(val, 0.0f);
		gl::drawSolidRect(Rectf(0, 0, size * 0.1f, val * -size));
	}

	glColor3f(0,0,0);
	gl::drawSolidCircle(ci::Vec2f(0,0), InfinitudeAppApp::mp_App->getWindowWidth() * 0.125f);
}