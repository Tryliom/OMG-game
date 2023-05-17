#include "../include/Window.h"

int main()
{
    const uint32_t width = 640;
    const uint32_t height = 640;

    Window window(width, height);

    int frame = 0;
    do {
        frame++;

        int size = 30;
        int offset = frame % (width - size);

        window.DrawFullRectangle(offset, offset, size, size, Color::Blue);

        int lineOffset = frame % width;

        window.DrawVerticalLine(lineOffset, 0, lineOffset, Color::Green);
        window.DrawHorizontalLine(0, lineOffset, lineOffset, Color::Red);

        window.Update();
    }
    while (window.IsOpen());
}
