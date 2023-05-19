#pragma once

#include <stdint.h>

class Image
{
public:
	Image(const char* filename);

private:
	uint32_t _originalWidth;
	uint32_t _originalHeight;

	uint32_t* _originalBuffer;

	uint32_t _width;
	uint32_t _height;

	uint32_t* _buffer;

	float _scale = 1.f;

public:
	uint32_t GetWidth() { return _width; }
	uint32_t GetHeight() { return _height; }

	uint32_t* GetBuffer() { return _buffer; }

	float GetScale() { return _scale; }

	void SetScale(float factor);
};