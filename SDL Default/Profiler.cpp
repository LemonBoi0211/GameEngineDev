#include "Profiler.h"



ProfilerSystem g_profileManager = ProfilerSystem();

void ProfilerSystem::storeSample(const char* name, __int64 elapsedTime)
{
    SampleData* sample = new SampleData();
    sample->frameReference = currentFrame;
    sample->functionTime = elapsedTime;

    frameData[name].push_back(sample);
}

ProfilerSystem::ProfilerSystem()
{
}

ProfilerSystem::~ProfilerSystem()
{
} 

void ProfilerSystem::startFrame()
{
}

void ProfilerSystem::endFrame()
{
}
