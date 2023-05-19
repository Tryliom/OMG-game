#include "../include/Window.h"

int main()
{
    const uint32_t width = 640;
    const uint32_t height = 640;

    Window window(width, height);
	Image bull("assets/bull.png");

    do {
		auto frame = window.GetFrame() % width;
		//window.DrawCustom();
		window.DrawImage(bull, frame, frame, Pivot::Center);

        window.Update();
    }
    while (window.IsOpen());
}
