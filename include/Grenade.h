#pragma once

#include "Image.h"
#include "Vector.h"
#include "Window.h"

class Grenade
{
public:
    Grenade();

private:
    static Image Sprite;

    Vector2F _position {};
    Vector2F _direction = { 0.f, 0.f };

    float _speed = 600.f;

    bool _isExploded = true;

public:
    void Update();
    void Draw(Window& window) const;

    Vector2F GetPosition() { return _position; }
    void SetPosition(Vector2F position) { _position = position; }

    void SetDirection(Vector2F direction) { _direction = direction; }

    bool IsExploded() { return _isExploded; }
    void SetExploded(bool isExploded) { _isExploded = isExploded; }
};