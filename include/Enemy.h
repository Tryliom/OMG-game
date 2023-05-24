#pragma once

#include "Utility.h"
#include "Image.h"
#include "Window.h"

class Enemy
{
public:
    Enemy();

private:
    static Image _image;
    Vector2I _position;

    float _speed = 2.f;
    Vector2F _direction = { 0.f, 1.f };

public:
    void Initialize();
    void Update();
    void Draw(Window window);

    Vector2I GetPosition() { return _position; }
    void SetPosition(Vector2I position) { _position = position; }

    Vector2F GetDirection() { return _direction; }
    void SetDirection(Vector2F direction) { _direction = direction; }
};
