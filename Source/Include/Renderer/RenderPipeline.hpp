/*
 * @Author: Vanish
 * @Date: 2024-11-13 16:44:09
 * @LastEditTime: 2024-11-13 19:57:24
 * Also View: http://vanishing.cc
 * Contract Me: http://qunchengxiao.me
 * Copyright@ http://www.wtfpl.net/
 */
/*
 * @Author: Vanish
 * @Date: 2024-11-13 16:44:09
 * @LastEditTime: 2024-11-13 16:44:53
 * Also View: http://vanishing.cc
 * Contract Me: http://qunchengxiao.me
 * Copyright@ http://www.wtfpl.net/
 */
#pragma once

#include <memory>
#include <Renderer/RenderResource.hpp>
#include <Renderer/RenderPass.hpp>

struct RenderPipelineInitInfo
{
    
};


class RenderPipeline
{
public:
    RenderPipeline() = default;
    virtual ~RenderPipeline() = default;

    virtual void Clear(){};
    virtual void Initialize(RenderPipelineInitInfo&& initInfo) = 0;

    virtual void PreparePassData(std::shared_ptr<RenderResource> renderResource);
    virtual void Render(std::shared_ptr<RenderResource> renderResource);

};

class RenderPipeline_Forward : public RenderPipeline
{
public:
    virtual void Initialize(RenderPipelineInitInfo&& initInfo) override final;
    virtual void Render(std::shared_ptr<RenderResource> renderResource) override final;

private:
    std::shared_ptr<RenderPass> m_SkyBoxPass;
    std::shared_ptr<RenderPass> m_PointLight_ShadowMap_Pass;
    std::shared_ptr<RenderPass> m_MainCameraForwardPass;
    std::shared_ptr<RenderPass> m_PostProcessPass;
};

class RenderPipeline_Deferred : public RenderPipeline
{
public:
    virtual void Initialize(RenderPipelineInitInfo&& initInfo) override final;
    virtual void Render(std::shared_ptr<RenderResource> renderResource) override final;

private:
    std::shared_ptr<RenderPass> m_SkyBoxPass;
    std::shared_ptr<RenderPass> m_PointLight_ShadowMap_Pass;
    std::shared_ptr<RenderPass> m_GBufferPass;
    std::shared_ptr<RenderPass> m_MainCameraDeferredPass;
    std::shared_ptr<RenderPass> m_PostProcessPass;
};