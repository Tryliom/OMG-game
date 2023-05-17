#pragma once

#include <stdint.h>

enum Color
{
    Black = 0x000000,
    White = 0xFFFFFF,
    Red = 0xFF0000,
    Green = 0x00FF00,
    Blue = 0x0000FF
};

class Window
{
public:
    Window(uint32_t width, uint32_t height);

private:
    uint32_t _width;
    uint32_t _height;

    struct mfb_window* _window;
    uint32_t* _buffer;

    void DrawPixel(uint32_t index, Color color);

public:
    void Update();
    bool IsOpen();

    void DrawPixel(uint32_t x, uint32_t y, Color color);

    void DrawHorizontalLine(uint32_t x, uint32_t y, uint32_t length, Color color);
    void DrawVerticalLine(uint32_t x, uint32_t y, uint32_t length, Color color);

    void DrawRectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height, Color color);
    void DrawFullRectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height, Color color);
};
