#pragma once

#include <memory>
#include "Scene/Scene.hpp"

#include "Renderer/RenderPass.hpp"
#include "Renderer/RenderResource_SkyBox.hpp"

struct RenderResource
{
    std::shared_ptr<Scene> scene;

    RenderResource_SkyBox m_SkyBoxRenderResource;
};