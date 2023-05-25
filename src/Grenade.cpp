#include "Grenade.h"

Image Grenade::Sprite("../assets/grenade.png");

Grenade::Grenade()
{
    _position = { 0, 0 };
}

void Grenade::Update()
{
    _position.X += _direction.X * _speed;
    _position.Y += _direction.Y * _speed;
}

void Grenade::Draw(Window& window) const
{
    Sprite.SetRotation(Sprite.GetRotation() + 10.f);

    window.DrawImage(Sprite, _position.X, _position.Y, Pivot::Center);
}