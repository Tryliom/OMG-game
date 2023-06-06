call C:\tools\emsdk\emsdk_env.bat

mkdir bin

call C:\tools\emsdk\upstream\emscripten\em++ src\Window.cpp src\AudioManager.cpp src\BlackHole.cpp src\Enemy.cpp src\EnemyManager.cpp src\Grenade.cpp src\Image.cpp src\Input.cpp src\Player.cpp src\Timer.cpp src\Utility.cpp src\main.cpp ^
    -o bin/game.js ^
    -std=c++20 ^
    -Wall -Wextra ^
    -I libs/include ^
    -I include ^
    libs/web/libminifb.a ^
    -fcolor-diagnostics ^
    -fansi-escape-codes ^
    -sEXPORT_NAME=my_game ^
    -sASYNCIFY ^
    --preload-file assets ^
    -sSTRICT=1 ^
    -sENVIRONMENT=web ^
    -sMODULARIZE=1 ^
    -sALLOW_MEMORY_GROWTH=1 ^
    -sALLOW_TABLE_GROWTH ^
    -sMALLOC=emmalloc ^
    -sEXPORT_ALL=1 ^
    -sEXPORTED_FUNCTIONS=[\"_malloc\",\"_free\",\"_main\"] ^
    -sEXPORTED_RUNTIME_METHODS=ccall,cwrap ^
    -sASYNCIFY ^
    --no-entry ^
    -O3

python3 -m http.server 8000