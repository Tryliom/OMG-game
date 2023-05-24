#pragma once

#include <cstdint>

class Image
{
public:
	explicit Image(const char* filename);

private:
	uint32_t _originalWidth;
	uint32_t _originalHeight;

	uint32_t* _originalBuffer;

	uint32_t _width;
	uint32_t _height;

	uint32_t* _buffer;

	float _scale = 1.f;
    float _rotation = 0.f;

public:
	[[nodiscard]] uint32_t GetWidth() const { return _width; }
	[[nodiscard]] uint32_t GetHeight() const { return _height; }

	uint32_t* GetBuffer() { return _buffer; }

	[[nodiscard]] float GetScale() const { return _scale; }
    [[nodiscard]] float GetRotation() const { return _rotation; }

    void SetRotation(float angle);
	void SetScale(float factor);
};