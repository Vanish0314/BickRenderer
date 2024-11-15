/*
 * @Author: Vanish
 * @Date: 2024-09-14 15:31:38
 * @LastEditTime: 2024-11-15 14:26:31
 * Also View: http://vanishing.cc
 * Copyright@ https://creativecommons.org/licenses/by/4.0/deed.zh-hans
 */
#pragma once

#include <map>
#include <memory>

#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "Common/Singleton.hpp"
#include "Camera/Camera.hpp"

class Mouse
{
    friend class Singleton<Mouse>;
private: 
    int lastX = 0, lastY = 0;
    int x , y ;
public: 
    /// @brief 移动多少像素,才移动1度
    int horizontalSensitivity = 10;
    int verticalSensitivity   = 10;
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
    void UpdatePerFrame();
    void UpdatePosition(int x, int y);    //像素位置
    void UpdateButton(bool left, bool wheelPressed, bool right);
    void UpdateScroll(int scroll);
public:
    void MoveCamera();
};

enum KeyCode
{
    W,
    A,
    S,
    D,
    ESC,
    C,
    SPACE,
    LEFT_ALT
};
class KeyBoard
{
    friend class Singleton<KeyBoard>;
private: 
    KeyBoard  ()            ;
    KeyBoard  (const KeyBoard&) = delete;
    KeyBoard& operator       = (const KeyBoard&) = delete;
    ~KeyBoard()              = default;
public:
    std::map<KeyCode,bool> m_keys;
public: 
    void Update();
};


class InputSystem
{
    friend class Singleton<InputSystem>;
private: 
    InputSystem ()                   = default;
    InputSystem (const InputSystem&) = delete;
    InputSystem& operator            = (const InputSystem&) = delete;
    ~InputSystem()                   = default;
private:
    GLFWwindow  *m_window;
public:
    /// @brief 不要释放指针
    /// @return 
    GLFWwindow* GetWindow() const { return m_window; }
public: 
    Mouse& mouse = Singleton<Mouse>::Instance();
    KeyBoard& keyboard = Singleton<KeyBoard>::Instance();
public:
    void Init(GLFWwindow *window);
public:
    void Update();
    static void MouseUpdateCallBack(GLFWwindow* window,double xpos,double ypos);
};