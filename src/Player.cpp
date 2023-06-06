#include "Player.hpp"

#include "Input.hpp"
#include "Timer.hpp"

#ifdef EMSCRIPTEN
#define IMG_PATH "assets/player.png"
#else
#define IMG_PATH "../assets/player.png"
#endif

Player::Player() : _image(IMG_PATH)
{
    _position = { 0, 0 };
    _image.SetColor(0xFF4444FF);
}

void Player::Update()
{
    if (Input::IsKeyHeld(KB_KEY_A))
    {
        _position.X -= _speed * Timer::GetDeltaTime();
    }
    else if (Input::IsKeyHeld(KB_KEY_D))
    {
        _position.X += _speed * Timer::GetDeltaTime();
    }
}

void Player::Draw(Window &window)
{
    window.DrawImage(_image, _position.X, _position.Y, Pivot::Center);
}