#include "Bick.hpp"
#include "Renderer/RenderPass.hpp"

void RenderPass_PostProcess::Initialize(std::shared_ptr<RenderPassInitInfo> info)
{
    RenderPass::Initialize(info);

    auto res = m_renderResource;
    if(res)
    {
        auto vert = res->m_PostProcessRenderResource.postProcessVertShaderPath;
        auto frag = res->m_PostProcessRenderResource.postProcessFragShaderPath;
        m_PostProcessShader.InitShader(vert,frag,"PostProcessShader");

        //VAO
        glGenVertexArrays(1, &m_PostProcessVAO);
        glBindVertexArray(m_PostProcessVAO);
        //VBO
        glGenBuffers(1, &m_PostProcessVBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_PostProcessVBO);
        glBufferData(GL_ARRAY_BUFFER,6*4*sizeof(float), m_postProcessVertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));

        //解绑
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

void RenderPass_PostProcess::DrawPass(GLuint inputFBO, GLuint outputFBO)
{

    GLuint inputTexture = 0;
    glBindFramebuffer(GL_FRAMEBUFFER, inputFBO);
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, (GLint*)&inputTexture);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    if (inputTexture == 0) {
        std::cerr << "[RenderPass_PostProcess::DrawPass] 无法从输入FBO中获取颜色缓冲,请检查缓冲位置是否正确" << std::endl;
        return;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, outputFBO);
    glClearColor(1.0f, 0.1f, 0.5f, 1.0f);  // 清屏
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glBindVertexArray(m_PostProcessVAO);
    m_PostProcessShader.Use(); 
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, inputTexture);  // 绑定输入纹理
    GLuint textureLoc = glGetUniformLocation(m_PostProcessShader.shaderProgramID, "screenTexture");
    glUniform1i(textureLoc, GL_TEXTURE0);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    // 清理状态
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}

const float RenderPass_PostProcess::m_postProcessVertices[] = 
{
    // positions   // texCoords
    -1.0f, 1.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, 0.0f, 0.0f,
    1.0f, -1.0f, 1.0f, 0.0f,
    -1.0f, 1.0f, 0.0f, 1.0f,
    1.0f, -1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 1.0f, 1.0f
};