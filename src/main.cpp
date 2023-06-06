#include "Window.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "EnemyManager.hpp"
#include "Utility.hpp"
#include "Input.hpp"
#include "Grenade.hpp"
#include "BlackHole.hpp"
#include "AudioManager.hpp"

const uint32_t width = 640;
const uint32_t height = 640;

int spawnRate = 200;
int enemyPerSpawn = 1;
int life = 3;
int score = 0;

int invincibleTimer = 0;

Window window(width, height);
Player player;
EnemyManager enemyManager;
Grenade grenade;
BlackHole blackHole;

void SpawnEnemy()
{
	auto maxEnemyPerSpawn = Utility::Range(1, enemyPerSpawn);

	for (int i = 0; i < maxEnemyPerSpawn; i++)
	{
		Enemy enemy;
		Vector2F targetPosition = {Utility::Range(50.f, (float) width - 50.f), player.GetPosition().Y };

		enemy.SetPosition({ Utility::Range(50.f, (float) width - 50.f), - Utility::Range(50.f, 100.f) });
		enemy.SetDirection(Utility::GetDirection(enemy.GetPosition(), targetPosition));

		enemyManager.AddEnemy(enemy);
	}

	if (spawnRate > 60 && Utility::Range(0, 100) < 10)
	{
		spawnRate -= 1;

		if (enemyPerSpawn < 5 && Utility::Range(0, 100) < 10)
		{
			enemyPerSpawn++;
		}
	}
}

bool CanShoot()
{
	return (Input::IsMouseButtonPressed(MOUSE_LEFT) || Input::IsKeyPressed(KB_KEY_SPACE)) && !blackHole.IsActive();
}

void OnShoot()
{
	if (grenade.IsExploded())
	{
        AudioManager::Play(AudioType::Shoot);

		grenade.SetPosition(player.GetPosition());
		grenade.SetDirection(Utility::GetDirection(player.GetPosition(), player.GetPosition() + Vector2F{ 0.f, -100.f }));
		grenade.SetExploded(false);
	}
	else
	{
        AudioManager::Play(AudioType::BlackHole);

		grenade.SetExploded(true);

		blackHole.Reset();
		blackHole.UpdateMaxScale(score);
		blackHole.SetPosition(grenade.GetPosition());
	}
}

void CheckGrenade()
{
	if (!grenade.IsExploded())
	{
		grenade.Update();
		grenade.Draw(window);

		if (grenade.GetPosition().Y < 0.f)
		{
			grenade.SetExploded(true);
		}
	}
}

void CheckBlackHole()
{
	if (blackHole.IsActive())
	{
		blackHole.Update();
		blackHole.Draw(window);

		enemyManager.CheckCollisionWithBlackHole(blackHole.GetPosition(), blackHole.GetRadius());
	}
}

void Reset()
{
	spawnRate = 200;
	life = 3;
	score = 0;
	enemyPerSpawn = 1;
	invincibleTimer = 0;

	enemyManager.Clear();
	player.SetPosition({ width / 2.f, height - 80.f });
}

void OnEnemySwallowed(Enemy enemy)
{
	score += 10;

	if (score % 300 == 0)
	{
		life++;
	}
}

int main()
{
	Reset();
	enemyManager.SetOnEnemySwallowed(OnEnemySwallowed);
    AudioManager::Init();
    AudioManager::Play(AudioType::MainMusic, true);

    do {
		auto frame = window.GetFrame();

		// Make the background color change over time
		window.SetBackgroundColor(Utility::ToColor(0, 20, 70) - Utility::ToColor(0, 0, (int) (sin(frame * 0.005f) * 10.f)));

		if (life > 0)
		{
			if (frame % spawnRate == 0) SpawnEnemy();
			if (CanShoot()) OnShoot();

			CheckGrenade();
			CheckBlackHole();

			player.Update();

			auto playerPosition = player.GetPosition();

			if (playerPosition.X < 0.f) playerPosition.X = 0.f;
			if (playerPosition.X > width) playerPosition.X = width;

			player.SetPosition(playerPosition);

			player.Draw(window);

			enemyManager.Update(width, height);
			enemyManager.Draw(window);

			// Draw texts
			window.DrawText({.Text = "Life: " + std::to_string(life), .Position = {10, 10}, .Pivot = Pivot::TopLeft});
			window.DrawText({.Text = std::to_string(score) + " PTS", .Position = {width - 10, 10}, .Pivot = Pivot::TopRight});

			if (enemyManager.HasCollidedAt(player.GetPosition(), 40) && invincibleTimer == 0)
			{
				life--;
				invincibleTimer = 60;
			}

			invincibleTimer = std::max(0, invincibleTimer - 1);
		}
		else
		{
			// Draw things without updating
			player.Draw(window);
			enemyManager.Draw(window);

			window.DrawText({.Text = "GAME OVER", .Size = 40.f, .Position = {width / 2, height / 2}, .Pivot = Pivot::Center});
			window.DrawText({.Text = "Press R to restart", .Position = {width / 2, height / 2 + 50}, .Pivot = Pivot::Center});

			if (Input::IsKeyPressed(KB_KEY_R))
			{
				Reset();
			}
		}

	    window.Update();
    }
    while (window.IsOpen());
}