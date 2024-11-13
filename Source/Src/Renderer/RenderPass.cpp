/*
 * @Author: Vanish
 * @Date: 2024-11-13 19:34:42
 * @LastEditTime: 2024-11-13 21:09:24
 * Also View: http://vanishing.cc
 * Contract Me: http://qunchengxiao.me
 * Copyright@ http://www.wtfpl.net/
 */

#include "Renderer/RenderPass.hpp"

void RenderPass::Initialize(RenderPassInitInfo&& info)
{
    m_renderResource = info.renderResource.lock();
    if(!m_renderResource)
    {
        throw std::runtime_error("RenderResource不存在");
        return;
    }
    
    m_width = info.width;
    m_height = info.height;
    m_outputInternalFormat = info.outputInternalFormat;

    //创建FBO
    CreateFrameBuffer();
}

void RenderPass::CreateFrameBuffer()
{
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
    if(m_fbo)
    {
        glDeleteFramebuffers(1, &m_fbo);
        m_fbo = 0;
    }
    if(m_outputTexture)
    {
        glDeleteTextures(1, &m_outputTexture);
        m_outputTexture = 0;
    }
    m_width = 0;
    m_height = 0;
    m_outputInternalFormat = 0;
}
