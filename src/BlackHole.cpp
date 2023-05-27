#include "BlackHole.h"

BlackHole::BlackHole() : _image("../assets/black_hole.png")
{
	Reset();
	_isActive = false;

	_image.SetColor(Utility::ToColor(0, 0, 0));
}

void BlackHole::Reset()
{
	_position = { 0.f, 0.f };
	_frame = 0;
	_image.SetScale(0.1f);
	_isActive = true;
}

void BlackHole::Update()
{
	_frame++;

	if (_frame < 100)
	{
		_image.SetScale(_image.GetScale() + 0.05f + 0.1f * _frame / 100.f);
	}
	else
	{
		_image.SetScale(_image.GetScale() - _image.GetScale() * 0.1f * (_frame - 100.f) / 50.f);
	}

	_image.SetRotation(_image.GetRotation() + 1.f + 3.f * _frame / 150.f);

	if (_frame > 150)
	{
		_isActive = false;
	}
}

void BlackHole::Draw(Window& window)
{
	window.DrawImage(_image, _position.X, _position.Y, Pivot::Center);
}