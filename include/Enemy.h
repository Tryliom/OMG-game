#pragma once

#include "Utility.h"
#include "Image.h"
#include "Window.h"

class Enemy
{
public:
    Enemy();

private:
    Vector2F _position{};

    float _speed = 2.f;
    Vector2F _direction = { 0.f, 0.f };

public:
	static Image Sprite;

    void Update();
    void Draw(Window& window) const;

    Vector2F GetPosition() { return _position; }
    void SetPosition(Vector2F position) { _position = position; }

    void SetDirection(Vector2F direction) { _direction = direction; }
};
