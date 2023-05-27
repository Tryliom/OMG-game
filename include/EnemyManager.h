#pragma once

#include "Enemy.h"

class EnemyManager
{
public:
	EnemyManager();

private:
	Enemy _enemies[50];
	uint32_t _enemyCount = 0;

public:
	void Update(uint32_t width, uint32_t height);
	void Draw(Window& window);

	void AddEnemy(Enemy enemy);

	void CheckCollision(Vector2F position, float radius);

	[[nodiscard]] uint32_t GetEnemyCount() const { return _enemyCount; }
	Enemy* GetEnemies() { return _enemies; }
};
