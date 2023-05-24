#include "../include/Window.h"
#include "../include/Input.h"
#include "../include/Player.h"
#include "../include/Enemy.h"

int main()
{
    const uint32_t width = 640;
    const uint32_t height = 640;

    Window window(width, height);
	Player player;
    Enemy enemy;

    player.SetPosition({ width / 2, height - 80 });
    enemy.SetPosition({ width / 2, -100 });
    enemy.SetDirection({ 0.f, 1.f });

    enemy.Initialize();

    do {
		player.Update();
        player.Draw(window);

        enemy.Update();
        enemy.Draw(window);

        window.Update();
    }
    while (window.IsOpen());
}
