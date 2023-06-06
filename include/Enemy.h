#pragma once

#include "Utility.h"
#include "Image.h"

struct Window;

class Enemy
{
public:
    Enemy();

private:
    Vector2F _position{};

    float _speed = 300.f;
    Vector2F _direction = { 0.f, 0.f };

	bool _isSwallowed = false;
	bool _isDead = false;
	Vector2F _swallowTarget = {};
	float _swallowDistance = 0.f;

public:
	static Image Sprite;

    void Update();
    void Draw(Window& window);

	void Swallow(Vector2F target);
	[[nodiscard]] bool IsSwallowed() const { return _isSwallowed; }

    Vector2F GetPosition() { return _position; }
    void SetPosition(Vector2F position) { _position = position; }

    void SetDirection(Vector2F direction) { _direction = direction; }

	[[nodiscard]] bool IsDead() const { return _isDead; }
};
