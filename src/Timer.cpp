#include "Timer.h"

#include "MiniFB.h"

float deltaTime = 0.f;
int frames = 0;
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
		frames++;
		totalTime += deltaTime;

		if (frames == 201 && !stabilized)
		{
            frames = 1;
			totalTime = deltaTime;
			stabilized = true;
		}

		if (totalTime > 99999.f)
		{
			totalTime -= 99999.f;
            frames = 0;
		}
	}

	float GetDeltaTime()
	{
		if (!stabilized) return deltaTime;

		return totalTime / frames;
	}
}
