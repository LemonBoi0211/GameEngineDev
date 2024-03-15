#pragma once
#include "SDL.h"
#include <map>
#include <vector>

#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>

/// @brief data that would be stored from a sample snapshot
struct SampleData
{
    __int64 functionTime;
    int frameReference;
};

typedef std::map<const char*, std::vector<SampleData*>> FrameMap;



class ProfilerSystem
{
public:
    ProfilerSystem();
    ~ProfilerSystem();

    void startFrame();
    void storeSample(const char* name, __int64 elapsedTime);
    void endFrame();

private:

    int currentFrame;
    FrameMap frameData;
};

extern ProfilerSystem g_profileManager;

struct Profile
{
    Profile(const char* name)
    {
        _name = name;
        LARGE_INTEGER li;
        QueryPerformanceCounter(&li);
        startTime = li.QuadPart;
    }

    ~Profile()
    {
        LARGE_INTEGER li;
        QueryPerformanceCounter(&li);
        __int64 endTime = li.QuadPart;
        __int64 elapsedTime = endTime - startTime;
        g_profileManager.storeSample(_name, elapsedTime);
    }

    const char* _name;
    __int64 startTime;
};
#define PROFILE(name) Profile p(name)
