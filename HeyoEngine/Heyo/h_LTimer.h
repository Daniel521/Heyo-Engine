#pragma once
//#include "..\SDL2\include\SDL.h"
#include <SDL.h>


namespace Heyo {

	// This class was taken from: http://lazyfoo.net/tutorials/SDL/44_frame_independent_movement/index.php
	// Credit goes to that gentleman

	//The application time based timer
	class LTimer
	{
	public:
		//Initializes variables
		LTimer();

		//The various clock actions
		void start();
		void stop();
		void pause();
		void unpause();

		//Gets the timer's time
		Uint32 time;
		float seconds;
		Uint32 getTicks();

		//Checks the status of the timer
		bool isStarted();
		bool isPaused();

	private:
		//The clock time when the timer started
		Uint32 mStartTicks;

		//The ticks stored when the timer was paused
		Uint32 mPausedTicks;

		//The timer status
		bool mPaused;
		bool mStarted;
	};

}