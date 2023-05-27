#pragma once

#include "Utility.h"
#include "Image.h"
#include "Window.h"

class BlackHole
{
public:
	BlackHole();

private:
	Image _image;
	Vector2F _position {};

	int _frame { 0 };
	bool _isActive { false };

public:
	void Reset();

	void Update();
	void Draw(Window& window);

	Vector2F GetPosition() { return _position; }
	void SetPosition(Vector2F position) { _position = position; }

	float GetRadius() { return _image.GetScale() * 25.f; }

	[[nodiscard]] bool IsActive() const { return _isActive; }
};