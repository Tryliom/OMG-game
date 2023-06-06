#pragma once

#include <cstdint>
#include <map>

#include "Image.hpp"
#include "Utility.hpp"
#include "Font.hpp"

class Window
{
public:
    Window(uint32_t width, uint32_t height);

private:
    uint32_t _width;
    uint32_t _height;
    uint32_t _background;

    struct mfb_window* _window;
    uint32_t* _buffer;

	uint32_t _frame { 0 };

    // Font
    std::map<int, rtpAtlasSprite> _chars;
    std::map<int, Image> _charsImage;

    void DrawPixel(uint32_t index, int color);

    static Vector2I GetStartPosition(uint32_t width, uint32_t height, int x, int y, Pivot pivot);
    static Vector2I GetRotatedPosition(int x, int y, Image image, Pivot pivot);

public:
    [[nodiscard]] uint32_t GetFrame() const { return _frame; }

    [[nodiscard]] uint32_t GetWidth() const { return _width; }
    [[nodiscard]] uint32_t GetHeight() const { return _height; }

    [[nodiscard]] uint32_t GetBackgroundColor() const { return _background; }
    void SetBackgroundColor(uint32_t color) { _background = color; }

    void Update();
    bool IsOpen();

    void DrawPixel(uint32_t x, uint32_t y, int color);

    void DrawHorizontalLine(uint32_t x, uint32_t y, uint32_t length, int color);
    void DrawVerticalLine(uint32_t x, uint32_t y, uint32_t length, int color);

    // Top left pivot
    void DrawRectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height, int color);
    void DrawFullRectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height, int color);

    void DrawLine(Vector2I start, Vector2I end, int color);

	void DrawImage(Image image, int x, int y, Pivot pivot = Pivot::Center);

	void DrawPlasma();
	void DrawCustom();

    Vector2I GetMousePosition();

    void DrawText(Text text);
};
