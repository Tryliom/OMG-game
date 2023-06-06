#include "Timer.hpp"

#include "MiniFB.h"

float deltaTime = 0.f;
int deltaFrames = 0;
float totalTime = 0.f;
bool stabilized = false;
mfb_timer* timer;

namespace Timer
{
	void Init()
	{
		timer = mfb_timer_create();
		mfb_timer_reset(timer);
	}

	void Update()
	{
		deltaTime = mfb_timer_delta(timer);
		deltaFrames++;
		totalTime += deltaTime;

		if (deltaFrames == 201 && !stabilized)
		{
			deltaFrames = 1;
			totalTime = deltaTime;
			stabilized = true;
		}

		if (totalTime > 99999.f)
		{
			totalTime -= 99999.f;
			deltaFrames = 0;
		}
	}

	float GetDeltaTime()
	{
		if (!stabilized) return deltaTime;

		return totalTime / deltaFrames;
	}
}
