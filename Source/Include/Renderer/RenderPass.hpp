/*
 * @Author: Vanish
 * @Date: 2024-11-13 16:46:50
 * @LastEditTime: 2024-11-14 17:17:29
 * Also View: http://vanishing.cc
 * Contract Me: http://qunchengxiao.me
 * Copyright@ http://www.wtfpl.net/
 */
#pragma once

struct RenderResource;

#include <string>
#include <memory>
#include <iostream>
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
    /// @brief 绘制在Pass的FBO上
    virtual void Draw() = 0;
    /// @brief 绘制在指定的FBO上,FBO必须完整
    virtual void Draw(GLuint FBO) = 0;
    virtual GLuint GetOutputTexture() const;
    virtual GLuint GetFBO() const;
    virtual void CleanUp();

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
    virtual void Draw() override final;
    virtual void Draw(GLuint FBO) override final;

private:
    GLuint m_SkyBoxVAO;
    GLuint m_SkyBoxVBO;
    Shader m_SkyBoxShader;
    GLuint m_SkyBoxCubeMap;

private:
    static const float m_skyboxVertices[];
};
