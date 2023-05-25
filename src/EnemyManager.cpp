#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
	Enemy::Sprite.SetColor(0xFFFF3355);
}

void EnemyManager::Update(uint32_t width, uint32_t height)
{
    for (uint32_t i = 0; i < _enemyCount; i++)
	{
		_enemies[i].Update();

		// Check if enemy is out of bounds
		auto position = _enemies[i].GetPosition();

		if (position.X < 0 || position.X > width || position.Y > height)
		{
			_enemies[i] = _enemies[_enemyCount - 1];
			_enemyCount--;
			i--;
		}
	}
}

void EnemyManager::Draw(Window& window)
{
	for (uint32_t i = 0; i < _enemyCount; i++)
	{
		_enemies[i].Draw(window);
	}
}

void EnemyManager::AddEnemy(Enemy enemy)
{
	_enemies[_enemyCount] = enemy;
	_enemyCount++;
}