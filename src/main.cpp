#include "Window.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "Utility.h"

int main()
{
    const uint32_t width = 640;
    const uint32_t height = 640;

    Window window(width, height);
	Player player;
	EnemyManager enemyManager;

    player.SetPosition({ width / 2, height - 80 });

    do {
		auto frame = window.GetFrame();

		if (frame % 200 == 0)
		{
			Enemy enemy;

			enemy.SetPosition({ Utility::Range(0, width), 100 });
			enemy.SetDirection(Utility::GetDirection((Vector2F) enemy.GetPosition(), (Vector2F) player.GetPosition()));

			enemyManager.AddEnemy(enemy);
		}

		player.Update();
        player.Draw(window);

		enemyManager.Update(width, height);
		enemyManager.Draw(window);

        window.Update();
    }
    while (window.IsOpen());
}
