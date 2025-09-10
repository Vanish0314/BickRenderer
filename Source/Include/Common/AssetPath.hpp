/*
 * @Author: Vanish
 * @Date: 2025-09-10 20:15:00
 * @LastEditTime: 2025-09-10 20:15:00
 * Also View: http://vanishing.cc
 * Copyright@ https://creativecommons.org/licenses/by/4.0/deed.zh-hans
 */

#pragma once

#include <string>
#include <filesystem>

/**
 * @brief 资源路径管理类
 * 提供统一的资源路径访问接口，支持开发和运行时的不同路径结构
 */
class AssetPath
{
public:
    /**
     * @brief 获取运行时资源文件夹的根路径
     * @return 资源文件夹的绝对路径
     */
    static std::string GetRuntimeAssetFolder();

    /**
     * @brief 获取完整的资源文件路径
     * @param relativePath 相对于Assets文件夹的路径，如："Textures/Skybox/MountainSea/right.jpg"
     * @return 完整的文件路径
     */
    static std::string GetAssetPath(const std::string& relativePath);

    /**
     * @brief 获取着色器文件路径
     * @param relativePath 相对于GLSL_Shaders文件夹的路径，如："Blinn-PhongShader/StdBlinnPhongVertex.glsl"
     * @return 完整的着色器文件路径
     */
    static std::string GetShaderPath(const std::string& relativePath);

    /**
     * @brief 检查文件是否存在
     * @param path 文件路径
     * @return 文件是否存在
     */
    static bool FileExists(const std::string& path);

    /**
     * @brief 初始化资源路径系统
     * 在程序启动时调用，用于确定资源文件夹的位置
     */
    static void Initialize();

private:
    static std::string s_runtimeAssetPath;
    static std::string s_runtimeShaderPath;
    static bool s_initialized;

    /**
     * @brief 查找资源文件夹的位置
     * @return 资源文件夹路径，如果找不到返回空字符串
     */
    static std::string FindAssetFolder();

    /**
     * @brief 查找着色器文件夹的位置
     * @return 着色器文件夹路径，如果找不到返回空字符串
     */
    static std::string FindShaderFolder();
};
