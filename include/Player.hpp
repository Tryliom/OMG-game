#pragma once

#include "Utility.hpp"
#include "Image.hpp"
#include "Window.hpp"

class Player
{
public:
    Player();

private:
    Image _image;
    Vector2F _position {};

    float _speed = 400.f;

public:
    void Update();
    void Draw(Window& window);

    Vector2F GetPosition() { return _position; }
    void SetPosition(Vector2F position) { _position = position; }

    void SetRotation(float rotation) { _image.SetRotation(rotation); }
};