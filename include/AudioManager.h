#pragma once

#include <vector>

struct Sample
{
    std::vector<float> Data;
    int FrameCount;
    bool Repeat;
};

enum class AudioType
{
    Shoot,
    BlackHole,
    Swallow,
    MainMusic
};

namespace AudioManager
{
    void Init();
    void Play(AudioType audioType);
    Sample LoadSample(const char* path);
}