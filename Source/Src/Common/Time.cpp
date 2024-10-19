#include "Common/Time.hpp"

float Time::frameDeltaTime = 0.02f;
float Time::lastFrameTime = 0.0f;
float Time::curTime = 0.0f;

void Time::Update()
{
    float currentTime = (float)glfwGetTime();
    frameDeltaTime = currentTime - lastFrameTime;
    lastFrameTime = currentTime;
    curTime = currentTime;
}

float Time::GetCurTime()
{
    return curTime;
}