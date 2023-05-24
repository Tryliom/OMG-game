#pragma once

#include "Utility.h"
#include "Image.h"
#include "Window.h"

class Player
{
public:
    Player();

private:
    Image _image;
    Vector2I _position;

    float _speed = 2.f;

public:
    void Update();
    void Draw(Window window);

    Vector2I GetPosition() { return _position; }
    void SetPosition(Vector2I position) { _position = position; }
};