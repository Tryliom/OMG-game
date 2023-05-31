#include <cassert>
#include <map>
#include <iostream>

#include "AudioManager.h"

#define SOKOL_IMPL
#include "sokol_log.h"
#include "sokol_audio.h"

#include "stb_vorbis.c"
#include "stb_vorbis.h"

float volume = 1.f;
std::vector<Sample> audioBuffers = {};
std::map<AudioType, Sample> audioSamples = {};

void audioCallback(float* buffer, int numFrames, int numChannels)
{
    assert(numChannels == 1);

    for (auto frame = 0; frame < numFrames; frame++)
    {
        float currentSample = 0.f;

        for (auto i = 0; i < audioBuffers.size(); i++)
        {
            auto& audioBuffer = audioBuffers[i];

            currentSample += audioBuffer.Data[audioBuffer.FrameCount];
            audioBuffer.FrameCount++;

            if (audioBuffer.FrameCount >= audioBuffer.Data.size())
            {
                if (audioBuffer.Repeat)
                {
                    audioBuffer.FrameCount = 0;
                }
                else
                {
                    // Remove audio buffer
                    audioBuffers.erase(audioBuffers.begin() + i);
                    i--;
                }
            }
        }

        buffer[frame] = currentSample * volume;
    }
}

namespace AudioManager
{
    void Init()
    {
        saudio_setup((saudio_desc)
        {
            .stream_cb = audioCallback,
            .logger =
            {
                .func = slog_func
            }
        });

        audioSamples[AudioType::Shoot] = AudioManager::LoadSample("../assets/sounds/shoot.ogg");
        audioSamples[AudioType::BlackHole] = AudioManager::LoadSample("../assets/sounds/blackHole.ogg");
        audioSamples[AudioType::Swallow] = AudioManager::LoadSample("../assets/sounds/swallow.ogg");
        audioSamples[AudioType::MainMusic] = AudioManager::LoadSample("../assets/sounds/mainMusic.ogg");
        audioSamples[AudioType::MainMusic].Repeat = true;
    }

    void Play(AudioType audioType)
    {
        audioBuffers.push_back(audioSamples[audioType]);
    }

    Sample LoadSample(const char* path)
    {
        Sample sample = {};

        // Get sample data from ogg file
        stb_vorbis* vorbis = stb_vorbis_open_filename(path, nullptr, nullptr);
        if (vorbis == nullptr)
        {
            std::cout << "Failed to load sample: " << path << std::endl;
            return sample;
        }

        stb_vorbis_info info = stb_vorbis_get_info(vorbis);

        int channels = info.channels;
        int sampleRate = info.sample_rate;

        int sampleCount = stb_vorbis_stream_length_in_samples(vorbis) * channels;

        auto* samples = new float[sampleCount];
        int sampleIndex = 0;

        while (true)
        {
            int readSamples = stb_vorbis_get_samples_float_interleaved(vorbis, channels, samples + sampleIndex, sampleCount - sampleIndex);
            sampleIndex += readSamples * channels;

            // Add all channels together
            for (auto i = 0; i < readSamples; i++)
            {
                float sampleValue = 0.f;
                for (auto channel = 0; channel < channels; channel++)
                {
                    sampleValue += samples[i * channels + channel];
                }
                samples[i] = sampleValue / channels;
            }

            if (readSamples == 0)
            {
                break;
            }
        }

        stb_vorbis_close(vorbis);

        sample.Data = std::vector<float>(samples, samples + sampleCount);
        sample.FrameCount = 0;
        sample.Repeat = false;

        return sample;
    }
}