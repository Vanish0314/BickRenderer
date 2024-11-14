/*
 * @Author: Vanish
 * @Date: 2024-11-13 19:34:42
 * @LastEditTime: 2024-11-14 18:00:05
 * Also View: http://vanishing.cc
 * Contract Me: http://qunchengxiao.me
 * Copyright@ http://www.wtfpl.net/
 */

#include "Renderer/RenderPass.hpp"

void RenderPass::Initialize(std::shared_ptr<RenderPassInitInfo> info)
{
    m_renderResource = info->renderResource.lock();
    if (!m_renderResource)
    {
        throw std::runtime_error("RenderResource不存在");
        return;
    }

    m_width = info->width;
    m_height = info->height;
    m_outputInternalFormat = info->outputInternalFormat;

    // 创建FBO
    CreateFrameBuffer();
}

void RenderPass::ChangeFBO(GLuint fbo)
{
    // 删除原有FBO会同时删除FBO上的attachment
    glDeleteFramebuffers(1, &m_fbo);
    m_fbo = fbo;

    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "FBO 不完整, 将自动补全" << std::endl;

        m_outputTexture = 0;
        // 创建一个纹理作为输出附件
        glGenTextures(1, &m_outputTexture);
        glBindTexture(GL_TEXTURE_2D, m_outputTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, m_outputInternalFormat, m_width, m_height, 0, m_outputInternalFormat, GL_FLOAT, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        // 绑定新纹理作为颜色附件
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_outputTexture, 0);

        // 检查帧缓冲完整性
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            std::cerr << "FBO 自动补全失败，FBO 不完整!" << std::endl;
            return; // 返回并不再继续执行
        }
    }
    else
    {
        // 如果 FBO 完整，获取新 FBO 的附件 ID
        std::cout << "FBO 完整，更新附件..." << std::endl;

        // 获取新 FBO 上的颜色附件对象
        GLuint attachedTexture = 0;
        glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, (GLint*)&attachedTexture);

        m_outputTexture = attachedTexture;
        GLint textureWidth = 0, textureHeight = 0;
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &textureWidth);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &textureHeight);
        m_width = textureWidth;
        m_height = textureHeight;

        // TODO: 如果pass中有模板和深度,需要更改

    }

    // 清除 FBO 绑定
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void RenderPass::CreateFrameBuffer()
{
    //TODO:这里只绑定了一个color buffer,需要绑定模板和深度buffer

    // 创建纹理
    glGenTextures(1, &m_outputTexture);
    glBindTexture(GL_TEXTURE_2D, m_outputTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, m_outputInternalFormat, m_width, m_height, 0, m_outputInternalFormat, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    // 创建FBO
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_outputTexture, 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cerr << "FBO不完整" << std::endl;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

inline GLuint RenderPass::GetOutputTexture() const
{
    return m_outputTexture;
}
inline GLuint RenderPass::GetFBO() const
{
    return m_fbo;
}
inline void RenderPass::CleanUp()
{
    if (m_fbo)
    {
        glDeleteFramebuffers(1, &m_fbo);
        m_fbo = 0;
    }
    if (m_outputTexture)
    {
        glDeleteTextures(1, &m_outputTexture);
        m_outputTexture = 0;
    }
    m_width = 0;
    m_height = 0;
    m_outputInternalFormat = 0;
}
