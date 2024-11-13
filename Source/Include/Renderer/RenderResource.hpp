#pragma once

#include <memory>
#include "Scene/Scene.hpp"

#include "Renderer/RenderPass_SkyBox.hpp"

class RenderResource
{
public:
    std::shared_ptr<Scene> scene;

public:
    RenderResource_SkyBox m_SkyBoxRenderResource;
};