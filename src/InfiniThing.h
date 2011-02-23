#pragma once
#include "cinder/Color.h"
#include "cinder/Vector.h"

#include <list>
#include "boost/shared_ptr.hpp"

//--------------------------------------------------------------------------------------
class MiniInfiniThingBase
{
public:
	MiniInfiniThingBase(int id, float time, const ci::Color& color, const ci::Vec3f& pos)
		:
		m_ID(id),
		m_TotalTime(time),
		m_CurrTime(0),
		m_TriggerCooloff(0),
		m_Strength(0),
		m_Colour(color),
		m_Pos(pos)
	{}

	void	Update(float time);
	void	Draw();

	virtual void	DrawImpl();
	virtual void	Trigger();

	int		GetID() { return m_ID; }

private:
	int		m_ID;
	float	m_TotalTime;
	float	m_CurrTime;
	float	m_TriggerCooloff;
	float	m_Strength;

	ci::Color m_Colour;
	ci::Vec3f m_Pos;
};

//--------------------------------------------------------------------------------------
class InfiniThing
{
public:
	InfiniThing();

	void	Update(float time);
	void	Draw();
	void	Trigger(int id);

private:
	typedef std::list<boost::shared_ptr<MiniInfiniThingBase> > TThingList;
	TThingList m_Things;
};