/*
 * @Author: Vanish
 * @Date: 2024-09-20 10:50:34
 * @LastEditTime: 2025-01-13 20:59:46
 * Also View: http://vanishing.cc
 * Copyright@ https://creativecommons.org/licenses/by/4.0/deed.zh-hans
 */
#pragma once

#include <memory>
#include <glm/gtc/type_ptr.hpp>
#include "Shader/Shader.hpp"
#include "Object/Object.hpp"

class Material
{
public:
    std::shared_ptr<Shader> shader;

public:
    Material(std::shared_ptr<Shader> shader) : shader(shader) {}

public:
    virtual void Use(Transform myTransform) = 0;
};