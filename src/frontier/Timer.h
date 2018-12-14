#include <SDL2/SDL.h>


namespace frontier 
{
	//!Class used for calculating framerate and other timed functions.
	class Timer
	{
	private:
		Uint32 m_startTicks;
		Uint32 m_pausedTicks;
		bool m_paused;
		bool m_started;

	public:
		//!Contructor for timer, sets variables to default values.
		Timer();

		//!Starts the timer.
		void Start();

		//!Stops the timer.
		void Stop();

		//!Pauses the timer.
		void Pause();

		//!Unpauses the timer.
		void Unpause();

		//!Gets the ticks on the timer.
		Uint32 GetTicks();

		//!Returns if the timer is started.
		bool IsStarted();

		//!Returns if the timer is paused.
		bool IsPaused();
	};
}