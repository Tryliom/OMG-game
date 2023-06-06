#include "Grenade.hpp"

#include "Timer.hpp"

#ifdef EMSCRIPTEN
#define IMG_PATH "assets/grenade.png"
#else
#define IMG_PATH "../assets/grenade.png"
#endif

Image Grenade::Sprite(IMG_PATH);

Grenade::Grenade()
{
    _position = { 0, 0 };
}

void Grenade::Update()
{
    _position.X += _direction.X * _speed * Timer::GetDeltaTime();
    _position.Y += _direction.Y * _speed * Timer::GetDeltaTime();
}

void Grenade::Draw(Window& window) const
{
    Sprite.SetRotation(Sprite.GetRotation() + 10.f);

    window.DrawImage(Sprite, _position.X, _position.Y, Pivot::Center);
}