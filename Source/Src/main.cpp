/*
 * @Author: Vanish
 * @Date: 2024-09-09 21:35:01
 * @LastEditTime: 2024-11-15 15:36:19
 * Also View: http://vanishing.cc
 * Copyright@ https://creativecommons.org/licenses/by/4.0/deed.zh-hans
 */

#include "Bick.hpp"

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

    //------------------------FB0----------------------------------------------//
    unsigned int fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    unsigned int texture;
    glGenTextures(1, &texture);                                                          // 生成纹理
    glBindTexture(GL_TEXTURE_2D, texture);                                               // 绑定纹理
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1920, 1080, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL); // 定义纹理大小,格式,数据
    // 图象从纹理图象空间映射到帧缓冲图象空间(映射需要重新构造纹理图像,这样就会造成应用到多边形上的图像失真),这时就可用glTexParmeteri()函数来确定如何把纹理象素映射成像素.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // 设置纹理缩小过滤方式,LINEAR表示线性插值
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // 设置纹理放大过滤方式,LINEAR表示线性插值
    glBindTexture(GL_TEXTURE_2D, 0);                                  // 解绑纹理

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0); // 将纹理attach到帧缓冲对象上

    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);                                                                  // 生成渲染缓冲
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);                                                     // 绑定渲染缓冲
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1920, 1080);                        // 定义渲染缓冲大小,格式,数据
    glBindRenderbuffer(GL_RENDERBUFFER, 0);                                                       // 解绑渲染缓冲
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // 将渲染缓冲attach到帧缓冲对象上

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "Framebuffer not complete!" << std::endl;
        throw std::runtime_error("Framebuffer not complete!");
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    float quadVertices[] = {// vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
                            // positions   // texCoords
                            -1.0f, 1.0f, 0.0f, 1.0f,
                            -1.0f, -1.0f, 0.0f, 0.0f,
                            1.0f, -1.0f, 1.0f, 0.0f,

                            -1.0f, 1.0f, 0.0f, 1.0f,
                            1.0f, -1.0f, 1.0f, 0.0f,
                            1.0f, 1.0f, 1.0f, 1.0f};
    unsigned int quadVAO, quadVBO;
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));

    Shader screenShader = Shader(
        "Source/GLSL_Shaders/ScreenShader/vert.glsl",
        "Source/GLSL_Shaders/ScreenShader/frag.glsl",
        "ScreenShader");
    //------------------------FB0-END----------------------------------------------//
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
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        // 渲染
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);               // 设置清空屏幕使用的颜色
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // 清空颜色缓冲

        skyboxPass->Draw(fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        model.Draw();
        //-----------后处理--------------------------//
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        screenShader.Use();
        unsigned short textureLoc = glGetUniformLocation(screenShader.shaderProgramID, "screenTexture");
        glUniform1i(textureLoc, GL_TEXTURE0);
        glBindVertexArray(quadVAO);
        glDisable(GL_DEPTH_TEST);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        //-----------后处理-END----------//

        // 交换缓冲,检查并调用事件回调函数
        glfwSwapBuffers(window); // 交换颜色缓冲
        glfwPollEvents();        // 检查是否触发事件(输入),更新窗口状态,调用对应回调函数
#pragma endregion
        
        // 报错
        // GLenum err;
        // while ((err = glGetError()) != GL_NO_ERROR)
        // {
        //     std::cerr << "OpenGL error: " << err << std::endl;
        // }
        // std::cout << "frameCount: " << ++frameCount << std::endl;
    }

    glfwTerminate(); // 终止glfw
}
