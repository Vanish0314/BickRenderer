#pragma once

#include <memory>
#include "Scene/Scene.hpp"

#include "Renderer/RenderResource_SkyBox.hpp"
#include "Renderer/RenderResource_PostProcess.hpp"

/// 目前的想法是一个包含所有资源的结构体,为了方便配置场景,或许可以设计为单例模式.
struct RenderResource
{
    std::shared_ptr<Scene> scene;

    RenderResource_SkyBox m_SkyBoxRenderResource;
    RenderResource_PostProcess m_PostProcessRenderResource;
};