mkdir bin

clang++ src/main.cpp src/Window.cpp src/Image.cpp src/Input.cpp src/Player.cpp src/Enemy.cpp ^
    -o bin/game.exe ^
    -std=c++20 ^
    -Wall -Wextra ^
    -I libs/include ^
    libs/win-x64/minifb.lib ^
    -lkernel32 -luser32 -lshell32 -ldxgi -ld3d11 -lole32 -lgdi32 -lwinmm -lopengl32

bin\game.exe