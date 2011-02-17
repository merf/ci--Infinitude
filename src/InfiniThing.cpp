#include "InfiniThing.h"

#include "cinder/gl/gl.h"

using namespace cinder;

//*************************************************************************
//*************************************************************************
InfiniThing::InfiniThing()
{
	for(int i=0; i<10; ++i)
	{
		float f = i / 10.0f;
		m_Things.push_back(boost::shared_ptr<MiniInfiniThingBase> (new MiniInfiniThingBase(i, 3.0f, Color(CM_HSV, f, 1.0f, 1.0f), Vec3f(0, (f-0.5f) * 300.0f, 0))));
	}
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
void MiniInfiniThingBase::Draw()
{
	gl::pushMatrices();
	gl::translate(m_Pos);
	DrawImpl();
	gl::popMatrices();
}

//*************************************************************************
void MiniInfiniThingBase::Update(float time)
{
	float f = m_CurrTime / m_TotalTime;
	f *= 2.0f;
	if(f > 2.0f)
	{
		m_Strength = 0;
	}
	else
	{
		m_Strength = 1-f;
	}
	//else if(f > 1.0f)
	//{
	//	m_Strength = 2.0f - f;
	//}
	//else
	//{
	//	m_Strength = f;
	//}

	m_CurrTime += time;
}

//*************************************************************************
void MiniInfiniThingBase::DrawImpl()
{
	Vec2f offset(100, 0);
	glColor3f(m_Colour);
	gl::drawSolidCircle(offset * m_Strength, 1 + m_Strength * 10);
	gl::drawSolidCircle(offset * -m_Strength, 1 + m_Strength * 10);
}