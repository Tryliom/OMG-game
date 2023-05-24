#include "../include/Window.h"

#include <iostream>

int main()
{
    const uint32_t width = 640;
    const uint32_t height = 640;

    Window window(width, height);
	Image bull("assets/bull.png");

    do {
		auto mousePosition = window.GetMousePosition();

		window.DrawCustom();

		bull.SetScale(5.f + sin(window.GetFrame() / 10.f));
        bull.SetRotation(window.GetFrame() / 100.f);

		window.DrawImage(bull, mousePosition.X, mousePosition.Y, Pivot::Center);

        window.Update();
    }
    while (window.IsOpen());
}
