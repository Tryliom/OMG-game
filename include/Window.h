#pragma once

#include <stdint.h>
#include "Image.h"
#include "Utility.h"

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
    Position GetRotatedPosition(int x, int y, Image image, Pivot pivot);

public:
    void Update();
    bool IsOpen();

    void DrawPixel(uint32_t x, uint32_t y, int color);

    void DrawHorizontalLine(uint32_t x, uint32_t y, uint32_t length, Color color);
    void DrawVerticalLine(uint32_t x, uint32_t y, uint32_t length, Color color);

    // Top left pivot
    void DrawRectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height, Color color);
    void DrawFullRectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height, Color color);

	void DrawImage(Image image, uint32_t x, uint32_t y, Pivot pivot = Pivot::Center);

	void DrawPlasma();
	void DrawCustom();

	uint32_t GetFrame() { return _frame; }

    Position GetMousePosition();
};
