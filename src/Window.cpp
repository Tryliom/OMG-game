#include "../include/Window.h"

#include "MiniFB.h"
#include "malloc.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

Window::Window(uint32_t width, uint32_t height)
{
    _width = width;
    _height = height;

    _window = mfb_open_ex("OMG-game", width, height, false);
    _buffer = (uint32_t*) malloc(width * height * sizeof(uint32_t));
}

void Window::Update()
{
    int state = mfb_update_ex(_window, _buffer, _width, _height);

    if (state < 0)
    {
        _window = nullptr;
    }
    else
    {
        memset(_buffer, 0, _width * _height * sizeof(uint32_t));
    }

	_frame++;
}

bool Window::IsOpen()
{
    return _window != nullptr;
}

void Window::DrawPixel(uint32_t index, Color color)
{
    if (index >= _width * _height)
    {
        return;
    }

    _buffer[index] = color;
}

void Window::DrawPixel(uint32_t x, uint32_t y, int color)
{
	const uint32_t index = y * _width + x;

	if (index >= _width * _height)
	{
		return;
	}

	_buffer[index] = color;
}

void Window::DrawPixel(uint32_t x, uint32_t y, Color color)
{
    DrawPixel(y * _width + x, color);
}

void Window::DrawHorizontalLine(uint32_t x, uint32_t y, uint32_t length, Color color)
{
    for (uint32_t i = 0; i < length; i++)
    {
        DrawPixel(x + i, y, color);
    }
}

void Window::DrawVerticalLine(uint32_t x, uint32_t y, uint32_t length, Color color)
{
    for (uint32_t i = 0; i < length; i++)
    {
        DrawPixel(x, y + i, color);
    }
}

void Window::DrawRectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height, Color color)
{
    DrawHorizontalLine(x, y, width, color);
    DrawHorizontalLine(x, y + height - 1, width, color);

    DrawVerticalLine(x, y, height, color);
    DrawVerticalLine(x + width - 1, y, height, color);
}

void Window::DrawFullRectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height, Color color)
{
    for (uint32_t i = 0; i < height; i++)
    {
        DrawHorizontalLine(x, y + i, width, color);
    }
}

void Window::DrawPlasma()
{
	const float size = 15.f;
	const float speed = -0.1f;
	const float alteredTime = _frame * speed;
	const float colorBlurOffset = 4.f;

	for (uint32_t y = 0; y < _height; y++)
	{
		for (uint32_t x = 0; x < _width; x++)
		{
			uint32_t color;

			float screenX = (float) x / (float) _width;
			float screenY = (float) y / (float) _height;

			float xSinValue = sin(screenX * size + alteredTime);
			float ySinValue = sin(screenY * size + alteredTime);
			float positionSinValue = sin((screenX + screenY) * size + alteredTime);
			float sqrtSinValue = sin(sqrtf(screenX * screenX + screenY * screenY) * size + alteredTime);

			float colorValue = xSinValue + ySinValue + positionSinValue + sqrtSinValue + colorBlurOffset;

			color = (uint32_t) (colorValue * 32.0f);

			DrawPixel(x, y, color);
		}
	}
}

void Window::DrawCustom()
{
	const uint32_t maxRadius = _width / 2;
	const uint32_t maxRadiusSquared = maxRadius * maxRadius;
	const uint32_t colorMultiplier = 0xFFFFFF / maxRadiusSquared * _frame * 0.001f;

	for (uint32_t y = 0; y < _height; y++)
	{
		for (uint32_t x = 0; x < _width; x++)
		{
			const uint32_t dx = x - maxRadius;
			const uint32_t dy = y - maxRadius;

			const uint32_t distanceSquared = dx * dx + dy * dy;

			const uint32_t color = distanceSquared * colorMultiplier - _frame * _frame * 100 /*sin(cos(_frame) * cos(_frame)) * cos(sin(_frame) * sin(_frame))*/;

			DrawPixel(x, y, color);
		}
	}
}

