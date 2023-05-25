#pragma once

#include <cstdint>
#include <string>

enum Color
{
    Black = 0x000000,
    White = 0xFFFFFF,
    Red = 0xFF0000,
    Green = 0x00FF00,
    Blue = 0x0000FF
};

enum Pivot
{
    TopLeft,
    Center
};

struct Vector2F
{
	float X;
	float Y;
};

struct Vector2I
{
    int X;
    int Y;

	explicit operator Vector2F() const
	{
		return { (float)X, (float)Y };
	}
};

struct Text
{
    std::string Text;
    float Size { 32.f };
    Vector2I Position { 0, 0 };
    Color Color { Color::White };
    Pivot Pivot { Pivot::TopLeft };
    bool Shadow { true };
};

namespace Utility
{
	float GetDistance(Vector2F a, Vector2F b);
	float GetAngle(Vector2F a, Vector2F b);
	Vector2F GetDirection(Vector2F a, Vector2F b);
	float Range(float min, float max);
	int Range(int min, int max);
}