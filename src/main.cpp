#include "Window.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "Utility.h"
#include "Input.h"
#include "Grenade.h"
#include "BlackHole.h"

int main()
{
    const uint32_t width = 640;
    const uint32_t height = 640;

    int spawnRate = 200;

    Window window(width, height);
	Player player;
	EnemyManager enemyManager;
    Grenade grenade;
	BlackHole blackHole;

    player.SetPosition({ width / 2.f, height - 80.f });

    do {
		auto frame = window.GetFrame();

		// Make the background color change over time
		window.SetBackgroundColor(Utility::ToColor(0, 20, 70) - Utility::ToColor(0, 0, (int) (sin(frame * 0.005f) * 10.f)));

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

        if ((Input::IsMouseButtonPressed(MOUSE_LEFT) || Input::IsKeyPressed(KB_KEY_SPACE)) && !blackHole.IsActive())
        {
            if (grenade.IsExploded())
            {
                grenade.SetPosition(player.GetPosition());
                grenade.SetDirection(Utility::GetDirection(player.GetPosition(), player.GetPosition() + Vector2F{ 0.f, -100.f }));
                grenade.SetExploded(false);
            }
            else
            {
                grenade.SetExploded(true);

				blackHole.Reset();
				blackHole.SetPosition(grenade.GetPosition());
            }
        }

        if (!grenade.IsExploded())
        {
            grenade.Update();
            grenade.Draw(window);

            if (grenade.GetPosition().Y < 0.f)
            {
                grenade.SetExploded(true);
            }
        }

		if (blackHole.IsActive())
		{
			blackHole.Update();
			blackHole.Draw(window);

			enemyManager.CheckCollision(blackHole.GetPosition(), blackHole.GetRadius());
		}

		player.Update();
        player.Draw(window);

		enemyManager.Update(width, height);
		enemyManager.Draw(window);

        window.Update();
    }
    while (window.IsOpen());
}
