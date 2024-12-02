/*
 * @Author: Vanish
 * @Date: 2024-11-13 19:34:42
 * @LastEditTime: 2024-12-02 17:01:16
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

void RenderPass::Draw(GLuint InputFBO, std::optional<GLuint> OutputFBO)
{
    if(OutputFBO.has_value())
    {
        DrawPass(InputFBO, OutputFBO.value());
    }
    else
    {
        ClearBuffer();
        DrawPass(InputFBO, m_fbo);
    }
    UnBind();
}
void RenderPass::ClearBuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}
void RenderPass::UnBind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);   // 恢复到默认帧缓冲
    glBindVertexArray(0);                   // 解绑 VAO
    glUseProgram(0);                        // 解绑当前着色器
    glBindTexture(GL_TEXTURE_2D, 0);        // 解绑当前纹理
    glBindBuffer(GL_ARRAY_BUFFER, 0);       // 解绑 VBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // 解绑索引缓冲
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
    // 创建颜色纹理
    glGenTextures(1, &m_outputTexture);
    glBindTexture(GL_TEXTURE_2D, m_outputTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, m_outputInternalFormat, m_width, m_height, 0, m_outputInternalFormat, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    // 创建FBO
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    // 绑定颜色纹理到FBO
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_outputTexture, 0);

    // 创建深度和模板缓冲对象
    GLuint depthStencilRBO;
    glGenRenderbuffers(1, &depthStencilRBO);
    glBindRenderbuffer(GL_RENDERBUFFER, depthStencilRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height); // 24位深度 + 8位模板
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    // 将深度和模板缓冲绑定到FBO
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthStencilRBO);

    // 检查FBO是否完整
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cerr << "[RenderPass::CreateFrameBuffer] FBO不完整" << std::endl;
    }

    // 解绑FBO
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
