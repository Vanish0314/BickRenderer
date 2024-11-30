/*
 * @Author: Vanish
 * @Date: 2024-09-09 21:35:01
 * @LastEditTime: 2024-11-30 23:33:46
 * Also View: http://vanishing.cc
 * Copyright@ https://creativecommons.org/licenses/by/4.0/deed.zh-hans
 */
 
#include <iostream>
#include "glad/glad.h" //glad 必须在Glfw前加载
#include "Glfw/glfw3.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif

#include "Camera/Camera.hpp"
#include "Mesh/Model.hpp"
#include "Input/InputSystem.hpp"

#include "Renderer/RenderPass.hpp"

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
    glfwSetFramebufferSizeCallback(window, callback); // 设置窗口大小变化回调函数

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

int main()
{
    GLFWwindow *window = CreateWindow(1920, 1080, "BickRenderer", framebuffer_size_callback);
    HellowWorld();

    Camera camera = Camera(1920, 1080, 90.0);
    camera.SetPosition(glm::vec3(0.0f, 0.0f, 1.0f));
    camera.SetForward(glm::vec3(0.0f, 0.0f, -1.0f));

    auto directionalLight = std::make_shared<DirectionalLight>((glm::vec3(-1.0f, -1.0f, -1.0f)));
    Singleton<Scene>::Instance().directionalLights.push_back(directionalLight);

    auto phongMat = MatFactory_StandardPBM_MetallicWorkFlow(
        "Source/GLSL_Shaders/Blinn-PhongShader/StdBlinnPhongVertex.glsl",
        "Source/GLSL_Shaders/Blinn-PhongShader/StdBlinnPhongFrag.glsl"
        );

    Model model = Model("Assets/Models/NanoSuit/nanosuit.obj", &phongMat, Transform(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.3f)));

//-------------------------------SKYBOX-PASS----------//
    auto skyboxPass = std::make_shared<RenderPass_SkyBox>();
    auto renderResoruce = std::make_shared<RenderResource>();
    renderResoruce->m_SkyBoxRenderResource.skyBoxTexturePath = {
        "Assets/Textures/Skybox/MountainSea/right.jpg",
        "Assets/Textures/Skybox/MountainSea/left.jpg",
        "Assets/Textures/Skybox/MountainSea/top.jpg",
        "Assets/Textures/Skybox/MountainSea/bottom.jpg",
        "Assets/Textures/Skybox/MountainSea/front.jpg",
        "Assets/Textures/Skybox/MountainSea/back.jpg"
        };
    auto renderPassInfo = std::make_shared<RenderPassInitInfo>();
    renderPassInfo->width = 1920;
    renderPassInfo->height = 1080;
    renderPassInfo->renderResource = renderResoruce;
    skyboxPass->Initialize(renderPassInfo);
//----------SKYBOX-PASS-END----------//
    auto postProcessPass = std::make_shared<RenderPass_PostProcess>();
    renderResoruce->m_PostProcessRenderResource.postProcessVertShaderPath = "Source/GLSL_Shaders/ScreenShader/vert.glsl";
    renderResoruce->m_PostProcessRenderResource.postProcessFragShaderPath = "Source/GLSL_Shaders/ScreenShader/frag.glsl";
    postProcessPass->Initialize(renderPassInfo);
//--------------------------------
    SetOpenGL();
    int frameCount = 0;
    // 渲染循环
    while (!glfwWindowShouldClose(window)) // 窗口应该关闭时结束循环
    {
        // 更新数据
        // Time::Update();

        // 输入
        Singleton<InputSystem>::Instance().Update();

#pragma region 渲染
        skyboxPass->Draw();
        glBindFramebuffer(GL_FRAMEBUFFER, skyboxPass->GetFBO());
        model.Draw();
        postProcessPass->Draw(skyboxPass->GetFBO(),0);

        // 交换缓冲,检查并调用事件回调函数
        glfwSwapBuffers(window); // 交换颜色缓冲
        glfwPollEvents();        // 检查是否触发事件(输入),更新窗口状态,调用对应回调函数
#pragma endregion
        
        //TODO:数据显示
    }

    glfwTerminate(); // 终止glfw
}
