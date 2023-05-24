#pragma once

#include "Utility.h"
#include "Image.h"
#include "Window.h"

class Enemy
{
public:
    Enemy();

private:
    Vector2I _position{};

    float _speed = 2.f;
    Vector2F _direction = { 0.f, 1.f };

public:
	static Image Sprite;

    void Update();
    void Draw(Window window) const;

    Vector2I GetPosition() { return _position; }
    void SetPosition(Vector2I position) { _position = position; }

    Vector2F GetDirection() { return _direction; }
    void SetDirection(Vector2F direction) { _direction = direction; }
};
