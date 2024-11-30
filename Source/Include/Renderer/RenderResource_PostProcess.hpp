#pragma once

#include <string>

/// @brief 后处理赞数不需要任何资源
struct RenderResource_PostProcess
{
    std::string postProcessVertShaderPath ="Source/GLSL_Shaders/ScreenShader/vert.glsl";
    std::string postProcessFragShaderPath ="Source/GLSL_Shaders/ScreenShader/frag.glsl";
};