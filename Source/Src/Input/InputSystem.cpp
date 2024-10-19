/*
 * @Author: Vanish
 * @Date: 2024-09-14 15:31:32
 * @LastEditTime: 2024-10-19 21:14:07
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

KeyBoard::KeyBoard()
{
    m_keys[KeyCode::ESC] = false;
    m_keys[KeyCode::W] = false;
    m_keys[KeyCode::A] = false;
    m_keys[KeyCode::S] = false;
    m_keys[KeyCode::D] = false;
    m_keys[KeyCode::SPACE] = false;
    m_keys[KeyCode::C] = false;
}

void KeyBoard::Update()
{
    GLFWwindow *window = Singleton<InputSystem>::Instance().GetWindow();
    this->m_keys.at(KeyCode::ESC) = glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS;
    this->m_keys.at(KeyCode::W) = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
    this->m_keys.at(KeyCode::A) = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
    this->m_keys.at(KeyCode::S) = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
    this->m_keys.at(KeyCode::D) = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
    this->m_keys.at(KeyCode::SPACE) = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
    this->m_keys.at(KeyCode::C) = glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS;
}

void InputSystem::Init(GLFWwindow *window)
{
    m_window = window;
    glfwSetCursorPosCallback(window, MouseUpdateCallBack);
}

void InputSystem::Update()
{
    glm::vec2 input = glm::vec2(0.0f);
    keyboard.Update();
    input.x = - (keyboard.m_keys.at(KeyCode::A)?1.0f:0.0f + keyboard.m_keys.at(KeyCode::D)?-1.0f:0.0f);
    input.y = - (keyboard.m_keys.at(KeyCode::W)?1.0f:0.0f + keyboard.m_keys.at(KeyCode::S)?-1.0f:0.0f);

    glm::vec2 view  = glm::vec2(Singleton<InputSystem>::Instance().mouse.mouseBias.x,Singleton<InputSystem>::Instance().mouse.mouseBias.y) / glm::vec2(100.0f, 100.0f);
    Camera::main->Move(glm::vec3(input.x, 0.0f, input.y) * (Camera::main->speed / 100));
    Camera::main->Rotate(view.x, view.y);

}

void InputSystem::MouseUpdateCallBack(GLFWwindow *window,double xpos,double ypos)
{
    Singleton<InputSystem>::Instance().mouse.UpdatePosition(xpos,ypos);
}