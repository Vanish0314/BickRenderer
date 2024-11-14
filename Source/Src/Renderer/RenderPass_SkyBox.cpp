/*
 * @Author: Vanish
 * @Date: 2024-11-13 20:11:54
 * @LastEditTime: 2024-11-14 18:18:22
 * Also View: http://vanishing.cc
 * Contract Me: http://qunchengxiao.me
 * Copyright@ http://www.wtfpl.net/
 */

#include <iostream>
#include "Renderer/RenderPass.hpp"
#include "stb_image.h"

// TODO: too much junk code,need to be simplified
void RenderPass_SkyBox::Initialize(std::shared_ptr<RenderPassInitInfo> info)
{
    //调用父类Initialize函数
    RenderPass::Initialize(info);

    auto res = m_renderResource;
    if (res)
    {
        auto skyBoxPath = res->m_SkyBoxRenderResource.skyBoxTexturePath;
        auto vert = res->m_SkyBoxRenderResource.skyBoxVertShaderPath;
        auto frag = res->m_SkyBoxRenderResource.skyBoxFragShaderPath;

        // 创建shader
        m_SkyBoxShader.InitShader(vert, frag, "SkyBoxShader");

        // 创建立方体贴图
        glGenTextures(1, &m_SkyBoxCubeMap);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_SkyBoxCubeMap);

        int width, height, nrChannels;
        unsigned char *data;
        for (unsigned int i = 0; i < 6; i++)
        {
            data = stbi_load(skyBoxPath[i].c_str(), &width, &height, &nrChannels, 0);
            glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        stbi_image_free(data);

        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

        // 创建VAO
        glGenVertexArrays(1, &m_SkyBoxVAO);
        glGenBuffers(1, &m_SkyBoxVBO);
        glBindVertexArray(m_SkyBoxVAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_SkyBoxVBO);
        glBufferData(GL_ARRAY_BUFFER, 36*3*4, &m_skyboxVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glBindVertexArray(0);
    }
    else
    {
        throw std::runtime_error("Render Resource被释放");
    }
}

void RenderPass_SkyBox::Draw()
{
    //TODO: 处理OpenGl设置
    //关闭深度写入
    glDepthMask(GL_FALSE);

    // 绑定framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    //绑定VAO
    glBindVertexArray(m_SkyBoxVAO);

    // 绑定shader
    m_SkyBoxShader.Use();
    unsigned short skyboxLoc = glGetUniformLocation(m_SkyBoxShader.shaderProgramID, "skybox");
    glUniform1i(skyboxLoc, GL_TEXTURE0);
    glm::mat4 viewMatrix = Camera::main->GetViewMatrix();
    glm::mat4 projectionMatrix = Camera::main->GetProjectionMatrix();
    unsigned short viewLoc = glGetUniformLocation(m_SkyBoxShader.shaderProgramID, "view");
    unsigned short projectionLoc = glGetUniformLocation(m_SkyBoxShader.shaderProgramID, "projection");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_SkyBoxCubeMap);

    // 绘制立方体
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    // 解绑
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);

    glDepthMask(GL_TRUE);
}
void RenderPass_SkyBox::Draw(GLuint FBO)
{
    //TODO: 处理OpenGl设置
    glDepthMask(GL_FALSE);

    // 绑定framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    //绑定VAO
    glBindVertexArray(m_SkyBoxVAO);

    // 绑定shader
    m_SkyBoxShader.Use();
    unsigned short skyboxLoc = glGetUniformLocation(m_SkyBoxShader.shaderProgramID, "skybox");
    glUniform1i(skyboxLoc, GL_TEXTURE0);
    glm::mat4 viewMatrix = Camera::main->GetViewMatrix();
    glm::mat4 projectionMatrix = Camera::main->GetProjectionMatrix();
    unsigned short viewLoc = glGetUniformLocation(m_SkyBoxShader.shaderProgramID, "view");
    unsigned short projectionLoc = glGetUniformLocation(m_SkyBoxShader.shaderProgramID, "projection");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_SkyBoxCubeMap);

    // 绘制立方体
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    // 解绑
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    
    //开启深度写入
    glDepthMask(GL_TRUE);
}

const float RenderPass_SkyBox::m_skyboxVertices[] = 
{
    // positions
    -1.0f, 1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,

    -1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,

    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,

    -1.0f, 1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, 1.0f
};