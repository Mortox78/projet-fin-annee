#include <stdlib.h>

#include <iostream>

#include "TimeManager.hpp"
using namespace Tools;

Time& Time::Summon()
{
    static Time timeManagment;

    return timeManagment;
}

Time::Time()
    : deltaTime(0), gameTime(0)
{
#if defined(WIN32) || defined(_WIN32)
    QueryPerformanceFrequency(&frequency);
    startCount.QuadPart = 0;
    endCount.QuadPart = 0;

#else
    startCount.tv_sec = startCount.tv_usec = 0;
    endCount.tv_sec = endCount.tv_usec = 0;

#endif

    stopped = 0;
    startTimeInMicroSec = 0;
    endTimeInMicroSec = 0;

    StartTimer();
}


void Time::Update()
{
    StopTimer();

    deltaTime = GetElapsedTimeInSec();
    gameTime = gameTime + deltaTime;

    StartTimer();
}


void Time::StartTimer()
{
    stopped = 0; // reset stop flag
#if defined(WIN32) || defined(_WIN32)
    QueryPerformanceCounter(&startCount);

#else
    gettimeofday(&startCount, NULL);

#endif
}

void Time::StopTimer()
{
    stopped = 1; // set time stopped flag

#if defined(WIN32) || defined(_WIN32)
    QueryPerformanceCounter(&endCount);

#else
    gettimeofday(&endCount, NULL);

#endif
}

double Time::GetElapsedTimeInMicroSec()
{
#if defined(WIN32) || defined(_WIN32)
    if(!stopped)
        QueryPerformanceCounter(&endCount);

    startTimeInMicroSec = startCount.QuadPart * (1000000.0 / frequency.QuadPart);
    endTimeInMicroSec   = endCount.QuadPart   * (1000000.0 / frequency.QuadPart);

#else
    if(!stopped)
        gettimeofday(&endCount, NULL);

    startTimeInMicroSec = (startCount.tv_sec * 1000000.0) + startCount.tv_usec;
    endTimeInMicroSec   = (endCount.tv_sec   * 1000000.0) + endCount.tv_usec;

#endif

    return endTimeInMicroSec - startTimeInMicroSec;
}

double Time::GetElapsedTimeInSec()
{ return GetElapsedTimeInMicroSec() * 0.000001; }