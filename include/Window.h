#pragma once

#include <stdint.h>
#include "Image.h"

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
	TopCenter,
	TopRight,
	CenterLeft,
	Center,
	CenterRight,
	BottomLeft,
	BottomCenter,
	BottomRight
};

struct Position
{
	uint32_t X;
	uint32_t Y;
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

	uint32_t _frame;

    void DrawPixel(uint32_t index, int color);

	Position GetStartPosition(uint32_t width, uint32_t height, uint32_t x, uint32_t y, Pivot pivot);

public:
    void Update();
    bool IsOpen();

    void DrawPixel(uint32_t x, uint32_t y, int color);

    void DrawHorizontalLine(uint32_t x, uint32_t y, uint32_t length, Color color);
    void DrawVerticalLine(uint32_t x, uint32_t y, uint32_t length, Color color);

    void DrawRectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height, Color color);
    void DrawFullRectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height, Color color);

	void DrawImage(Image image, uint32_t x, uint32_t y, Pivot pivot = Pivot::Center);

	void DrawPlasma();
	void DrawCustom();

	uint32_t GetFrame() { return _frame; }

	Position GetMousePosition();
};
