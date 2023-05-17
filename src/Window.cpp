#include "../include/Window.h"

#include "MiniFB.h"
#include "malloc.h"
#include <stdio.h>
#include <string.h>

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