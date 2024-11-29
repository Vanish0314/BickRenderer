/*
 * @Author: Vanish
 * @Date: 2024-11-14 18:08:59
 * @LastEditTime: 2024-11-29 15:11:00
 * Also View: http://vanishing.cc
 * Contract Me: http://qunchengxiao.me
 * Copyright@ http://www.wtfpl.net/
 */
#pragma once

#include <iostream>
#include <filesystem>
#include <cmath>
#include "glad/glad.h" //glad 必须在Glfw前加载
#include "Glfw/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include "stb_image.h"

#include "Shader/Shader.hpp"
#include "Texture/Texture.hpp"
#include "Camera/Camera.hpp"
#include "Mesh/Model.hpp"
#include "Input/InputSystem.hpp"
#include "Light/Light.hpp"

#include "Renderer/RenderPass.hpp"


//设置程序运行目录
void SetRootPath()
{
    std::cout<<"当前工作目录为:"<<std::filesystem::current_path()<<std::endl;

    // try {
    //     std::filesystem::current_path("C:/Users/20131/Desktop/BickRenderer/");
    //     std::cout << "工作目录设置为：" << std::filesystem::current_path() << std::endl;
    // } catch (const std::exception &e) {
    //     std::cerr << "无法设置工作目录：" << e.what() << std::endl;
    // }
}

// 窗口大小变化回调函数
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

GLFWwindow *CreateWindow(int width, int height, const char *title, GLFWframebuffersizefun callback)
{
    // 初始化glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                 // 设置opengl主版本为3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                 // 设置opengl次版本为3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 告诉GLFW 我们使用的是核心模式
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // 创建窗口
    GLFWwindow *window = glfwCreateWindow(1920, 1080, "BickRenderer", NULL, NULL); // 创建窗口,800*600为窗口大小,LearnOpenGL为窗口标题
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate(); // 终止glfw
        return 0;
    }
    glfwMakeContextCurrent(window); // 通知GLFW将此窗口的上下文设置为当前线程的主上下文

    // 初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) // TODO: 这里暂时不是很清楚
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return 0;
    }

    // 设置Viewport
    Singleton<InputSystem>::Instance().Init(window);
    glViewport(0, 0, 1920, 1080);                                        // 左下角坐标为(0,0),右上角坐标为(800,600)
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // 设置窗口大小变化回调函数

    return window;
}
void HellowWorld()
{
    std::string startTitle =
        "|********************************************|\n"
        "|************BickRenderer start**************|\n"
        "|*********Welcome to BickRenderer************|\n"
        "|********************************************|";

    std::cout << "\n\n\n"
              << startTitle << std::endl
              << std::endl;
}
void SetOpenGL()
{
    glEnable(GL_DEPTH_TEST); // 启用深度测试
    glDepthFunc(GL_LESS);    // 设置深度测试函数为 LESS
    glDepthMask(GL_TRUE);    // 启用深度写入
    glDisable(GL_CULL_FACE); // 禁用背面剔除
    glEnable(GL_BLEND);      // 启用混合
}