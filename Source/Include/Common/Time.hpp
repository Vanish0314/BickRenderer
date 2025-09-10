#pragma once

#include <GLFW/glfw3.h>

class Time
{
public:
    static float frameDeltaTime;
private:
    static float lastFrameTime;
    static float curTime;
public:
    static void Update();
    static float GetCurTime();
};