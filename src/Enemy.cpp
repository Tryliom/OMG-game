#include "Enemy.h"

#include "AudioManager.h"
#include "Timer.h"
#include "Window.h"

#include <cmath>

#define IMG_PATH "../assets/enemy.png"

Image Enemy::Sprite(IMG_PATH);

Enemy::Enemy()
{
    _position = { 0, 0 };
}

void Enemy::Update()
{
	if (_isSwallowed)
	{
		_direction = Utility::GetDirection(_position, _swallowTarget);
	}

    _position.X += _direction.X * _speed * Timer::GetSmoothDeltaTime();
    _position.Y += _direction.Y * _speed * Timer::GetSmoothDeltaTime();
}

void Enemy::Draw(Window& window)
{
	if (_isSwallowed)
	{
		auto distance = Utility::GetDistance(_position, _swallowTarget);
		Sprite.SetScale(distance / _swallowDistance);
		Sprite.SetRotation(distance / _swallowDistance * 360.f);

		if (Utility::GetDistance(_position, _swallowTarget) < 10.f)
		{
			_isDead = true;
		}
	}
	else
	{
		// Set rotation according to the direction
		float angle = Utility::ToDegrees(std::atan2(_direction.Y, _direction.X)) + 90.f;

		Sprite.SetScale(1.f);
		Sprite.SetRotation(angle);
	}

	window.DrawImage(Sprite, _position.X, _position.Y, Pivot::Center);
}

void Enemy::Swallow(Vector2F target)
{
	_swallowTarget = target;
	_isSwallowed = true;
	_speed = 250.f;
	_direction = Utility::GetDirection(_position, target);
	_swallowDistance = Utility::GetDistance(_position, target);

    AudioManager::Play(AudioType::Swallow);
}