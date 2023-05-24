#include "../include/Image.h"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"
#if defined(_WIN32)
    #include "malloc.h"
#endif
#include <stdio.h>
#include <string.h>

Image::Image(const char* filename)
{
	int width, height, channels;

	stbi_uc* pixels = stbi_load(filename, &width, &height, &channels, 4);

	if (pixels == nullptr)
	{
		printf("Failed to load image: %s\n", filename);
		return;
	}

	_width = width;
	_height = height;

	_originalWidth = width;
	_originalHeight = height;

	_buffer = (uint32_t*) malloc(width * height * sizeof(uint32_t));
	_originalBuffer = (uint32_t*) malloc(width * height * sizeof(uint32_t));

	memcpy(_buffer, pixels, width * height * sizeof(uint32_t));

	// Convert from RGBA to ARGB
	for (int i = 0; i < width * height; i++)
	{
		const uint32_t r = pixels[i * 4 + 0];
		const uint32_t g = pixels[i * 4 + 1];
		const uint32_t b = pixels[i * 4 + 2];
		const uint32_t a = pixels[i * 4 + 3];

		_buffer[i] = (a << 24) | (r << 16) | (g << 8) | b;
	}

	memcpy(_originalBuffer, _buffer, width * height * sizeof(uint32_t));

	stbi_image_free(pixels);
}

void Image::SetRotation(float angle)
{
    _rotation = angle;
}

void Image::SetScale(float factor)
{
	_scale = factor;

	_width = _originalWidth * factor;
	_height = _originalHeight * factor;

	free(_buffer);

	_buffer = (uint32_t*) malloc(_width * _height * sizeof(uint32_t));

	for (uint32_t y = 0; y < _height; y++)
	{
		for (uint32_t x = 0; x < _width; x++)
		{
			const uint32_t originalX = x / factor;
			const uint32_t originalY = y / factor;

			const uint32_t index = y * _width + x;
			const uint32_t originalIndex = originalY * _originalWidth + originalX;

			_buffer[index] = _originalBuffer[originalIndex];
		}
	}
}