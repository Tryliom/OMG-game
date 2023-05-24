#include "Utility.h"

#include <cmath>
#include <random>

namespace Utility
{
	float GetDistance(Vector2F a, Vector2F b)
	{
		return std::sqrt(std::pow(b.X - a.X, 2) + std::pow(b.Y - a.Y, 2));
	}

	float GetAngle(Vector2F a, Vector2F b)
	{
		return std::atan2(b.Y - a.Y, b.X - a.X) * 180.f / 3.14159265f;
	}

	Vector2F GetDirection(Vector2F a, Vector2F b)
	{
		float angle = GetAngle(a, b);

		return { std::cos(angle * 3.14159265f / 180.f), std::sin(angle * 3.14159265f / 180.f) };
	}

	float Range(float min, float max)
	{
		std::random_device os_seed;
		uint_least32_t seed = os_seed();

		float offset = 0;

		if (min < 0)
		{
			max -= min;
			offset = min;
			min = 0;
		}

		std::mt19937 generator(seed);
		std::uniform_real_distribution<float> distribute(min, max);

		return distribute(generator) + offset;
	}

	int Range(int min, int max)
	{
		std::random_device os_seed;
		uint_least32_t seed = os_seed();

		int offset = 0;

		if (min < 0)
		{
			max -= min;
			offset = min;
			min = 0;
		}

		std::mt19937 generator(seed);
		std::uniform_int_distribution<uint_least32_t> distribute(min, max);

		return (int) distribute(generator) + offset;
	}
}
