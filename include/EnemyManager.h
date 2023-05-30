#pragma once

#include "Enemy.h"

#include <functional>

class EnemyManager
{
public:
	EnemyManager();

private:
	Enemy _enemies[50];
	uint32_t _enemyCount = 0;

	std::function<void(Enemy)> _onEnemySwallowed = nullptr;
public:
	void Update(uint32_t width, uint32_t height);
	void Draw(Window& window);

	void AddEnemy(Enemy enemy);

	void CheckCollisionWithBlackHole(Vector2F position, float radius);
	bool HasCollidedAt(Vector2F position, float radius);

	void SetOnEnemySwallowed(std::function<void(Enemy)> onEnemySwallowed) { _onEnemySwallowed = onEnemySwallowed; }

	void Clear() { _enemyCount = 0; }
};
