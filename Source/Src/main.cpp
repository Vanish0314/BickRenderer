/*
 * @Author: Vanish
 * @Date: 2024-09-09 21:35:01
 * @LastEditTime: 2024-11-05 19:57:55
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
// GLFWwindow* CreateWindow(int width, int height, const char* title)
// {
//     return window;
// }

GLFWwindow* CreateWindow(int width, int height, const char* title,GLFWframebuffersizefun callback)
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
    Singleton<InputSystem>::Instance().Init(window);
    glViewport(0, 0, 800, 800);//左下角坐标为(0,0),右上角坐标为(800,600)
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//设置窗口大小变化回调函数

    return window;
}
void HellowWorld()
{
    std::string startTitle = 
        "|********************************************|\n"
        "|************BickRenderer start**************|\n"
        "|*********Welcome to BickRenderer************|\n"
        "|********************************************|";

    std::cout <<"\n\n\n"<< startTitle << std::endl<<std::endl;
}
void SetOpenGL()
{
    glEnable(GL_DEPTH_TEST); // 启用深度测试
    glDepthFunc(GL_LESS);    // 设置深度测试函数为 LESS
    glDepthMask(GL_TRUE);    // 启用深度写入
    glDisable(GL_CULL_FACE); // 禁用背面剔除
    glEnable(GL_BLEND); // 启用混合
}
int main()
{
    GLFWwindow *window = CreateWindow(800, 600, "BickRenderer",framebuffer_size_callback);
    HellowWorld();
    
    Camera camera = Camera(800,600,90.0);
    camera.SetPosition(glm::vec3(0.0f, 0.0f, 1.0f));
    camera.SetForward(glm::vec3(0.0f, 0.0f, -1.0f));

    auto directionalLight = std::make_shared<DirectionalLight>((glm::vec3(-1.0f, -1.0f, -1.0f)));
    Singleton<Scene>::Instance().directionalLights.push_back(directionalLight);

    MatFactory_StandardPBM_MetallicWorkFlow phongMat = MatFactory_StandardPBM_MetallicWorkFlow(
        "Source/GLSL_Shaders/Blinn-PhongShader/StdBlinnPhongVertex.glsl",
        "Source/GLSL_Shaders/Blinn-PhongShader/StdBlinnPhongFrag.glsl"
    );
    
    Model model = Model("Assets/Models/NanoSuit/nanosuit.obj",&phongMat,Transform(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(45.0f, 0.0f, 0.0f), glm::vec3(0.3f)));

//------------------------FB0----------------------------------------------//
    unsigned int fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    unsigned int texture;
    glGenTextures(1, &texture); // 生成纹理
    glBindTexture(GL_TEXTURE_2D, texture); // 绑定纹理
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL); // 定义纹理大小,格式,数据
    //图象从纹理图象空间映射到帧缓冲图象空间(映射需要重新构造纹理图像,这样就会造成应用到多边形上的图像失真),这时就可用glTexParmeteri()函数来确定如何把纹理象素映射成像素.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // 设置纹理缩小过滤方式,LINEAR表示线性插值
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // 设置纹理放大过滤方式,LINEAR表示线性插值
    glBindTexture(GL_TEXTURE_2D, 0); // 解绑纹理
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);// 将纹理attach到帧缓冲对象上

    unsigned int rbo;
    glGenRenderbuffers(1, &rbo); // 生成渲染缓冲
    glBindRenderbuffer(GL_RENDERBUFFER, rbo); // 绑定渲染缓冲
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);// 定义渲染缓冲大小,格式,数据
    glBindRenderbuffer(GL_RENDERBUFFER, 0); // 解绑渲染缓冲
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // 将渲染缓冲attach到帧缓冲对象上

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "Framebuffer not complete!" << std::endl;
        throw std::runtime_error("Framebuffer not complete!");
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };
    unsigned int quadVAO, quadVBO;
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    Shader screenShader = Shader(
        "Source/GLSL_Shaders/ScreenShader/vert.glsl",
        "Source/GLSL_Shaders/ScreenShader/frag.glsl",
        "ScreenShader"
    );
//------------------------FB0-END----------------------------------------------//
//------------------------CUBEMAP----------------------------------------------//


    GLuint cubeMap;
    glGenTextures(1, &cubeMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap);

    std::vector<std::string> textures_faces = {
        "Assets/Textures/Skybox/MountainSea/right.jpg",
        "Assets/Textures/Skybox/MountainSea/left.jpg",
        "Assets/Textures/Skybox/MountainSea/top.jpg",
        "Assets/Textures/Skybox/MountainSea/bottom.jpg",
        "Assets/Textures/Skybox/MountainSea/front.jpg",
        "Assets/Textures/Skybox/MountainSea/back.jpg"
    };
    int width, height, nrChannels;
    unsigned char *data;
    for (unsigned int i = 0; i < textures_faces.size(); i++)
    {
        data = stbi_load(textures_faces[i].c_str(), &width, &height, &nrChannels, 0);
        glTexImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
            0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    Shader skyboxShader = Shader(
        "Source/GLSL_Shaders/SkyBox/cubemapvert.glsl",
        "Source/GLSL_Shaders/SkyBox/cubemapfrag.glsl",
        "SkyboxShader"
    );

    float skyboxVertices[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };
    unsigned int skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

//------------------------CUBEMAP-END----------------------------------------------//

    SetOpenGL();
    int frameCount = 0;
    //渲染循环
    while(!glfwWindowShouldClose(window))//窗口应该关闭时结束循环
    {
        // 更新数据
        // Time::Update();

        //输入
        Singleton<InputSystem>::Instance().Update();

        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        //渲染
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//设置清空屏幕使用的颜色,是一个状态设置函数
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清空颜色缓冲,是一个状态使用函数,获取状态后执行
//-----------天空盒----------//
        skyboxShader.Use();
        unsigned short skyboxLoc = glGetUniformLocation(skyboxShader.shaderProgramID, "skybox");
        glUniform1i(skyboxLoc, GL_TEXTURE0);
        glm::mat4 viewMatrix       = Camera::main->GetViewMatrix();
        glm::mat4 projectionMatrix = Camera::main->GetProjectionMatrix();
        unsigned short viewLoc       = glGetUniformLocation(skyboxShader.shaderProgramID, "view");
        unsigned short projectionLoc = glGetUniformLocation(skyboxShader.shaderProgramID, "projection");
        glUniformMatrix4fv(viewLoc      , 1, GL_FALSE, glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));    
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap);
        glBindVertexArray(skyboxVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
//-----------天空盒-END----------//
//-----------模型----------//
        model.Draw();
//-----------模型-END----------//
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

        //交换缓冲,检查并调用事件回调函数
        glfwSwapBuffers(window); //交换颜色缓冲
        glfwPollEvents(); //检查是否触发事件(输入),更新窗口状态,调用对应回调函数

        // 报错
        // GLenum err;
        // while ((err = glGetError()) != GL_NO_ERROR)
        // {
        //     std::cerr << "OpenGL error: " << err << std::endl;
        // }
        // std::cout << "frameCount: " << ++frameCount << std::endl;
    }

    glfwTerminate(); //终止glfw
}
