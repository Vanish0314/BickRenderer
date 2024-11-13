/*
 * @Author: Vanish
 * @Date: 2024-09-23 18:25:11
 * @LastEditTime: 2024-11-13 17:01:14
 * Also View: http://vanishing.cc
 * Contract Me: http://qunchengxiao.me
 * Copyright@ http://www.wtfpl.net/
 */
#pragma once

#include <memory>
#include "Common/Window.hpp"
#include "Scene/Scene.hpp"
#include "Camera/Camera.hpp"
#include "Renderer/RenderResource.hpp"
#include "Renderer/RenderPipeline.hpp"

struct RendererSystemInitInfo
{
    std::shared_ptr<Window> window;
    std::shared_ptr<Scene> scene;
    std::shared_ptr<RenderResource> renderResource;
};
class Renderer
{
public:
    Renderer() = default;
    ~Renderer() = default;

public:
    void Initialize(RendererSystemInitInfo&& initInfo);
    void Tick(float deltaTime);
    void Clear();
    void Shutdown();

private: 
    std::shared_ptr<Camera> m_Camera;
    std::shared_ptr<Scene> m_Scene;
    std::shared_ptr<RenderResource> m_RendererSystem;
    std::shared_ptr<RenderPipeline> m_RenderPipeline;
};