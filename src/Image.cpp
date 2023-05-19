#include "../include/Image.h"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"
#include "malloc.h"
#include <stdio.h>

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

	_buffer = (uint32_t*) malloc(width * height * sizeof(uint32_t));

	memcpy(_buffer, pixels, width * height * sizeof(uint32_t));

	stbi_image_free(pixels);
}
