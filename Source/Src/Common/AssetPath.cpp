/*
 * @Author: Vanish
 * @Date: 2025-09-10 20:15:00
 * @LastEditTime: 2025-09-10 20:15:00
 * Also View: http://vanishing.cc
 * Copyright@ https://creativecommons.org/licenses/by/4.0/deed.zh-hans
 */

#include "Common/AssetPath.hpp"
#include <iostream>
#include <filesystem>

// 静态成员变量定义
std::string AssetPath::s_runtimeAssetPath = "";
std::string AssetPath::s_runtimeShaderPath = "";
bool AssetPath::s_initialized = false;

void AssetPath::Initialize()
{
    if (s_initialized) {
        return;
    }

    s_runtimeAssetPath = FindAssetFolder();
    s_runtimeShaderPath = FindShaderFolder();
    s_initialized = true;

    std::cout << "[AssetPath] 资源路径初始化完成" << std::endl;
    std::cout << "[AssetPath] Assets路径: " << s_runtimeAssetPath << std::endl;
    std::cout << "[AssetPath] Shaders路径: " << s_runtimeShaderPath << std::endl;
}

std::string AssetPath::GetRuntimeAssetFolder()
{
    if (!s_initialized) {
        Initialize();
    }
    return s_runtimeAssetPath;
}

std::string AssetPath::GetAssetPath(const std::string& relativePath)
{
    if (!s_initialized) {
        Initialize();
    }
    
    if (s_runtimeAssetPath.empty()) {
        std::cerr << "[AssetPath] 错误: 找不到Assets文件夹!" << std::endl;
        return relativePath; // 返回原路径作为后备
    }
    
    std::filesystem::path fullPath = std::filesystem::path(s_runtimeAssetPath) / relativePath;
    return fullPath.string();
}

std::string AssetPath::GetShaderPath(const std::string& relativePath)
{
    if (!s_initialized) {
        Initialize();
    }
    
    if (s_runtimeShaderPath.empty()) {
        std::cerr << "[AssetPath] 错误: 找不到Shaders文件夹!" << std::endl;
        return relativePath; // 返回原路径作为后备
    }
    
    std::filesystem::path fullPath = std::filesystem::path(s_runtimeShaderPath) / relativePath;
    return fullPath.string();
}

bool AssetPath::FileExists(const std::string& path)
{
    return std::filesystem::exists(path);
}

std::string AssetPath::FindAssetFolder()
{
    namespace fs = std::filesystem;
    
    // 获取当前可执行文件的路径
    std::string currentPath = fs::current_path().string();
    
    // 可能的搜索路径列表
    std::vector<std::string> searchPaths = {
        currentPath + "/Assets",                    // 当前目录下的Assets
        currentPath + "/../Assets",                 // 上级目录的Assets
        currentPath + "/../../Assets",              // 上两级目录的Assets
        currentPath + "/../../../Assets",           // 上三级目录的Assets
        currentPath + "/../../../../Assets"         // 上四级目录的Assets
    };
    
    // 遍历搜索路径
    for (const auto& searchPath : searchPaths) {
        fs::path assetsPath = fs::path(searchPath);
        if (fs::exists(assetsPath) && fs::is_directory(assetsPath)) {
            return fs::canonical(assetsPath).string();
        }
    }
    
    std::cerr << "[AssetPath] 警告: 在以下路径中找不到Assets文件夹:" << std::endl;
    for (const auto& path : searchPaths) {
        std::cerr << "  - " << path << std::endl;
    }
    
    return "";
}

std::string AssetPath::FindShaderFolder()
{
    namespace fs = std::filesystem;
    
    // 获取当前可执行文件的路径
    std::string currentPath = fs::current_path().string();
    
    // 可能的搜索路径列表
    std::vector<std::string> searchPaths = {
        currentPath,                                // 当前目录下的着色器文件
        currentPath + "/Shaders",                   // 当前目录下的Shaders文件夹
        currentPath + "/GLSL_Shaders",              // 当前目录下的GLSL_Shaders文件夹
        currentPath + "/../Source/GLSL_Shaders",    // 相对路径到源码目录
        currentPath + "/../../Source/GLSL_Shaders", // 上两级目录的源码
        currentPath + "/../../../Source/GLSL_Shaders", // 上三级目录的源码
        currentPath + "/../../../../Source/GLSL_Shaders" // 上四级目录的源码
    };
    
    // 遍历搜索路径
    for (const auto& searchPath : searchPaths) {
        fs::path shaderPath = fs::path(searchPath);
        if (fs::exists(shaderPath) && fs::is_directory(shaderPath)) {
            // 检查是否包含一些常见的着色器文件夹
            if (fs::exists(shaderPath / "Blinn-PhongShader") || 
                fs::exists(shaderPath / "SkyBox") ||
                fs::exists(shaderPath / "ScreenShader")) {
                return fs::canonical(shaderPath).string();
            }
        }
    }
    
    std::cerr << "[AssetPath] 警告: 在以下路径中找不到着色器文件夹:" << std::endl;
    for (const auto& path : searchPaths) {
        std::cerr << "  - " << path << std::endl;
    }
    
    return "";
}
