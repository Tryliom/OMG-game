#include "Window.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "Utility.h"
#include "Input.h"

int main()
{
    const uint32_t width = 640;
    const uint32_t height = 640;

    int spawnRate = 200;

    Window window(width, height);
	Player player;
	EnemyManager enemyManager;

    window.SetBackgroundColor(Color::White);
    player.SetPosition({ width / 2.f, height - 80.f });

    do {
		auto frame = window.GetFrame();

        if (frame % spawnRate == 0)
        {
            Enemy enemy;

            enemy.SetPosition({ Utility::Range(50.f, (float) width - 50.f), - Utility::Range(50.f, 100.f) });
            enemy.SetDirection(Utility::GetDirection((Vector2F) enemy.GetPosition(), (Vector2F) player.GetPosition()));

            enemyManager.AddEnemy(enemy);

            if (spawnRate > 60)
            {
                spawnRate -= 1;
            }
        }

		player.Update();
        player.Draw(window);

		enemyManager.Update(width, height);
		enemyManager.Draw(window);

        window.Update();
    }
    while (window.IsOpen());
}
