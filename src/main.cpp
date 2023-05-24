#include "../include/Window.h"
#include "../include/Input.h"

#include <iostream>

int main()
{
    const uint32_t width = 640;
    const uint32_t height = 640;

    Window window(width, height);
	Image bull("assets/bull.png");
    Position bullPosition = { 0, 0 };

    do {
		window.DrawCustom();

		bull.SetScale(5.f + sin(window.GetFrame() / 10.f));
        bull.SetRotation(window.GetFrame() / 100.f);

        if (Input::IsKeyHeld(KB_KEY_A))
        {
            bullPosition.X -= 1;
        }
        else if (Input::IsKeyHeld(KB_KEY_D))
        {
            bullPosition.X += 1;
        }

        if (Input::IsKeyHeld(KB_KEY_W))
        {
            bullPosition.Y -= 1;
        }
        else if (Input::IsKeyHeld(KB_KEY_S))
        {
            bullPosition.Y += 1;
        }

		window.DrawImage(bull, bullPosition.X, bullPosition.Y, Pivot::Center);

        window.Update();
    }
    while (window.IsOpen());
}
