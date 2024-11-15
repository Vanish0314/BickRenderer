/*
 * @Author: Vanish
 * @Date: 2024-09-14 15:31:32
 * @LastEditTime: 2024-11-15 15:30:41
 * Also View: http://vanishing.cc
 * Copyright@ https://creativecommons.org/licenses/by/4.0/deed.zh-hans
 */
#include <iostream>
#include "Input/InputSystem.hpp"

void Mouse::UpdatePerFrame()
{
    lastX = x;
    lastY = y;
}

void Mouse::UpdatePosition(int x, int y)
{
    lastX = this->x;
    lastY = this->y;
    this->x = x;
    this->y = y;
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
void Mouse::MoveCamera()
{
    float xAngle,yAngle;
    float xOffset = x - lastX;
    float yOffset = y - lastY;
    
    float sentivity = 0.05f;
    xOffset *= sentivity;
    yOffset *= sentivity;
    xAngle = -xOffset;
    yAngle = yOffset;

    lastX = x;
    lastY = y;

    Camera::main->Rotate(xAngle, yAngle);
#ifdef STD_COUT
    if(yAngle != 0.0f || xAngle != 0.0f)
    {
        std::cout<<"摄像机视角更新"<<std::endl;
        std::cout<<"移动角度:"<<xAngle<<","<<yAngle<<std::endl;
        std::cout<<"摄像机角度:"<<Camera::main->yaw<<","<<Camera::main->pitch<<std::endl;
        std::cout<<"视角方向:"<<Camera::main->forward.x<<","<<Camera::main->forward.y<<","<<Camera::main->forward.z<<std::endl;
    }
#endif
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
    m_keys[KeyCode::LEFT_ALT] = false;
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
    this->m_keys.at(KeyCode::LEFT_ALT) = glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS;
}

void InputSystem::Init(GLFWwindow *window)
{
    m_window = window;
    glfwSetCursorPosCallback(window, MouseUpdateCallBack);
}

void InputSystem::Update()
{
    glm::vec3 input = glm::vec3(0.0f);
    keyboard.Update();
    glm::vec3 forward = Camera::main->forward;
    glm::vec3 right = Camera::main->right;    
    glm::vec3 up = Camera::main->up;          

    input.x = (keyboard.m_keys.at(KeyCode::A) ? -1.0f : 0.0f) + (keyboard.m_keys.at(KeyCode::D) ? 1.0f : 0.0f);
    input.y = (keyboard.m_keys.at(KeyCode::SPACE) ? 1.0f : 0.0f) + (keyboard.m_keys.at(KeyCode::C) ? -1.0f : 0.0f);
    input.z = (keyboard.m_keys.at(KeyCode::W) ? 1.0f : 0.0f) + (keyboard.m_keys.at(KeyCode::S) ? -1.0f : 0.0f);

    glm::vec3 move = (forward * input.z + right * input.x + up * input.y) * 0.01f;
    Camera::main->Move(move);

    if (keyboard.m_keys.at(KeyCode::LEFT_ALT))
        mouse.MoveCamera();
}

void InputSystem::MouseUpdateCallBack(GLFWwindow *window,double xpos,double ypos)
{
    Singleton<InputSystem>::Instance().mouse.UpdatePosition(xpos,ypos);
}
