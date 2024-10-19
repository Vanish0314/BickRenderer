/*
 * @Author: Vanish
 * @Date: 2024-09-09 21:35:01
 * @LastEditTime: 2024-10-19 19:30:46
 * Also View: http://vanishing.cc
 * Copyright@ https://creativecommons.org/licenses/by/4.0/deed.zh-hans
 */
#include <iostream>
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

//窗口大小变化回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

//输入处理函数
void ProcessInput(GLFWwindow* window,Camera &camera)
{
    //按下ESC键退出程序
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.Move(camera.forward * 0.02f);
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.Move(camera.forward * -0.02f);
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.Move(camera.right * -0.02f);
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.Move(camera.right * 0.02f);
}
void ProcessMouseInput(GLFWwindow* window,double xpos,double ypos)
{
    Singleton<InputSystem>::Instance().mouse.UpdatePosition(xpos,ypos);
}

// GLFWwindow* CreateWindow(int width, int height, const char* title)
// {
//     return window;
// }

int main()
{
    //初始化glfw
    glfwInit(); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 设置opengl主版本为3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 设置opengl次版本为3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //告诉GLFW 我们使用的是核心模式
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //创建窗口
    GLFWwindow* window = glfwCreateWindow(800, 600, "BickRenderer", NULL, NULL);//创建窗口,800*600为窗口大小,LearnOpenGL为窗口标题
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();//终止glfw
        return 0;
    }
    glfwMakeContextCurrent(window);//通知GLFW将此窗口的上下文设置为当前线程的主上下文
    
    //初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))//TODO: 这里暂时不是很清楚
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return 0;
    }

    //设置Viewport
    glViewport(0, 0, 800, 800);//左下角坐标为(0,0),右上角坐标为(800,600)
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//设置窗口大小变化回调函数
    glfwSetCursorPosCallback(window,ProcessMouseInput);

    std::cout << "BickRenderer启动,你好!!!" << std::endl<<std::endl;
    
    Camera camera = Camera(800,600,90.0);
    camera.SetPosition(glm::vec3(0.0f, 0.0f, 1.0f));
    camera.SetForward(glm::vec3(0.0f, 0.0f, -1.0f));

    auto directionalLight = std::make_shared<DirectionalLight>((glm::vec3(1.0f, 1.0f, 1.0f)));
    Singleton<Scene>::Instance().directionalLights.push_back(directionalLight);

    MatFactory_StandardPBM_MetallicWorkFlow furMat = MatFactory_StandardPBM_MetallicWorkFlow(
        "Source/GLSL_Shaders/Fur/FuryVertex.glsl",
        "Source/GLSL_Shaders/Fur/FuryGeometry.glsl",
        "Source/GLSL_Shaders/Fur/FuryFrag.glsl"
    );
    MatFactory_StandardPBM_MetallicWorkFlow jadeMat = MatFactory_StandardPBM_MetallicWorkFlow(
        "Source/GLSL_Shaders/Jade/JadeVertex.glsl",
        "Source/GLSL_Shaders/Jade/JadeFrag.glsl"
    );
    MatFactory_StandardPBM_MetallicWorkFlow phongMat = MatFactory_StandardPBM_MetallicWorkFlow(
        "Source/GLSL_Shaders/Blinn-PhongShader/StdBlinnPhongVertex.glsl",
        "Source/GLSL_Shaders/Blinn-PhongShader/StdBlinnPhongFrag.glsl"
    );
    
    Model model = Model("Assets/Models/NanoSuit/nanosuit.obj",&phongMat,Transform(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(45.0f, 0.0f, 0.0f), glm::vec3(0.3f)));


    glEnable(GL_DEPTH_TEST); // 启用深度测试
    glDepthFunc(GL_LESS);    // 设置深度测试函数为 LESS
    glDepthMask(GL_TRUE);    // 启用深度写入
    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    //渲染循环
    while(!glfwWindowShouldClose(window))//窗口应该关闭时结束循环
    {
        //输入
        ProcessInput(window,camera);//处理输入
        camera.Rotate(Singleton<InputSystem>::Instance().mouse.mouseBias.x,Singleton<InputSystem>::Instance().mouse.mouseBias.y);

        //渲染
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//设置清空屏幕使用的颜色,是一个状态设置函数
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清空颜色缓冲,是一个状态使用函数,获取状态后执行

        model.Draw();

        //交换缓冲,检查并调用事件回调函数
        glfwSwapBuffers(window); //交换颜色缓冲
        glfwPollEvents(); //检查是否触发事件(输入),更新窗口状态,调用对应回调函数

        // 报错
        // GLenum err;
        // while ((err = glGetError()) != GL_NO_ERROR)
        // {
        //     std::cerr << "OpenGL error: " << err << std::endl;
        // }
    }

    glfwTerminate(); //终止glfw
}
