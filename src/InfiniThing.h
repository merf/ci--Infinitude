#pragma once
#include "cinder/Color.h"
#include "cinder/Vector.h"

#include <list>
#include "boost/shared_ptr.hpp"
class CSoundEngine;

//--------------------------------------------------------------------------------------
class MiniInfiniThingAbstractBase
{
public:
	MiniInfiniThingAbstractBase()
		:
		m_ID(-1)
	{}

	void Init(int id, const ci::Vec3f& pos)
	{
		m_ID = id;
		m_Pos = pos;
	}

	virtual void	Trigger() {}
	virtual void	CheckForTrigger() {}

	virtual void	Update(float time) {};
	void	Draw();

	int		GetID() { return m_ID; }

protected:
	virtual void	DrawImpl() = 0;

	int		m_ID;

	ci::Vec3f m_Pos;
};

//--------------------------------------------------------------------------------------
class MiniInfiniThingSimpleBase : public MiniInfiniThingAbstractBase
{
public:
	MiniInfiniThingSimpleBase()
		:
	MiniInfiniThingAbstractBase(),
		m_TotalTime(1),
		m_CurrTime(0),
		m_TriggerCooloff(0),
		m_Strength(0),
		m_Colour()
	{}

	void Init(int id, float time, const ci::Color& color, const ci::Vec3f& pos)
	{
		__super::Init(id, pos);

		m_TotalTime = time;
		m_Colour = color;
	}

	void	Update(float time);

	virtual void	Trigger();
	virtual void	CheckForTrigger() {}
protected:
	virtual void	DrawImpl();

	float	m_TotalTime;
	float	m_CurrTime;
	float	m_TriggerCooloff;
	float	m_Strength;

	ci::Color m_Colour;
};

//--------------------------------------------------------------------------------------
class MiniInfiniThingFreqBase : public MiniInfiniThingSimpleBase
{
public:
	MiniInfiniThingFreqBase()
		:
	MiniInfiniThingSimpleBase(),
	m_Freq(0),
	m_Threshold(1)
	{

	}

	void			Init(int id, float time, const ci::Color& color, const ci::Vec3f& pos, float freq, float thresh)
	{
		__super::Init(id, time, color, pos);
		m_Freq = freq;
		m_Threshold = thresh;
	}

	virtual void	CheckForTrigger();

protected:
	float m_Freq;
	float m_Threshold;
};

//--------------------------------------------------------------------------------------
class MiniInfiniThingRect : public MiniInfiniThingFreqBase
{
public:
	MiniInfiniThingRect() : MiniInfiniThingFreqBase() {}

protected:
	virtual void	DrawImpl();
	void SetAngle(float angle) { m_Angle = angle; }

private:
	float m_Angle;
};

//--------------------------------------------------------------------------------------
class MiniInfiniThingScope : public MiniInfiniThingFreqBase
{
public:
	MiniInfiniThingScope() : MiniInfiniThingFreqBase() {}

protected:
	virtual void	DrawImpl();
};

//--------------------------------------------------------------------------------------
class MiniInfiniThingSolar : public MiniInfiniThingAbstractBase
{
public:
	MiniInfiniThingSolar() : MiniInfiniThingAbstractBase(), m_Angle(0) {}

	virtual void	Update(float time) { m_Angle += time * 180.0f; }
protected:
	virtual void	DrawImpl();
private:
	float			m_Angle;
};

//--------------------------------------------------------------------------------------
class InfiniThing
{
public:
	InfiniThing();

	void	Update(float time);
	void	Draw();
	void	CheckTriggers();
	void	Trigger(int id);

	void	AddThing(MiniInfiniThingAbstractBase* p_thing);

private:
	typedef boost::shared_ptr<MiniInfiniThingAbstractBase> TThingPtr;
	typedef std::list<TThingPtr > TThingList;
	TThingList m_Things;
};