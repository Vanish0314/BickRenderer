#pragma once

#include "glm/glm.hpp"
#include "Common/Singleton.hpp"

class Mouse
{
    friend class Singleton<Mouse>;
private: 
    int lastX = -1, lastY = -1;
    int x , y ;
public: 
    double horizontalSensitivity = 1.0;
    double verticalSensitivity   = 1.0;
public: 
    bool leftButtonPressed  = false;
    bool rightButtonPressed = false;
    bool wheelPressed       = false;
    int  scroll             = 0;
    glm::vec2 mouseBias     = glm::vec2(0.0f, 0.0f);

private: 
    Mouse  ()             = default;
    Mouse  (const Mouse&) = delete;
    Mouse& operator       = (const Mouse&) = delete;
    ~Mouse()              = default;

public: 
    void UpdatePosition(int x, int y);    //像素位置
    void UpdateButton(bool left, bool wheelPressed, bool right);
    void UpdateScroll(int scroll);
};

class InputSystem
{
    friend class Singleton<InputSystem>;
private: 
    InputSystem ()                   = default;
    InputSystem (const InputSystem&) = delete;
    InputSystem& operator            = (const InputSystem&) = delete;
    ~InputSystem()                   = default;
public: 
    Mouse& mouse = Singleton<Mouse>::Instance();
};