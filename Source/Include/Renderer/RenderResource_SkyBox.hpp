/*
 * @Author: Vanish
 * @Date: 2024-11-13 20:03:06
 * @LastEditTime: 2024-11-13 20:08:57
 * Also View: http://vanishing.cc
 * Contract Me: http://qunchengxiao.me
 * Copyright@ http://www.wtfpl.net/
 */
#pragma once

#include <vector>
#include <string>

struct RenderResource_SkyBox
{
    /// @brief 按照顺序存储六个立方体贴图的路径
    std::vector<std::string> skyBoxTexturePath;
    std::string skyBoxVertShaderPath = "Source/GLSL_Shaders/SkyBox/cubemapvert.glsl";
    std::string skyBoxFragShaderPath = "Source/GLSL_Shaders/SkyBox/cubemapfrag.glsl";
};