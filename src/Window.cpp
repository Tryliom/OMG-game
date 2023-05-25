#include "Window.h"

#include "MiniFB.h"
#include "Input.h"

#if defined(_WIN32)
    #include "malloc.h"
#endif
#include <cstring>
#include <cmath>
#include <iostream>

Window::Window(uint32_t width, uint32_t height)
{
    _width = width;
    _height = height;

    _background = Color::Black;

    _window = mfb_open_ex("Black hole shooter", width, height, false);
    _buffer = (uint32_t*) malloc(width * height * sizeof(uint32_t));

    Input::Initialize(_window);

    // Assign each chars to an image using char value as index
    auto font = Image(ATLAS_FONT_IMAGE_PATH);
    _chars = {};
    _charsImage = {};

    for (rtpAtlasSprite sprite: rtpDescBoldFonts)
    {
        _chars[sprite.charValue] = sprite;
        _charsImage[sprite.charValue] = font.Cut(sprite.positionX, sprite.positionY, sprite.sourceWidth, sprite.sourceHeight);
    }
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

        // Draw background
        for (uint32_t i = 0; i < _width * _height; i++)
        {
            _buffer[i] = _background;
        }
    }

	_frame++;

    Input::Update();
}

bool Window::IsOpen()
{
    return _window != nullptr;
}

void Window::DrawPixel(uint32_t index, int color)
{
    if (index >= _width * _height || color >> 24 == 0)
    {
        return;
    }

    if (_buffer[index] != 0)
    {
        // Alpha blending
        const float srcAlpha = (float) ((uint8_t) (color >> 24)) / 256.f;
        const float destAlpha = 1.f - srcAlpha;
        const uint32_t destColor = _buffer[index];

        const auto destR = (uint8_t) (destColor >> 16);
        const auto destG = (uint8_t) (destColor >> 8);
        const auto destB = (uint8_t) (destColor);

        const auto srcR = (uint8_t) (color >> 16);
        const auto srcG = (uint8_t) (color >> 8);
        const auto srcB = (uint8_t) (color);

        const auto r = (uint8_t) (srcR * srcAlpha + destR * destAlpha);
        const auto g = (uint8_t) (srcG * srcAlpha + destG * destAlpha);
        const auto b = (uint8_t) (srcB * srcAlpha + destB * destAlpha);

        color = MFB_RGB(r, g, b);
    }

    _buffer[index] = color;
}

void Window::DrawPixel(uint32_t x, uint32_t y, int color)
{
	const uint32_t index = y * _width + x;

	if (x >= _width || y >= _height)
	{
		return;
	}

	DrawPixel(index, color);
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

Vector2I Window::GetStartPosition(uint32_t width, uint32_t height, int x, int y, Pivot pivot)
{
    Vector2I position {};

	if (pivot == Pivot::Center)
	{
		position.X = x - width / 2;
		position.Y = y - height / 2;
	}
	else if (pivot == Pivot::TopLeft)
	{
		position.X = x;
		position.Y = y;
	}

	return position;
}

Vector2I Window::GetRotatedPosition(int x, int y, Image image, Pivot pivot)
{
    float angle = image.GetRotation();
    int width = image.GetWidth();
    int height = image.GetHeight();
    float sinAngle = sin(angle);
    float cosAngle = cos(angle);
    Vector2I position {};

    if (pivot == Pivot::Center)
    {
        x -= width / 2;
        y -= height / 2;

        position.X = (int) (x * cosAngle - y * sinAngle) + width / 2;
        position.Y = (int) (x * sinAngle + y * cosAngle) + height / 2;
    }
    else if (pivot == Pivot::TopLeft)
    {
        position.X = (int) (x * cosAngle - y * sinAngle);
        position.Y = (int) (x * sinAngle + y * cosAngle);
    }

    return position;
}

void Window::DrawImage(Image image, int x, int y, Pivot pivot)
{
	uint32_t imageWidth = image.GetWidth();
	uint32_t imageHeight = image.GetHeight();
    float imageRotation = image.GetRotation();

    auto position = GetStartPosition(imageWidth, imageHeight, x, y, pivot);

    for (uint32_t i = 0; i < imageHeight; i++)
    {
        for (uint32_t j = 0; j < imageWidth; j++)
        {
            uint32_t color = image.GetBuffer()[i * imageWidth + j];

            auto finalX = j;
            auto finalY = i;

            if (imageRotation != 0.f)
            {
                auto rotatedPosition = GetRotatedPosition(j, i, image, pivot);
                finalX = rotatedPosition.X;
                finalY = rotatedPosition.Y;
            }

            DrawPixel(position.X + finalX, position.Y + finalY, color);
        }
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

			color = (uint32_t) (colorValue * 32.f);

			DrawPixel(x, y, color);
		}
	}
}

void Window::DrawCustom()
{
	const uint32_t speed = 100;
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

			const uint32_t color = distanceSquared * colorMultiplier - _frame * _frame * speed /*sin(cos(_frame) * cos(_frame)) * cos(sin(_frame) * sin(_frame))*/;

			DrawPixel(x, y, color);
		}
	}
}

Vector2I Window::GetMousePosition()
{
    Vector2I position {};

    position.X = mfb_get_mouse_x(_window);
    position.Y = mfb_get_mouse_y(_window);

    return position;
}

void Window::DrawText(Text text)
{
    int length = text.Text.length();
    int width = 0, height = 0;
    float scale = text.Size / ATLAS_FONT_SIZE;

    for (uint32_t i = 0; i < length; i++)
    {
        char c = text.Text[i];

        if (_chars[c].charValue == 0)
        {
            c = '?';
        }

        width += _charsImage[c].GetWidth() + _chars[c].charOffsetX;

        if (height < _charsImage[c].GetHeight())
        {
            height = _charsImage[c].GetHeight();
        }
    }

    auto position = GetStartPosition(width, height, text.Position.X, text.Position.Y, text.Pivot);

    for (uint32_t i = 0; i < length; i++)
    {
        char c = text.Text[i];

        if (_chars[c].charValue == 0)
        {
            c = '?';
        }

        _charsImage[c].SetScale(scale);

        if (text.Shadow)
        {
            _charsImage[c].SetColor(Color::Black);

            const int shadowOffset = 2;

            DrawImage(_charsImage[c],position.X + _chars[c].charOffsetX + shadowOffset,position.Y + _chars[c].charOffsetY + shadowOffset, text.Pivot);
        }

        _charsImage[c].SetColor(text.Color);

        DrawImage(_charsImage[c],position.X + _chars[c].charOffsetX,position.Y + _chars[c].charOffsetY, text.Pivot);

        position.X += _chars[c].charAdvanceX * scale + 1;
    }
}