#include "Player.h"

#include "Input.h"

Player::Player() : _image("../assets/player.png")
{
    _position = { 0, 0 };
    _image.SetColor(0xFF4444FF);
}

void Player::Update()
{
    if (Input::IsKeyHeld(KB_KEY_A))
    {
        _position.X -= _speed;
    }
    else if (Input::IsKeyHeld(KB_KEY_D))
    {
        _position.X += _speed;
    }
}

void Player::Draw(Window &window)
{
    window.DrawImage(_image, _position.X, _position.Y, Pivot::Center);
}