/*
 * @Author: Vanish
 * @Date: 2024-09-14 15:31:32
 * @LastEditTime: 2024-10-11 22:13:52
 * Also View: http://vanishing.cc
 * Copyright@ https://creativecommons.org/licenses/by/4.0/deed.zh-hans
 */
#include "Input/InputSystem.hpp"

void Mouse::UpdatePosition(int x, int y)
{
    if(lastX == -1 || lastY == -1)
    {
        lastX = x;
        lastY = y;
        mouseBias = glm::vec2(0.0f);
        return;
    }
    mouseBias = glm::vec2(x - lastX, y - lastY);
    if(glm::length(mouseBias) < 2)
        mouseBias = glm::vec2(0.0f);
    lastX = x;
    lastY = y;
    x = 0;
    y = 0;
}

void Mouse::UpdateButton(bool left,bool wheelPressed,bool right)
{
    leftButtonPressed = left;
    wheelPressed = wheelPressed;
    rightButtonPressed = right;
}

void Mouse::UpdateScroll(int scroll)
{
    this->scroll = scroll;
}