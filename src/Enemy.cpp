#include "../include/Enemy.h"

#include "math.h"

Enemy::Enemy()
{
    _position = { 0, 0 };
}

void Enemy::Initialize()
{
    _image = Image("assets/enemy.png");
}

void Enemy::Update()
{
    _position.X += _direction.X * _speed;
    _position.Y += _direction.Y * _speed;
}

void Enemy::Draw(Window window)
{
    // Set rotation according to the direction
    float angle = atan2(_direction.Y, _direction.X) + 180.f;

    _image.SetRotation(angle);

    window.DrawImage(_image, _position.X, _position.Y, Pivot::Center);
}