#include "../include/Input.h"

#include "MiniFB.h"
#include <functional>
#include <iostream>

bool _keys[KB_KEY_LAST + 1];
bool _previousKeys[KB_KEY_LAST + 1];

bool _mouseButtons[MOUSE_BTN_7 + 1];
bool _previousMouseButtons[MOUSE_BTN_7 + 1];

void OnKey(struct mfb_window *, mfb_key key, mfb_key_mod, bool pressed)
{
    _keys[key] = pressed;
}

void OnMouse(struct mfb_window *, mfb_mouse_button button, mfb_key_mod, bool pressed)
{
    _mouseButtons[button] = pressed;
}

namespace Input
{
    void Initialize(struct mfb_window* window)
    {
        using namespace std::placeholders;

        mfb_set_keyboard_callback(window, OnKey);
        mfb_set_mouse_button_callback(window, OnMouse);
    }

    void Update()
    {
        memcpy(_previousKeys, _keys, sizeof(_keys));
        memcpy(_previousMouseButtons, _mouseButtons, sizeof(_mouseButtons));
    }

    bool IsKeyPressed(int key)
    {
        return _keys[key] && !_previousKeys[key];
    }

    bool IsKeyReleased(int key)
    {
        return !_keys[key] && _previousKeys[key];
    }

    bool IsKeyHeld(int key)
    {
        return _keys[key];
    }

    bool IsMouseButtonPressed(int button)
    {
        return _mouseButtons[button] && !_previousMouseButtons[button];
    }

    bool IsMouseButtonReleased(int button)
    {
        return !_mouseButtons[button] && _previousMouseButtons[button];
    }

    bool IsMouseButtonHeld(int button)
    {
        return _mouseButtons[button];
    }
}