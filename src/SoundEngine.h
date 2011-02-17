#pragma once
#include "cinder/audio/Output.h"
#include "cinder/audio/Io.h"
#include "Kiss.h"
#include "cinder/app/AppBasic.h"

#include <list>

#define NUM_BARK_SCALE_BANDS 25
#define NUM_FFT_BANDS 512

enum ENormalizationStrategy
{
	NORMALIZE_CLAMP_BARK_BANDS,
	SMOOTH_LIMIT_BARK_BANDS,
};

//--------------------------------------------------------------------------------------
class CSoundEngine
{
public:
	CSoundEngine(ci::app::AppBasic* p_parent) 
		:
	mp_App(p_parent)
	{ 
		Init(); 
	}

	void	Init();
	void	Update();
	void	ProcessAudio(float time_step);
	void	NormalizeAudio();
	void	Draw();

	float		GetAmplitude(float f);
	float		GetAverage(float f);
	float		GetShortAverage(float f);
	float		GetMovement(float f);

private:
	float		GetVariance(float f);
	float		GetValue(float* vals, float f);

	ci::app::AppBasic* mp_App;

	// Audio file
	audio::SourceRef mAudioSource;
	audio::TrackRef mTrack;
	audio::PcmBuffer32fRef mBuffer;

	// Analyzer
	bool mFftInit;
	Kiss mFft;


	float* mp_FFTOutput;

	float m_BarkScaleValues[NUM_BARK_SCALE_BANDS];
	float m_BarkShortAverages[NUM_BARK_SCALE_BANDS];
	float m_BarkLongAverages[NUM_BARK_SCALE_BANDS];
	float m_BarkVariance[NUM_BARK_SCALE_BANDS];
	float m_BarkBandFrequencies[NUM_BARK_SCALE_BANDS];
	float m_BarkBandMultipliers[NUM_BARK_SCALE_BANDS];

	std::list<float>		m_History[NUM_BARK_SCALE_BANDS];

	int* binToBark;

	int m_BufferSize;
	int m_NumFFTBands;

	float m_SmoothVolume;
	float m_SmoothBarkBandMax;
};