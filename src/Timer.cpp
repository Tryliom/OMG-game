#include "Timer.h"

#include "MiniFB.h"

float deltaTime = 0.f;
int deltaFrames = 0;
float time = 0.f;
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
		time += deltaTime;

		if (deltaFrames < 200 && !stabilized)
		{
			time = 0;
		}
		else if (deltaFrames == 201 && !stabilized)
		{
			deltaFrames = 1;
			time = deltaTime;
			stabilized = true;
		}

		if (time > 99999.f)
		{
			time -= 99999.f;
			deltaFrames = 0;
		}
	}

	float GetDeltaTime()
	{
		if (!stabilized) return deltaTime;

		return time / deltaFrames;
	}

	float GetTime()
	{
		return time;
	}
}
