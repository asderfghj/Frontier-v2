#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include <SDL2/SDL.h>
#include <memory>

namespace frontier
{

	class Timer;

	//!Deals with framerate, time and random values.
	class Environment
	{
	private:
		double m_deltaTime;
		Uint64 m_last, m_now;
		std::shared_ptr<Timer> m_timer;
		int m_countedFrames;
	public:
		//!Initialises the default variables in environment.
		Environment();

		//!Returns the current delta time.
		float GetDeltaTime();

		//!Updates the delta time
		void Tick();

		//!Returns the active timer.
		std::shared_ptr<Timer> GetTimer();

		//!Increments the frame counter.
		void IncrementFrameCounter();

		//!Returns the counted frames.
		int GetCountedFrames();

		//!Returns the current frames per second.
		float GetFPS();

		//!Returns a random value between two specified values.
		/*!
			\param _val1 Lowest value for the random float.
			\param _val2 Highest value for the random float.
		*/
		float GetRandomBetweenTwoValues(float _val1, float _val2);

		//!Returns the time since the program began.
		Uint32 GetTime();
	};
}

#endif