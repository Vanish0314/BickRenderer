/*
 * @Author: Vanish
 * @Date: 2024-11-13 16:46:50
 * @LastEditTime: 2024-11-30 23:11:06
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

    /// @brief 设置输入FBO和输出FBO,如果不指定则绘制在默认FBO上.
    void Draw(GLuint InputFBO = 0, std::optional<GLuint> OutputFBO = std::nullopt);

    virtual GLuint GetOutputTexture() const;
    virtual GLuint GetFBO() const;
    virtual void CleanUp();

protected:
    virtual void DrawPass(GLuint InputFBO,GLuint OutputFBO) = 0;

private:
    void CreateFrameBuffer();

protected:
    std::shared_ptr<RenderResource> m_renderResource;

protected:
    GLuint m_fbo;
    GLuint m_outputTexture;
    int m_width, m_height;

    GLint m_outputInternalFormat;
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