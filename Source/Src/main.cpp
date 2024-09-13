/*
 * @Author: Vanish
 * @Date: 2024-09-09 21:35:01
 * @LastEditTime: 2024-09-13 21:58:33
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


//窗口大小变化回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

//输入处理函数
void ProcessInput(GLFWwindow* window)
{
    //按下ESC键退出程序
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    //初始化glfw
    glfwInit(); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 设置opengl主版本为3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 设置opengl次版本为3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //告诉GLFW 我们使用的是核心模式
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //创建窗口
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL-BickRenderer", NULL, NULL);//创建窗口,800*600为窗口大小,LearnOpenGL为窗口标题
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();//终止glfw
        return -1;
    }
    glfwMakeContextCurrent(window);//通知GLFW将此窗口的上下文设置为当前线程的主上下文
    
    //初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))//TODO: 这里暂时不是很清楚
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //设置Viewport
    glViewport(0, 0, 800, 600);//左下角坐标为(0,0),右上角坐标为(800,600)
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//设置窗口大小变化回调函数
    
    //Shader
    Shader ourShader("Source\\GLSL_Shaders\\ShaderClass\\VertexShader.glsl",
                     "Source\\GLSL_Shaders\\ShaderClass\\FragmentShader.glsl");

    //输入顶点数据
    float vertices[] = {
    // ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
    };//顶点坐标
    unsigned int indices[] = {
    // 注意索引从0开始! 
    // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
    // 这样可以由下标代表顶点组合成矩形
    0, 1, 3, // 第一个三角形
    1, 2, 3  // 第二个三角形
    };//索引
    unsigned int VBO,VAO,EBO;//声明一个VBO,VAO,EBO
    glGenVertexArrays(1, &VAO);//生成一个VAO,并将其ID存储在VAO中,此时VAO拥有了其唯一的id
    glGenBuffers(1, &VBO);//生成一个VBO,并将其ID存储在VBO中,此时VBO拥有了其唯一的id
    glGenBuffers(1, &EBO);//生成一个EBO,并将其ID存储在EBO中,此时EBO拥有了其唯一的id

    glBindVertexArray(VAO);//绑定VAO到当前活动的缓冲区,此时VAO将成为活动缓冲区

    glBindBuffer(GL_ARRAY_BUFFER, VBO);//绑定VBO到GL_ARRAY_BUFFER目标,GL_ARRAY_BUFFER是VBO(顶点缓冲对象)的缓冲类型
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//将顶点数据复制到缓冲中,并指定数据用以静态访问

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//绑定EBO到GL_ELEMENT_ARRAY_BUFFER目标,GL_ELEMENT_ARRAY_BUFFER是EBO(索引缓冲对象)的缓冲类型
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);//将索引数据复制到缓冲中,并指定数据用以静态访问

    //位置属性
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);//设置顶点属性指针,第一个参数为属性索引,第二个参数为属性个数,第三个参数为属性类型,第四个参数为是否归一化,第五个参数为偏移量,第六个参数为数据指针
    glEnableVertexAttribArray(0);//启用顶点属性数组
    //颜色属性
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));//设置顶点属性指针,第一个参数为属性索引,第二个参数为属性个数,第三个参数为属性类型,第四个参数为是否归一化,第五个参数为偏移量,第六个参数为数据指针
    glEnableVertexAttribArray(1);//启用顶点属性数组
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6*sizeof(float)));//设置顶点属性指针,第一个参数为属性索引,第二个参数为属性个数,第三个参数为属性类型,第四个参数为是否归一化,第五个参数为偏移量,第六个参数为数据指针
    glEnableVertexAttribArray(2);//启用顶点属性数组

    Texture wall = Texture("Assets\\Textures\\wall.jpg",GL_TEXTURE0);
    Texture smile = Texture("Assets\\Textures\\awesomeface.png",GL_TEXTURE1);

    glm::mat4 trans(1.0f);
    //渲染循环
    while(!glfwWindowShouldClose(window))//窗口应该关闭时结束循环
    {
        //输入
        ProcessInput(window);//处理输入

        //渲染
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//设置清空屏幕使用的颜色,是一个状态设置函数
        glClear(GL_COLOR_BUFFER_BIT);//清空颜色缓冲,是一个状态使用函数,获取状态后执行

        //绘制
        float timeValue = (float)glfwGetTime(); //获取当前时间
        float greenValue = (std::sin(timeValue) / 2.0f) + 0.5f; //计算绿色值
        ourShader.Use(); //使用着色器程序
        int vertexColorLocation = glGetUniformLocation(ourShader.shaderProgramID, "ourColor"); //获取ourColor变量的位置
        glUniform4f(vertexColorLocation, 0.8f, greenValue, 0.8f, 1.0f);//设置ourColor变量的值,即设置顶点颜色
        int transformLocation = glGetUniformLocation(ourShader.shaderProgramID, "transform"); //获取transform变量的位置
        trans = glm::rotate(trans,(float)glfwGetTime()/100,glm::vec3(0.0f,0.0f,1.0f));
        glUniformMatrix4fv(transformLocation,1,GL_FALSE,glm::value_ptr(trans)); //设置transform变量的值,即设置模型矩阵
        wall.Activate(ourShader.shaderProgramID, "Texture0"); //激活纹理0
        smile.Activate(ourShader.shaderProgramID, "Texture1"); //激活纹理1
        glBindVertexArray(VAO);//绑定VAO到当前活动的缓冲区
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);//绘制三角形,第一个参数为绘制模式,第二个参数为起始索引,第三个参数为绘制数量

        //交换缓冲,检查并调用事件回调函数
        glfwSwapBuffers(window); //交换颜色缓冲
        glfwPollEvents(); //检查是否触发事件(输入),更新窗口状态,调用对应回调函数 
    }

    glfwTerminate(); //终止glfw
}
