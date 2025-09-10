/*
 * @Author: Vanish
 * @Date: 2024-09-09 21:35:01
 * @LastEditTime: 2025-09-10 20:23:28
 * Also View: http://vanishing.cc
 * Copyright@ https://creativecommons.org/licenses/by/4.0/deed.zh-hans
 */

#include "glad/glad.h" //glad 必须在Glfw前加载
#include <GLFW/glfw3.h>
#include <iostream>


#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif

#include "Camera/Camera.hpp"
#include "Input/InputSystem.hpp"
#include "Mesh/Model.hpp"
#include "Common/AssetPath.hpp"

#include "Renderer/RenderPass.hpp"

// 窗口大小变化回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

GLFWwindow* CreateWindow(int width, int height, const char* title, GLFWframebuffersizefun callback)
{
    // 初始化glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 设置opengl主版本为3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 设置opengl次版本为3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 告诉GLFW 我们使用的是核心模式
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // 创建窗口
    GLFWwindow* window = glfwCreateWindow(1920, 1080, "BickRenderer", NULL, NULL); // 创建窗口,800*600为窗口大小,LearnOpenGL为窗口标题
    if (window == NULL) {
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
    glViewport(0, 0, 1920, 1080); // 左下角坐标为(0,0),右上角坐标为(800,600)
    glfwSetFramebufferSizeCallback(window, callback); // 设置窗口大小变化回调函数

    return window;
}
void HellowWorld()
{
    std::string startTitle = "|********************************************|\n"
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
    glDepthFunc(GL_LESS); // 设置深度测试函数为 LESS
    glDepthMask(GL_TRUE); // 启用深度写入
    glDisable(GL_CULL_FACE); // 禁用背面剔除
    glEnable(GL_BLEND); // 启用混合
}

int main()
{
    GLFWwindow* window = CreateWindow(1920, 1080, "BickRenderer", framebuffer_size_callback);
    HellowWorld();
    
    // 初始化资源路径系统
    AssetPath::Initialize();

#pragma region SceneSetUp
    // 创建主摄像机 - 使用原来的方式但手动设置为main
    Camera camera = Camera(1920, 1080, 90, false); // 不自动设置为main，避免shared_ptr问题
    camera.SetPosition(glm::vec3(0.0f, 0.0f, 1.0f));
    camera.SetForward(glm::vec3(0.0f, 0.0f, -1.0f));
    
    // 手动设置Camera::main
    Camera::main = std::make_shared<Camera>(camera);

    auto directionalLight = std::make_shared<DirectionalLight>((glm::vec3(-1.0f, -1.0f, -1.0f)));
    Singleton<Scene>::Instance().directionalLights.push_back(directionalLight);

    auto phongMat = MatFactory_StandardPBM_MetallicWorkFlow(
        AssetPath::GetShaderPath("Blinn-PhongShader/StdBlinnPhongVertex.glsl"),
        AssetPath::GetShaderPath("Blinn-PhongShader/StdBlinnPhongFrag.glsl"));

    Model model = Model(AssetPath::GetAssetPath("Models/NanoSuit/nanosuit.obj"), &phongMat, Transform(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.3f)));

#pragma endregion

#pragma region PassSetUp

    auto skyboxPass = std::make_shared<RenderPass_SkyBox>();
    auto renderResoruce = std::make_shared<RenderResource>();
    renderResoruce->m_SkyBoxRenderResource.skyBoxTexturePath = {
        AssetPath::GetAssetPath("Textures/Skybox/MountainSea/right.jpg"),
        AssetPath::GetAssetPath("Textures/Skybox/MountainSea/left.jpg"),
        AssetPath::GetAssetPath("Textures/Skybox/MountainSea/top.jpg"), 
        AssetPath::GetAssetPath("Textures/Skybox/MountainSea/bottom.jpg"),
        AssetPath::GetAssetPath("Textures/Skybox/MountainSea/front.jpg"),
        AssetPath::GetAssetPath("Textures/Skybox/MountainSea/back.jpg")
    };
    auto renderPassInfo = std::make_shared<RenderPassInitInfo>();
    renderPassInfo->width = 1920;
    renderPassInfo->height = 1080;
    renderPassInfo->renderResource = renderResoruce;
    skyboxPass->Initialize(renderPassInfo);
    auto postProcessPass = std::make_shared<RenderPass_PostProcess>();
    renderResoruce->m_PostProcessRenderResource.postProcessVertShaderPath = AssetPath::GetShaderPath("ScreenShader/vert.glsl");
    renderResoruce->m_PostProcessRenderResource.postProcessFragShaderPath = AssetPath::GetShaderPath("ScreenShader/frag.glsl");
    postProcessPass->Initialize(renderPassInfo);

#pragma endregion

    SetOpenGL();
    int frameCount = 0;
    while (!glfwWindowShouldClose(window)) // 窗口应该关闭时结束循环
    {
        // 更新数据
        // Time::Update();

        // 输入
        Singleton<InputSystem>::Instance().Update();

#pragma region 渲染
        // 清除屏幕
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, 1920, 1080);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 第一阶段：渲染天空盒到屏幕
        glDepthMask(GL_FALSE); // 禁用深度写入
        skyboxPass->Draw(0, 0); // 直接渲染到默认帧缓冲
        glDepthMask(GL_TRUE);  // 重新启用深度写入
        
        // 第二阶段：渲染模型到屏幕（天空盒作为背景）
        model.Draw();

        // 交换缓冲,检查并调用事件回调函数
        glfwSwapBuffers(window); // 交换颜色缓冲
        glfwPollEvents(); // 检查是否触发事件(输入),更新窗口状态,调用对应回调函数
#pragma endregion

        std::cout << "\rFrameCount: " << frameCount++;
        std::cout.flush();
    }
    glfwTerminate(); // 终止glfw
}
