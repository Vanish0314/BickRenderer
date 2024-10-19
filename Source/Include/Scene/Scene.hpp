/*
 * @Author: Vanish
 * @Date: 2024-10-15 15:23:57
 * @LastEditTime: 2024-10-15 15:42:56
 * Also View: http://vanishing.cc
 * Copyright@ https://creativecommons.org/licenses/by/4.0/deed.zh-hans
 */
#pragma once

#include <memory>
#include <vector>
#include <list>

#include "Common/Singleton.hpp"
#include "Mesh/Model.hpp"
#include "Light/DirectionalLight.hpp"
#include "Light/PointLight.hpp"

class Scene
{
public:
    friend class Singleton<Scene>;

public:
    std::vector<std::shared_ptr<Model>> models;
    std::vector<std::shared_ptr<DirectionalLight>> directionalLights;
    std::vector<std::shared_ptr<PointLight>> pointLights;
    
    std::shared_ptr<Camera> mainCamera;
    std::vector<std::shared_ptr<Camera>> cameras;

public:
    Scene() = default;
    ~Scene() = default;
};