#include <iostream>
#include <time.h>
#include "Environment.h"
#include "Timer.h"

namespace frontier
{

	Environment::Environment()
	{
		m_now = SDL_GetPerformanceCounter();
		m_last = 0;
		m_deltaTime = 0;
		m_timer = std::make_shared<Timer>();
		m_countedFrames = 0;
		srand(time(NULL));
	}

	float Environment::GetDeltaTime()
	{
		return (float)m_deltaTime;
	}

	void Environment::Tick()
	{
		m_last = m_now;
		m_now = SDL_GetPerformanceCounter();
		m_deltaTime = (double)((m_now - m_last) * 1000 / (double)SDL_GetPerformanceFrequency());
		if (m_deltaTime > 0.15)
		{
			m_deltaTime = 0.15;
		}
	}

	std::shared_ptr<Timer> Environment::GetTimer()
	{
		return m_timer;
	}

	void Environment::IncrementFrameCounter()
	{
		m_countedFrames++;
	}

	int Environment::GetCountedFrames()
	{
		return m_countedFrames;
	}

	float Environment::GetFPS()
	{
		float avgFPS = m_countedFrames / (m_timer->GetTicks() / 1000.0f);
		if (avgFPS > 2000000)
		{
			avgFPS = 0;
		}
		return avgFPS;
	}

	float Environment::GetRandomBetweenTwoValues(float _val1, float _val2)
	{
		float random = ((float)rand() / (float)RAND_MAX);
		float diff = _val2 - _val1;
		float r = random * diff;
		return _val1 + r;
	}

	Uint32 Environment::GetTime()
	{
		return m_timer->GetTicks();
	}

}