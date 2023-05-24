#pragma once

#include <stdint.h>

enum Color
{
    Black = 0x000000,
    White = 0xFFFFFF,
    Red = 0xFF0000,
    Green = 0x00FF00,
    Blue = 0x0000FF
};

enum Pivot
{
    TopLeft,
    Center
};

struct Vector2I
{
    int X;
    int Y;
};

struct Vector2F
{
    float X;
    float Y;
};