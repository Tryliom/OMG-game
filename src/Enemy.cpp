#include "Enemy.h"

#include <cmath>

Image Enemy::Sprite("../assets/enemy.png");

Enemy::Enemy()
{
    _position = { 0, 0 };
}

void Enemy::Update()
{
    _position.X += _direction.X * _speed;
    _position.Y += _direction.Y * _speed;
}

void Enemy::Draw(Window window) const
{
    // Set rotation according to the direction
    float angle = std::atan2(_direction.Y, _direction.X) * 180.f / 3.14159265f + 270.f;

    Sprite.SetRotation(angle);

    window.DrawImage(Sprite, _position.X, _position.Y, Pivot::Center);
}