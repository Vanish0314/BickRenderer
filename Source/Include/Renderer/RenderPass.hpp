/*
 * @Author: Vanish
 * @Date: 2024-11-13 16:46:50
 * @LastEditTime: 2024-12-02 21:07:25
 * Also View: http://vanishing.cc
 * Contract Me: http://qunchengxiao.me
 * Copyright@ http://www.wtfpl.net/
 */
#pragma once

struct RenderResource;

#include <optional>
#include <memory>
#include <glad/glad.h>
#include "Renderer/RenderResource.hpp"

struct RenderPassSettings
{
    
};

struct RenderPassInitInfo
{
    std::weak_ptr<RenderResource> renderResource;
    RenderPassSettings settings;

    unsigned short width, height;

    GLint outputInternalFormat = GL_RGBA;
};

class RenderPass
{
public: 
	RenderPass(){}
	virtual ~RenderPass(){}
public: 
    virtual void Initialize(std::shared_ptr<RenderPassInitInfo> info);
    virtual void ChangeFBO(GLuint fbo);

    /// @brief 设置输入FBO和输出FBO,如果不指定则绘制在默认FBO上.绘制在默认FBO上会执行清除,绘制在指定上不会,需要手动清除
    void Draw(GLuint InputFBO = 0, std::optional<GLuint> OutputFBO = std::nullopt);

    virtual GLuint GetOutputTexture() const;
    virtual GLuint GetFBO() const;
    virtual void CleanUp();

protected:
    virtual void DrawPass(GLuint InputFBO,GLuint OutputFBO) = 0;
    virtual void ClearBuffer();
    virtual void UnBind();

private:
    void CreateFrameBuffer();

protected:
    std::shared_ptr<RenderResource> m_renderResource;

protected:
    GLuint m_fbo;
    GLuint m_outputTexture;
    int m_width = 1920, m_height = 1080;

    GLint m_outputInternalFormat = GL_RGBA;

    glm::vec4 m_clearColor = glm::vec4(0.3f, 0.57f, 0.4f, 1.0f);
};



class RenderPass_SkyBox : public RenderPass
{
public:
    virtual void Initialize(std::shared_ptr<RenderPassInitInfo> info) override final;
protected:
    virtual void DrawPass(GLuint InputFBO,GLuint OutputFBO) override final;

private:
    GLuint m_SkyBoxVAO;
    GLuint m_SkyBoxVBO;
    Shader m_SkyBoxShader;
    GLuint m_SkyBoxCubeMap;

private:
    static const float m_skyboxVertices[];
};


class RenderPass_PostProcess : public RenderPass
{
public:
    virtual void Initialize(std::shared_ptr<RenderPassInitInfo> info) override final;
protected:
    virtual void DrawPass(GLuint InputFBO,GLuint OutputFBO) override final;

private:
    GLuint m_PostProcessVAO;
    GLuint m_PostProcessVBO;
    Shader m_PostProcessShader;
    GLuint m_inputFBO;
private:
    static const float m_postProcessVertices[];
};