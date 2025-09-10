/*
 * @Author: Vanish
 * @Date: 2024-11-13 20:11:54
 * @LastEditTime: 2024-11-30 23:37:23
 * Also View: http://vanishing.cc
 * Contract Me: http://qunchengxiao.me
 * Copyright@ http://www.wtfpl.net/
 */

#include "Renderer/RenderPass.hpp"
#include "Common/AssetPath.hpp"
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
        auto vert       = res->m_SkyBoxRenderResource.skyBoxVertShaderPath;
        auto frag       = res->m_SkyBoxRenderResource.skyBoxFragShaderPath;

        // 创建shader
        m_SkyBoxShader.InitShader(AssetPath::GetShaderPath(vert), AssetPath::GetShaderPath(frag), "SkyBoxShader");

        // 创建立方体贴图
        glGenTextures(1, &m_SkyBoxCubeMap);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_SkyBoxCubeMap);

        int width, height, nrChannels;
        unsigned char *data;
        for (unsigned int i = 0; i < 6; i++)
        {
            std::cout << "[SkyBox] 加载纹理: " << skyBoxPath[i] << std::endl;
            data = stbi_load(skyBoxPath[i].c_str(), &width, &height, &nrChannels, 0);
            if (data)
            {
                glTexImage2D(
                    GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                    0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                stbi_image_free(data);
                std::cout << "[SkyBox] 纹理 " << i << " 加载成功: " << width << "x" << height << std::endl;
            }
            else
            {
                std::cerr << "[SkyBox] 纹理 " << i << " 加载失败: " << skyBoxPath[i] << std::endl;
            }
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

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

void RenderPass_SkyBox::DrawPass(GLuint inputFBO, GLuint outputFBO)
{
    //TODO: 处理OpenGl设置
    glDepthMask(GL_FALSE);

    // 绑定framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, outputFBO);

    //绑定VAO
    glBindVertexArray(m_SkyBoxVAO);

    // 绑定shader
    m_SkyBoxShader.Use();
    unsigned short skyboxLoc = glGetUniformLocation(m_SkyBoxShader.shaderProgramID, "skybox");
    glUniform1i(skyboxLoc, 0); // 纹理单元0
    glm::mat4 viewMatrix = Camera::main->GetViewMatrix();
    //去除view矩阵中的位移
    viewMatrix[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    glm::mat4 projectionMatrix = Camera::main->GetProjectionMatrix();
    unsigned short viewLoc = glGetUniformLocation(m_SkyBoxShader.shaderProgramID, "view");
    unsigned short projectionLoc = glGetUniformLocation(m_SkyBoxShader.shaderProgramID, "projection");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_SkyBoxCubeMap);

    // 绘制立方体
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    // 解绑VAO和shader（但不解绑FBO，让基类处理）
    glBindVertexArray(0);
    glUseProgram(0);
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