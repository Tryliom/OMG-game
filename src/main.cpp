#include "../include/Window.h"

int main()
{
    const uint32_t width = 640;
    const uint32_t height = 640;

    Window window(width, height);

    do {
		window.DrawCustom();

        window.Update();
    }
    while (window.IsOpen());
}
