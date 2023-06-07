#include "BlackHole.h"

#define IMG_PATH "../assets/black_hole.png"

BlackHole::BlackHole() : _image(IMG_PATH)
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
	_maxScale = 5.f;
}

void BlackHole::UpdateMaxScale(int score)
{
	_maxScale = 5.f + score / 200.f;

	if (_maxScale > 15.f) _maxScale = 15.f;
}

void BlackHole::Update()
{
	_frame++;

	if (_frame < 100)
	{
		_image.SetScale(_maxScale * _frame / 100.f);
	}
	else
	{
		_image.SetScale(_maxScale * (1.f - (_frame - 100) / 50.f));
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