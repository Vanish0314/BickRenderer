#pragma once

#include <string>
#include <memory>
#include <iostream>
#include <glad/glad.h>
#include "Renderer/RenderResource.hpp"

struct RenderPassInitInfo
{
    std::weak_ptr<RenderResource> renderResource;

    unsigned short width, height;

    GLint outputInternalFormat = GL_RGBA;
};

class RenderPass
{
public: 
	RenderPass(){}
	virtual ~RenderPass(){}
public:
    //TODO: 应该传入一个共享指针而非右值引用
    virtual void Initialize(RenderPassInitInfo&& info){};
    virtual void Draw() = 0;
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