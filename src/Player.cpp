#include "Player.h"

#include "Input.h"
#include "Timer.h"

#define IMG_PATH "../assets/player.png"

Player::Player() : _image(IMG_PATH)
{
    _position = { 0, 0 };
    _image.SetColor(0xFF4444FF);
}

void Player::Update()
{
    if (Input::IsKeyHeld(KB_KEY_A))
    {
        _position.X -= _speed * Timer::GetSmoothDeltaTime();
    }
    else if (Input::IsKeyHeld(KB_KEY_D))
    {
        _position.X += _speed * Timer::GetSmoothDeltaTime();
    }
}

void Player::Draw(Window &window)
{
    window.DrawImage(_image, _position.X, _position.Y, Pivot::Center);
}