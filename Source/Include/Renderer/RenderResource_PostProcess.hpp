#pragma once

#include <string>
#include "Common/AssetPath.hpp"

/// @brief 后处理赞数不需要任何资源
struct RenderResource_PostProcess
{
    std::string postProcessVertShaderPath = "ScreenShader/vert.glsl";
    std::string postProcessFragShaderPath = "ScreenShader/frag.glsl";
};